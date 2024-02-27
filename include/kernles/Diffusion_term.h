#pragma once

#include "Kernel.h"

class Diffusion_term : public Kernel
{
public:
    Diffusion_term(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _diffusion_coefficient;
};