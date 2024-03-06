#include "Scattering_Twogroups_group1.h"

registerMooseObject("diffusion_2DApp", Scattering_Twogroups_group1);

InputParameters Scattering_Twogroups_group1::validParams()
{
    InputParameters params = Kernel::validParams();

    params.addRequiredCoupledVar("otherflux_1", "Couple other flux.");

    return params;
}

Scattering_Twogroups_group1::Scattering_Twogroups_group1(const InputParameters & parameters)
  :   Kernel(parameters),
        _sigma_s(getMaterialProperty<Real>("scattering_cross_section_group2to1")),
        _otherflux(coupledValue("otherflux_1"))
{
}

Real Scattering_Twogroups_group1::computeQpResidual()
{
  return -_test[_i][_qp] * _sigma_s[_qp] * _otherflux[_qp];
}

Real Scattering_Twogroups_group1::computeQpJacobian()
{
  return 0.0;
}
