#include "DelayedNeutron_Fission.h"
registerMooseObject("diffusion_2DApp", DelayedNeutron_Fission);

InputParameters DelayedNeutron_Fission::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("num", "Num of C.");
    params.addParam<Real>("coefficient", 1.0, "Sign for eigenvalue problem.");
    params.addRequiredCoupledVar("flux_group1", "Flux of group1.");
    params.addRequiredCoupledVar("flux_group2", "Flux of group2.");
    return params;
}

DelayedNeutron_Fission::DelayedNeutron_Fission(const InputParameters & parameters)
    :   Kernel(parameters),
        _num(getParam<Real>("num")),
        _coefficient(getParam<Real>("coefficient")),
        _beta((_num < 4)? ((_num == 1)? (getMaterialProperty<Real>("beta_1")) : ((_num == 2)? (getMaterialProperty<Real>("beta_2")) : (getMaterialProperty<Real>("beta_3")))) : ((_num == 4)? (getMaterialProperty<Real>("beta_4")) : ((_num == 5)? (getMaterialProperty<Real>("beta_5")) : (getMaterialProperty<Real>("beta_6"))))),
        _fission_cross_section_v_group1(getMaterialProperty<Real>("fission_cross_section_v_group1")),
        _fission_cross_section_v_group2(getMaterialProperty<Real>("fission_cross_section_v_group2")),
        _flux_group1(coupledValue("flux_group1")),
        _flux_group2(coupledValue("flux_group2"))
{
    // if(_num == 1)
    // {
    //     _beta = getMaterialProperty<Real>("beta_1");
    //     _lambda = getMaterialProperty<Real>("lambda_1");
    // }
    // else if(_num == 2)
    // {
    //     _beta = getMaterialProperty<Real>("beta_2");
    //     _lambda = getMaterialProperty<Real>("lambda_2");
    // }
    // else if(_num == 3)
    // {
    //     _beta = getMaterialProperty<Real>("beta_3");
    //     _lambda = getMaterialProperty<Real>("lambda_3");
    // }
    // else if(_num == 4)
    // {
    //     _beta = getMaterialProperty<Real>("beta_4");
    //     _lambda = getMaterialProperty<Real>("lambda_4");
    // }
    // else if(_num == 5)
    // {
    //     _beta = getMaterialProperty<Real>("beta_5");
    //     _lambda = getMaterialProperty<Real>("lambda_5");
    // }
    // else if(_num == 6)
    // {
    //     _beta = getMaterialProperty<Real>("beta_6");
    //     _lambda = getMaterialProperty<Real>("lambda_6");
    // }
}

Real DelayedNeutron_Fission::computeQpResidual()
{
    return _coefficient * _test[_i][_qp] * _beta[_qp] * (_fission_cross_section_v_group1[_qp] * _flux_group1[_qp] + _fission_cross_section_v_group2[_qp] * _flux_group2[_qp]);
}

Real DelayedNeutron_Fission::computeQpJacobian()
{
    return 0.0;
}