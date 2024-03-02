#pragma once

#include "Kernel.h"

class Fission : public Kernel
{
public:
    Fission(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _fission_cross_section_v;
    const Real & _coefficient;
};