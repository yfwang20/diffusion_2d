#include "DelayedNeutron_Decay.h"
registerMooseObject("diffusion_2DApp", DelayedNeutron_Decay);

InputParameters DelayedNeutron_Decay::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("num", "Num of C.");
    return params;
}

DelayedNeutron_Decay::DelayedNeutron_Decay(const InputParameters & parameters)
    :   Kernel(parameters),
        _num(getParam<Real>("num")),
        _lambda((_num < 4)? ((_num == 1)? (getMaterialProperty<Real>("lambda_1")) : ((_num == 2)? (getMaterialProperty<Real>("lambda_2")) : (getMaterialProperty<Real>("lambda_3")))) : ((_num == 4)? (getMaterialProperty<Real>("lambda_4")) : ((_num == 5)? (getMaterialProperty<Real>("lambda_5")) : (getMaterialProperty<Real>("lambda_6")))))
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

Real DelayedNeutron_Decay::computeQpResidual()
{
    return _test[_i][_qp] * _lambda[_qp] * _u[_qp];
}

Real DelayedNeutron_Decay::computeQpJacobian()
{
    return _test[_i][_qp] * _lambda[_qp] * _phi[_j][_qp];
}