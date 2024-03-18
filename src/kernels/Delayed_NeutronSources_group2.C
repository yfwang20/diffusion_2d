#include "Delayed_NeutronSources_group2.h"
registerMooseObject("diffusion_2DApp", Delayed_NeutronSources_group2);

InputParameters Delayed_NeutronSources_group2::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("delayed_nucleus", "Delayed nucleus auxvatiable.");
    return params;
}

Delayed_NeutronSources_group2::Delayed_NeutronSources_group2(const InputParameters & parameters)
    :   Kernel(parameters),
        _delayed_nucleus(coupledValue("delayed_nucleus")),
        _kai(getMaterialProperty<Real>("kai_group2"))
{
}

Real Delayed_NeutronSources_group2::computeQpResidual()
{
    return -_test[_i][_qp] * _kai[_qp] * _delayed_nucleus[_qp];
}

Real Delayed_NeutronSources_group2::computeQpJacobian()
{
    return 0.0;
}