#include "Absorption_Twogroups_group1.h"
registerMooseObject("diffusion_2DApp", Absorption_Twogroups_group1);

InputParameters Absorption_Twogroups_group1::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Absorption_Twogroups_group1::Absorption_Twogroups_group1(const InputParameters & parameters)
    :   Kernel(parameters),
        _absorption_cross_section(getMaterialProperty<Real>("absorption_cross_section_group1")),
        _sigma_s(getMaterialProperty<Real>("scattering_cross_section_group1to2"))
{
}

Real Absorption_Twogroups_group1::computeQpResidual()
{
    return _test[_i][_qp] * (_absorption_cross_section[_qp] + _sigma_s[_qp]) * _u[_qp];
}

Real Absorption_Twogroups_group1::computeQpJacobian()
{
    return _test[_i][_qp] * (_absorption_cross_section[_qp] + _sigma_s[_qp]) * _phi[_j][_qp];
}