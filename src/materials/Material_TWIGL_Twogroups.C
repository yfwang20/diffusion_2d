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

    params.addRequiredParam<Real>("velocity_group1", "add velocity_group1");
    params.addRequiredParam<Real>("velocity_group2", "add velocity_group2");

    params.addRequiredParam<Real>("beta", "add beta");
    params.addRequiredParam<Real>("beta_1", "add beta_1");
    params.addRequiredParam<Real>("beta_2", "add beta_2");
    params.addRequiredParam<Real>("beta_3", "add beta_3");
    params.addRequiredParam<Real>("beta_4", "add beta_4");
    params.addRequiredParam<Real>("beta_5", "add beta_5");
    params.addRequiredParam<Real>("beta_6", "add beta_6");

    params.addRequiredParam<Real>("lambda_1", "add lambda_1");
    params.addRequiredParam<Real>("lambda_2", "add lambda_2");
    params.addRequiredParam<Real>("lambda_3", "add lambda_3");
    params.addRequiredParam<Real>("lambda_4", "add lambda_4");
    params.addRequiredParam<Real>("lambda_5", "add lambda_5");
    params.addRequiredParam<Real>("lambda_6", "add lambda_6");

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
        _input_velocity_group1(getParam<Real>("velocity_group1")),
        _input_velocity_group2(getParam<Real>("velocity_group2")),
        _input_beta(getParam<Real>("beta")),
        _input_beta_1(getParam<Real>("beta_1")),
        _input_beta_2(getParam<Real>("beta_2")),
        _input_beta_3(getParam<Real>("beta_3")),
        _input_beta_4(getParam<Real>("beta_4")),
        _input_beta_5(getParam<Real>("beta_5")),
        _input_beta_6(getParam<Real>("beta_6")),
        _input_lambda_1(getParam<Real>("lambda_1")),
        _input_lambda_2(getParam<Real>("lambda_2")),
        _input_lambda_3(getParam<Real>("lambda_3")),
        _input_lambda_4(getParam<Real>("lambda_4")),
        _input_lambda_5(getParam<Real>("lambda_5")),
        _input_lambda_6(getParam<Real>("lambda_6")),

        _diffusion_coefficient_group1(declareProperty<Real>("diffusion_coefficient_group1")),
        _diffusion_coefficient_group2(declareProperty<Real>("diffusion_coefficient_group2")),
        _absorption_cross_section_group1(declareProperty<Real>("absorption_cross_section_group1")),
        _absorption_cross_section_group2(declareProperty<Real>("absorption_cross_section_group2")),
        _scattering_cross_section_group1to2(declareProperty<Real>("scattering_cross_section_group1to2")),
        _scattering_cross_section_group2to1(declareProperty<Real>("scattering_cross_section_group2to1")),
        _kai_group1(declareProperty<Real>("kai_group1")),
        _kai_group2(declareProperty<Real>("kai_group2")),
        _fission_cross_section_v_group1(declareProperty<Real>("fission_cross_section_v_group1")),
        _fission_cross_section_v_group2(declareProperty<Real>("fission_cross_section_v_group2")),
        _velocity_group1(declareProperty<Real>("velocity_group1")),
        _velocity_group2(declareProperty<Real>("velocity_group2")),
        _beta(declareProperty<Real>("beta")),
        _beta_1(declareProperty<Real>("beta_1")),
        _beta_2(declareProperty<Real>("beta_2")),
        _beta_3(declareProperty<Real>("beta_3")),
        _beta_4(declareProperty<Real>("beta_4")),
        _beta_5(declareProperty<Real>("beta_5")),
        _beta_6(declareProperty<Real>("beta_6")),
        _lambda_1(declareProperty<Real>("lambda_1")),
        _lambda_2(declareProperty<Real>("lambda_2")),
        _lambda_3(declareProperty<Real>("lambda_3")),
        _lambda_4(declareProperty<Real>("lambda_4")),
        _lambda_5(declareProperty<Real>("lambda_5")),
        _lambda_6(declareProperty<Real>("lambda_6"))
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
    _velocity_group1[_qp] = _input_velocity_group1;
    _velocity_group2[_qp] = _input_velocity_group2;
    _beta[_qp] = _input_beta;
    _beta_1[_qp] = _input_beta_1;
    _beta_2[_qp] = _input_beta_2;
    _beta_3[_qp] = _input_beta_3;
    _beta_4[_qp] = _input_beta_4;
    _beta_5[_qp] = _input_beta_5;
    _beta_6[_qp] = _input_beta_6;
    _lambda_1[_qp] = _input_lambda_1;
    _lambda_2[_qp] = _input_lambda_2;
    _lambda_3[_qp] = _input_lambda_3;
    _lambda_4[_qp] = _input_lambda_4;
    _lambda_5[_qp] = _input_lambda_5;
    _lambda_6[_qp] = _input_lambda_6;
}