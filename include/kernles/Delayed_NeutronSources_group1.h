#pragma once

#include "Kernel.h"

class Delayed_NeutronSources_group1 : public Kernel
{
public:
  Delayed_NeutronSources_group1(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const VariableValue & _delayed_nucleus;
  const MaterialProperty<Real> & _kai;
};