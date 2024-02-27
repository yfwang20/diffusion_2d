#include "Absorption.h"
registerMooseObject("diffusion_2DApp", Absorption);

InputParameters Absorption::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Absorption::Absorption(const InputParameters & parameters)
    :   Kernel(parameters),
        _absorption_cross_section(getMaterialProperty<Real>("absorption_cross_section"))
{
}

Real Absorption::computeQpResidual()
{
    return _test[_i][_qp] * (_absorption_cross_section[_qp] * _u[_qp]);
}

Real Absorption::computeQpJacobian()
{
     return _test[_i][_qp] * (_absorption_cross_section[_qp] * _phi[_j][_qp]);
}