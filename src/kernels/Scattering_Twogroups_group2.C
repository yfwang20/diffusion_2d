#include "Scattering_Twogroups_group2.h"

registerMooseObject("diffusion_2DApp", Scattering_Twogroups_group2);

InputParameters Scattering_Twogroups_group2::validParams()
{
    InputParameters params = Kernel::validParams();

    params.addRequiredCoupledVar("otherflux_1", "Couple other flux.");

    return params;
}

Scattering_Twogroups_group2::Scattering_Twogroups_group2(const InputParameters & parameters)
  :   Kernel(parameters),
        _sigma_s(getMaterialProperty<Real>("scattering_cross_section_group1to2")),
        _otherflux(coupledValue("otherflux_1")),
        _otherflux_var(coupled("otherflux_1"))
{
}

Real Scattering_Twogroups_group2::computeQpResidual()
{
  return -_test[_i][_qp] * _sigma_s[_qp] * _otherflux[_qp];
}

Real Scattering_Twogroups_group2::computeQpJacobian()
{
  return 0.0;
}

Real Scattering_Twogroups_group2::computeQpOffDiagJacobian(unsigned int jvar)
{
  if(jvar == _otherflux_var)
  {
    return -_test[_i][_qp] * _sigma_s[_qp] * _phi[_j][_qp];
  }
  return 0.0;
}
