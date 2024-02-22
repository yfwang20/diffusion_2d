#pragma once

#include "Material.h"

class Material_1 : public Material
{
public:
    static InputParameters validParams();

    Material_1(const InputParameters & parameters);

protected:
    virtual void computeQpProperties() override;

    const Real & _input_diffusion_coefficient;
    const Real & _input_absorption_cross_section;
    const Real & _input_fission_cross_section_v;

    ADMaterialProperty<Real> & _diffusion_coefficient;
    ADMaterialProperty<Real> & _absorption_cross_section;
    ADMaterialProperty<Real> & _fission_cross_section_v;
};

