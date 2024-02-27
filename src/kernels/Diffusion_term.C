#include "Diffusion_term.h"
registerMooseObject("diffusion_2DApp", Diffusion_term);

InputParameters Diffusion_term::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Diffusion_term::Diffusion_term(const InputParameters & parameters)
    :   Kernel(parameters),
        _diffusion_coefficient(getMaterialProperty<Real>("diffusion_coefficient"))
{
}

Real Diffusion_term::computeQpResidual()
{
    return -_grad_test[_i][_qp] * (_diffusion_coefficient[_qp] * _grad_u[_qp]);
}

Real Diffusion_term::computeQpJacobian()
{
     return -_grad_test[_i][_qp] * (_diffusion_coefficient[_qp] * _grad_phi[_j][_qp]);
}