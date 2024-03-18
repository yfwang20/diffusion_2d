#pragma once

#include "Kernel.h"

class Fission_Twogroups_Transientproblem_group2 : public Kernel
{
public:
    Fission_Twogroups_Transientproblem_group2(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _beta;
    const MaterialProperty<Real> & _kai;
    const MaterialProperty<Real> & _fission_cross_section_v_local;
    const MaterialProperty<Real> & _fission_cross_section_v_other;
    const VariableValue & _otherflux;
    const Real & _keff;
    const Real & _coefficient;
};