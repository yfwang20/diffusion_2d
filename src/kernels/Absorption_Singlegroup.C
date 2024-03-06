#include "Absorption_Singlegroup.h"
registerMooseObject("diffusion_2DApp", Absorption_Singlegroup);

InputParameters Absorption_Singlegroup::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Absorption_Singlegroup::Absorption_Singlegroup(const InputParameters & parameters)
    :   Kernel(parameters),
        _absorption_cross_section(getMaterialProperty<Real>("absorption_cross_section"))
{
}

Real Absorption_Singlegroup::computeQpResidual()
{
    return _test[_i][_qp] * (_absorption_cross_section[_qp] * _u[_qp]);
}

Real Absorption_Singlegroup::computeQpJacobian()
{
    return _test[_i][_qp] * (_absorption_cross_section[_qp] * _phi[_j][_qp]);
}