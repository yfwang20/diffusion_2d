#pragma once

#include "Kernel.h"

class Scattering_Twogroups_group2 : public Kernel
{
public:
    Scattering_Twogroups_group2(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _sigma_s;
    const VariableValue & _otherflux;
};