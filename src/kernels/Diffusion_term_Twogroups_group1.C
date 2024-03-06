#include "Diffusion_term_Twogroups_group1.h"
registerMooseObject("diffusion_2DApp", Diffusion_term_Twogroups_group1);

InputParameters Diffusion_term_Twogroups_group1::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Diffusion_term_Twogroups_group1::Diffusion_term_Twogroups_group1(const InputParameters & parameters)
    :   Diffusion(parameters),
        _diffusion_coefficient(getMaterialProperty<Real>("diffusion_coefficient_group1"))
{
}

Real Diffusion_term_Twogroups_group1::computeQpResidual()
{
    return _diffusion_coefficient[_qp] * Diffusion::computeQpResidual();
}

Real Diffusion_term_Twogroups_group1::computeQpJacobian()
{
    return _diffusion_coefficient[_qp] * Diffusion::computeQpJacobian();
}