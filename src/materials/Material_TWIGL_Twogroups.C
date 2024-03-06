#include "Material_TWIGL_Twogroups.h"

registerMooseObject("diffusion_2DApp", Material_TWIGL_Twogroups);

InputParameters Material_TWIGL_Twogroups::validParams()
{
    InputParameters params = Material::validParams();
    params.addClassDescription("For meterial in TWIGL");
    params.addRequiredParam<Real>("diffusion_coefficient_group1", "add diffusion_coefficient_group1t");
    params.addRequiredParam<Real>("diffusion_coefficient_group2", "add diffusion_coefficient_group2");

    params.addRequiredParam<Real>("absorption_cross_section_group1", "add absorption_cross_section_group1");
    params.addRequiredParam<Real>("absorption_cross_section_group2", "add absorption_cross_section_group2");

    params.addRequiredParam<Real>("scattering_cross_section_group1to2", "add scattering_cross_section_group1to2");
    params.addRequiredParam<Real>("scattering_cross_section_group2to1", "add scattering_cross_section_group2to1");

    params.addRequiredParam<Real>("kai_group1", "add kai_group1");
    params.addRequiredParam<Real>("kai_group2", "add kai_group2");

    params.addRequiredParam<Real>("fission_cross_section_v_group1", "add fission_cross_section_v_group1");
    params.addRequiredParam<Real>("fission_cross_section_v_group2", "add fission_cross_section_v_group2");
    return params;
}

Material_TWIGL_Twogroups::Material_TWIGL_Twogroups(const InputParameters & parameters)
    :   Material(parameters),
        _input_diffusion_coefficient_group1(getParam<Real>("diffusion_coefficient_group1")),
        _input_diffusion_coefficient_group2(getParam<Real>("diffusion_coefficient_group2")),
        _input_absorption_cross_section_group1(getParam<Real>("absorption_cross_section_group1")),
        _input_absorption_cross_section_group2(getParam<Real>("absorption_cross_section_group2")),
        _input_scattering_cross_section_group1to2(getParam<Real>("scattering_cross_section_group1to2")),
        _input_scattering_cross_section_group2to1(getParam<Real>("scattering_cross_section_group2to1")),
        _input_kai_group1(getParam<Real>("kai_group1")),
        _input_kai_group2(getParam<Real>("kai_group2")),
        _input_fission_cross_section_v_group1(getParam<Real>("fission_cross_section_v_group1")),
        _input_fission_cross_section_v_group2(getParam<Real>("fission_cross_section_v_group2")),

        _diffusion_coefficient_group1(declareProperty<Real>("diffusion_coefficient_group1")),
        _diffusion_coefficient_group2(declareProperty<Real>("diffusion_coefficient_group2")),
        _absorption_cross_section_group1(declareProperty<Real>("absorption_cross_section_group1")),
        _absorption_cross_section_group2(declareProperty<Real>("absorption_cross_section_group2")),
        _scattering_cross_section_group1to2(declareProperty<Real>("scattering_cross_section_group1to2")),
        _scattering_cross_section_group2to1(declareProperty<Real>("scattering_cross_section_group2to1")),
        _kai_group1(declareProperty<Real>("kai_group1")),
        _kai_group2(declareProperty<Real>("kai_group2")),
        _fission_cross_section_v_group1(declareProperty<Real>("fission_cross_section_v_group1")),
        _fission_cross_section_v_group2(declareProperty<Real>("fission_cross_section_v_group2"))
{
}

void Material_TWIGL_Twogroups::computeQpProperties()
{
    _diffusion_coefficient_group1[_qp] = _input_diffusion_coefficient_group1;
    _diffusion_coefficient_group2[_qp] = _input_diffusion_coefficient_group2;
    _absorption_cross_section_group1[_qp] = _input_absorption_cross_section_group1;
    _absorption_cross_section_group2[_qp] = _input_absorption_cross_section_group2;
    _scattering_cross_section_group1to2[_qp] = _input_scattering_cross_section_group1to2;
    _scattering_cross_section_group2to1[_qp] = _input_scattering_cross_section_group2to1;
    _kai_group1[_qp] = _input_kai_group1;
    _kai_group2[_qp] = _input_kai_group2;
    _fission_cross_section_v_group1[_qp] = _input_fission_cross_section_v_group1;
    _fission_cross_section_v_group2[_qp] = _input_fission_cross_section_v_group2;
}