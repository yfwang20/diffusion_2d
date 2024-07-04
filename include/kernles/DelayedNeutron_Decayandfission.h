#pragma once

#include "Kernel.h"

class DelayedNeutron_Decayandfission : public Kernel
{
public:
  DelayedNeutron_Decayandfission(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;
  
  const Real & _num;
  const Real & _keff;
  const MaterialProperty<Real> & _lambda;
  const MaterialProperty<Real> & _beta;
  const MaterialProperty<Real> & _fission_cross_section_v_group1;
  const MaterialProperty<Real> & _fission_cross_section_v_group2;
  const VariableValue & _flux_group1;
  const VariableValue & _flux_group2;
  const VariableValue & _fission;
  unsigned int _flux1_var;
  unsigned int _flux2_var;
};