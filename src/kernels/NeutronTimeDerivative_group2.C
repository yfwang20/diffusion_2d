#include "NeutronTimeDerivative_group2.h"

registerMooseObject("diffusion_2DApp", NeutronTimeDerivative_group2);

InputParameters NeutronTimeDerivative_group2::validParams()
{
  InputParameters params = TimeDerivative::validParams();
  return params;
}

NeutronTimeDerivative_group2::NeutronTimeDerivative_group2(const InputParameters & parameters)
  : TimeDerivative(parameters), _velocity(getMaterialProperty<Real>("velocity_group2"))
{
}

Real
NeutronTimeDerivative_group2::computeQpResidual()
{
  return TimeDerivative::computeQpResidual() / _velocity[_qp];
}

Real
NeutronTimeDerivative_group2::computeQpJacobian()
{
  return TimeDerivative::computeQpJacobian() / _velocity[_qp];
}