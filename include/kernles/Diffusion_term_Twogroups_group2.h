#pragma once

#include "Diffusion.h"

class Diffusion_term_Twogroups_group2 : public Diffusion
{
public:
    Diffusion_term_Twogroups_group2(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _diffusion_coefficient;
};