#pragma once

#include "Kernel.h"

class Absorption_Twogroups_group1 : public Kernel
{
public:
    Absorption_Twogroups_group1(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _absorption_cross_section;
    const MaterialProperty<Real> & _sigma_s;
};