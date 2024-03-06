#pragma once

#include "EigenKernel.h"

class Eigenkernel_Fission_Twogroups_group2 : public EigenKernel
{
public:
    Eigenkernel_Fission_Twogroups_group2(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    // virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _kai;
    const MaterialProperty<Real> & _fission_cross_section_v_local;
    const MaterialProperty<Real> & _fission_cross_section_v_other;
    const VariableValue & _otherflux;
};