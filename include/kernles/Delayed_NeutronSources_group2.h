#pragma once

#include "Kernel.h"

class Delayed_NeutronSources_group2 : public Kernel
{
public:
  Delayed_NeutronSources_group2(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const VariableValue & _delayed_nucleus;
  const MaterialProperty<Real> & _kai;
};