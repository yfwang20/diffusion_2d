#pragma once

#include "TimeDerivative.h"

class NeutronTimeDerivative_group2 : public TimeDerivative
{
public:
  NeutronTimeDerivative_group2(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _velocity;
};