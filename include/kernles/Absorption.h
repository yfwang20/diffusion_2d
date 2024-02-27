#pragma once

#include "Kernel.h"

class Absorption : public Kernel
{
public:
    Absorption(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _absorption_cross_section;
};