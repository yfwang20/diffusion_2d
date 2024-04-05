#pragma once

#include "Kernel.h"

class Scattering_Twogroups_group1 : public Kernel
{
public:
    Scattering_Twogroups_group1(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _sigma_s;
    const VariableValue & _otherflux;
    unsigned int _otherflux_var;
};