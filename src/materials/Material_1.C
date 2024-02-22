#include "Material_1.h"

registerMooseObject("diffusion_2DApp", Material_1);

InputParameters Material_1::validParams()
{
    InputParameters params = Material::validParams();
    params.addClassDescription("For meterial 1 in TWIGL");
    params.addRequiredParam<Real>("diffusion_coefficient", "add diffusion coefficient");
    params.addRequiredParam<Real>("absorption_cross_section", "add absorption cross section");
    params.addRequiredParam<Real>("fission_cross_section_v", "add fission cross section v");
    return params;
}

Material_1::Material_1(const InputParameters & parameters)
    :   Material(parameters),
        _input_diffusion_coefficient(getParam<Real>("diffusion_coefficient")),
        _input_absorption_cross_section(getParam<Real>("absorption_cross_section")),
        _input_fission_cross_section_v(getParam<Real>("fission_cross_section_v")),
        _diffusion_coefficient(declareADProperty<Real>("diffusion_coefficient")),
        _absorption_cross_section(declareADProperty<Real>("absorption_cross_section")),
        _fission_cross_section_v(declareADProperty<Real>("fission_cross_section_v"))
{
}

void Material_1::computeQpProperties()
{
    _diffusion_coefficient[_qp] = _input_diffusion_coefficient;
    _absorption_cross_section[_qp] = _input_absorption_cross_section;
    _fission_cross_section_v[_qp] = _input_fission_cross_section_v;
}