#include "Material_TWIGL_Singlegroup.h"

registerMooseObject("diffusion_2DApp", Material_TWIGL_Singlegroup);

InputParameters Material_TWIGL_Singlegroup::validParams()
{
    InputParameters params = Material::validParams();
    params.addClassDescription("For meterial 1 in TWIGL");
    params.addRequiredParam<Real>("diffusion_coefficient", "add diffusion coefficient");
    params.addRequiredParam<Real>("absorption_cross_section", "add absorption cross section");
    params.addRequiredParam<Real>("fission_cross_section_v", "add fission cross section v");
    return params;
}

Material_TWIGL_Singlegroup::Material_TWIGL_Singlegroup(const InputParameters & parameters)
    :   Material(parameters),
        _input_diffusion_coefficient(getParam<Real>("diffusion_coefficient")),
        _input_absorption_cross_section(getParam<Real>("absorption_cross_section")),
        _input_fission_cross_section_v(getParam<Real>("fission_cross_section_v")),
        _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
        _absorption_cross_section(declareProperty<Real>("absorption_cross_section")),
        _fission_cross_section_v(declareProperty<Real>("fission_cross_section_v"))
{
}

void Material_TWIGL_Singlegroup::computeQpProperties()
{
    _diffusion_coefficient[_qp] = _input_diffusion_coefficient;
    _absorption_cross_section[_qp] = _input_absorption_cross_section;
    _fission_cross_section_v[_qp] = _input_fission_cross_section_v;
}