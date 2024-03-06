#include "Diffusion_term_Singlegroup.h"
registerMooseObject("diffusion_2DApp", Diffusion_term_Singlegroup);

InputParameters Diffusion_term_Singlegroup::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Diffusion_term_Singlegroup::Diffusion_term_Singlegroup(const InputParameters & parameters)
    :   Kernel(parameters),
        _diffusion_coefficient(getMaterialProperty<Real>("diffusion_coefficient"))
{
}

Real Diffusion_term_Singlegroup::computeQpResidual()
{
    return _diffusion_coefficient[_qp] * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real Diffusion_term_Singlegroup::computeQpJacobian()
{
    return _diffusion_coefficient[_qp] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}