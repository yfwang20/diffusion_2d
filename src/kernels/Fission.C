#include "Fission.h"
registerMooseObject("diffusion_2DApp", Fission);

InputParameters Fission::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addParam<Real>("coefficient", 1.0, "Sign for eigenvalue problem.");
    return params;
}

Fission::Fission(const InputParameters & parameters)
    :   Kernel(parameters),
        _fission_cross_section_v(getMaterialProperty<Real>("fission_cross_section_v")),
        _coefficient(getParam<Real>("coefficient"))
{
}

Real Fission::computeQpResidual()
{
    return _coefficient * _test[_i][_qp] * (_fission_cross_section_v[_qp] * _u[_qp]);
}

Real Fission::computeQpJacobian()
{
    return _coefficient * _test[_i][_qp] * (_fission_cross_section_v[_qp] * _phi[_j][_qp]);
}