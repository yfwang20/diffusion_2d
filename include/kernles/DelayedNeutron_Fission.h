#pragma once

#include "Kernel.h"

class DelayedNeutron_Fission : public Kernel
{
public:
  DelayedNeutron_Fission(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const Real & _num;
  const Real & _coefficient;
  const MaterialProperty<Real> & _beta;
  const MaterialProperty<Real> & _fission_cross_section_v_group1;
  const MaterialProperty<Real> & _fission_cross_section_v_group2;
  const VariableValue & _flux_group1;
  const VariableValue & _flux_group2;
};