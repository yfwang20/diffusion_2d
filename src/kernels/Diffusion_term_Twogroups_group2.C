#include "Diffusion_term_Twogroups_group2.h"
registerMooseObject("diffusion_2DApp", Diffusion_term_Twogroups_group2);

InputParameters Diffusion_term_Twogroups_group2::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Diffusion_term_Twogroups_group2::Diffusion_term_Twogroups_group2(const InputParameters & parameters)
    :   Diffusion(parameters),
        _diffusion_coefficient(getMaterialProperty<Real>("diffusion_coefficient_group2"))
{
}

Real Diffusion_term_Twogroups_group2::computeQpResidual()
{
    return _diffusion_coefficient[_qp] * Diffusion::computeQpResidual();
}

Real Diffusion_term_Twogroups_group2::computeQpJacobian()
{
    return _diffusion_coefficient[_qp] * Diffusion::computeQpJacobian();
}