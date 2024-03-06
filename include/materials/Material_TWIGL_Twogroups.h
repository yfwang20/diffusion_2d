#pragma once

#include "Material.h"

class Material_TWIGL_Twogroups : public Material
{
public:
    static InputParameters validParams();

    Material_TWIGL_Twogroups(const InputParameters & parameters);

protected:
    virtual void computeQpProperties() override;

    const Real & _input_diffusion_coefficient_group1;
    const Real & _input_diffusion_coefficient_group2;

    const Real & _input_absorption_cross_section_group1;
    const Real & _input_absorption_cross_section_group2;

    const Real & _input_scattering_cross_section_group1to2;
    const Real & _input_scattering_cross_section_group2to1;

    const Real & _input_kai_group1;
    const Real & _input_kai_group2;

    const Real & _input_fission_cross_section_v_group1;
    const Real & _input_fission_cross_section_v_group2;


    MaterialProperty<Real> & _diffusion_coefficient_group1;
    MaterialProperty<Real> & _diffusion_coefficient_group2;

    MaterialProperty<Real> & _absorption_cross_section_group1;
    MaterialProperty<Real> & _absorption_cross_section_group2;

    MaterialProperty<Real> & _scattering_cross_section_group1to2;
    MaterialProperty<Real> & _scattering_cross_section_group2to1;

    MaterialProperty<Real> & _kai_group1;
    MaterialProperty<Real> & _kai_group2;

    MaterialProperty<Real> & _fission_cross_section_v_group1;
    MaterialProperty<Real> & _fission_cross_section_v_group2;
};

