#include "Delayed_NeutronSources_group1.h"
registerMooseObject("diffusion_2DApp", Delayed_NeutronSources_group1);

InputParameters Delayed_NeutronSources_group1::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("delayed_nucleus", "Delayed nucleus auxvatiable.");
    return params;
}

Delayed_NeutronSources_group1::Delayed_NeutronSources_group1(const InputParameters & parameters)
    :   Kernel(parameters),
        _delayed_nucleus(coupledValue("delayed_nucleus")),
        _kai(getMaterialProperty<Real>("kai_group1")),
        _delayed_nucleus_var(coupled("delayed_nucleus"))
{
}

Real Delayed_NeutronSources_group1::computeQpResidual()
{
    return -_test[_i][_qp] * _kai[_qp] * _delayed_nucleus[_qp];
}

Real Delayed_NeutronSources_group1::computeQpJacobian()
{
    return 0.0;
}

Real Delayed_NeutronSources_group1::computeQpOffDiagJacobian(unsigned int jvar)
{
  if(jvar == _delayed_nucleus_var)
  {
    return -_test[_i][_qp] * _kai[_qp] * _phi[_j][_qp];
  }
  return 0.0;
}