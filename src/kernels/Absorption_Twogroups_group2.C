#include "Absorption_Twogroups_group2.h"
registerMooseObject("diffusion_2DApp", Absorption_Twogroups_group2);

InputParameters Absorption_Twogroups_group2::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Absorption_Twogroups_group2::Absorption_Twogroups_group2(const InputParameters & parameters)
    :   Kernel(parameters),
        _absorption_cross_section(getMaterialProperty<Real>("absorption_cross_section_group2")),
        _sigma_s(getMaterialProperty<Real>("scattering_cross_section_group2to1"))
{
}

Real Absorption_Twogroups_group2::computeQpResidual()
{
    return _test[_i][_qp] * (_absorption_cross_section[_qp] + _sigma_s[_qp]) * _u[_qp];
}

Real Absorption_Twogroups_group2::computeQpJacobian()
{
    return _test[_i][_qp] * (_absorption_cross_section[_qp] + _sigma_s[_qp]) * _phi[_j][_qp];
}