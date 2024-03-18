#pragma once

#include "TimeDerivative.h"

class NeutronTimeDerivative_group1 : public TimeDerivative
{
public:
  NeutronTimeDerivative_group1(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _velocity;
};