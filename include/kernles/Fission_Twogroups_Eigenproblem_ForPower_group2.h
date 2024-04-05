#pragma once

#include "EigenKernel.h"

class Fission_Twogroups_Eigenproblem_ForPower_group2 : public EigenKernel
{
public:
    Fission_Twogroups_Eigenproblem_ForPower_group2(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _kai;
    const MaterialProperty<Real> & _fission_cross_section_v_local;
    const MaterialProperty<Real> & _fission_cross_section_v_other;
    const VariableValue & _otherflux;
    unsigned int _otherflux_var;
};