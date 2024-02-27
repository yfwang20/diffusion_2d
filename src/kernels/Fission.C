#include "Fission.h"
registerMooseObject("diffusion_2DApp", Fission);

InputParameters Fission::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Fission::Fission(const InputParameters & parameters)
    :   Kernel(parameters),
        _fission_cross_section_v(getMaterialProperty<Real>("fission_cross_section_v"))
{
}

Real Fission::computeQpResidual()
{
    return _test[_i][_qp] * (_fission_cross_section_v[_qp] * _u[_qp]);
}

Real Fission::computeQpJacobian()
{
     return _test[_i][_qp] * (_fission_cross_section_v[_qp] * _phi[_j][_qp]);
}