#include "DelayedNeutron_Decayandfission.h"
registerMooseObject("diffusion_2DApp", DelayedNeutron_Decayandfission);

InputParameters DelayedNeutron_Decayandfission::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("num", "Num of C.");
    params.addRequiredParam<Real>("keff", "keff.");
    params.addRequiredCoupledVar("flux_group1", "Flux of group1.");
    params.addRequiredCoupledVar("flux_group2", "Flux of group2.");
    params.addRequiredCoupledVar("fission", "Aux fission.");
    return params;
}

DelayedNeutron_Decayandfission::DelayedNeutron_Decayandfission(const InputParameters & parameters)
    :   Kernel(parameters),
        _num(getParam<Real>("num")),
        _keff(getParam<Real>("keff")),
        
        _lambda((_num < 4)? ((_num == 1)? (getMaterialProperty<Real>("lambda_1")) : ((_num == 2)? (getMaterialProperty<Real>("lambda_2")) : (getMaterialProperty<Real>("lambda_3")))) : ((_num == 4)? (getMaterialProperty<Real>("lambda_4")) : ((_num == 5)? (getMaterialProperty<Real>("lambda_5")) : (getMaterialProperty<Real>("lambda_6"))))),
        _beta((_num < 4)? ((_num == 1)? (getMaterialProperty<Real>("beta_1")) : ((_num == 2)? (getMaterialProperty<Real>("beta_2")) : (getMaterialProperty<Real>("beta_3")))) : ((_num == 4)? (getMaterialProperty<Real>("beta_4")) : ((_num == 5)? (getMaterialProperty<Real>("beta_5")) : (getMaterialProperty<Real>("beta_6"))))),
        _fission_cross_section_v_group1(getMaterialProperty<Real>("fission_cross_section_v_group1")),
        _fission_cross_section_v_group2(getMaterialProperty<Real>("fission_cross_section_v_group2")),
        _flux_group1(coupledValue("flux_group1")),
        _flux_group2(coupledValue("flux_group2")),
        _fission(coupledValue("fission"))
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

Real DelayedNeutron_Decayandfission::computeQpResidual()
{
    return _test[_i][_qp] * (_lambda[_qp] * _u[_qp] - _beta[_qp] * (_flux_group1[_qp] * _fission_cross_section_v_group1[_qp] + _flux_group2[_qp] * _fission_cross_section_v_group2[_qp]) / _keff);
}

Real DelayedNeutron_Decayandfission::computeQpJacobian()
{
    return _test[_i][_qp] * _lambda[_qp] * _phi[_j][_qp];
}