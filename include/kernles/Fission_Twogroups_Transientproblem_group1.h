#pragma once

#include "Kernel.h"

class Fission_Twogroups_Transientproblem_group1 : public Kernel
{
public:
    Fission_Twogroups_Transientproblem_group1(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _beta;
    const MaterialProperty<Real> & _kai;
    const MaterialProperty<Real> & _fission_cross_section_v_local;
    const MaterialProperty<Real> & _fission_cross_section_v_other;
    const VariableValue & _otherflux;
    const Real & _keff;
    const Real & _coefficient;
    unsigned int _otherflux_var;
};