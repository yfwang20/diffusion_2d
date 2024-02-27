#pragma once

#include "Material.h"

class Material_3 : public Material
{
public:
    static InputParameters validParams();

    Material_3(const InputParameters & parameters);

protected:
    virtual void computeQpProperties() override;

    const Real & _input_diffusion_coefficient;
    const Real & _input_absorption_cross_section;
    const Real & _input_fission_cross_section_v;

    MaterialProperty<Real> & _diffusion_coefficient;
    MaterialProperty<Real> & _absorption_cross_section;
    MaterialProperty<Real> & _fission_cross_section_v;
};

