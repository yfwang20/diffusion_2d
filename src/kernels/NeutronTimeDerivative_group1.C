#include "NeutronTimeDerivative_group1.h"

registerMooseObject("diffusion_2DApp", NeutronTimeDerivative_group1);

InputParameters NeutronTimeDerivative_group1::validParams()
{
  InputParameters params = TimeDerivative::validParams();
  return params;
}

NeutronTimeDerivative_group1::NeutronTimeDerivative_group1(const InputParameters & parameters)
  : TimeDerivative(parameters), _velocity(getMaterialProperty<Real>("velocity_group1"))
{
}

Real
NeutronTimeDerivative_group1::computeQpResidual()
{
  return TimeDerivative::computeQpResidual() / _velocity[_qp];
}

Real
NeutronTimeDerivative_group1::computeQpJacobian()
{
  return TimeDerivative::computeQpJacobian() / _velocity[_qp];
}