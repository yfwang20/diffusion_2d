#include "Eigenkernel_Fission_Twogroups_group1.h"
registerMooseObject("diffusion_2DApp", Eigenkernel_Fission_Twogroups_group1);

InputParameters Eigenkernel_Fission_Twogroups_group1::validParams()
{
    InputParameters params = EigenKernel::validParams();
    params.addRequiredCoupledVar("otherflux_1", "Couple other flux.");
    return params;
}

Eigenkernel_Fission_Twogroups_group1::Eigenkernel_Fission_Twogroups_group1(const InputParameters & parameters)
    :   EigenKernel(parameters),
        _kai(getMaterialProperty<Real>("kai_group1")),
        _fission_cross_section_v_local(getMaterialProperty<Real>("fission_cross_section_v_group1")),
        _fission_cross_section_v_other(getMaterialProperty<Real>("fission_cross_section_v_group2")),
        _otherflux(coupledValue("otherflux_1"))
{
}

Real Eigenkernel_Fission_Twogroups_group1::computeQpResidual()
{
    return -_test[_i][_qp] * _kai[_qp] * (_fission_cross_section_v_local[_qp] * _u[_qp] + _fission_cross_section_v_other[_qp] * _otherflux[_qp]);
}

// Real Eigenkernel_Fission_Twogroups_group1::computeQpJacobian()
// {
//     return _coefficient * _test[_i][_qp] * _kai[_qp] * (_fission_cross_section_v_local[_qp] * _phi[_j][_qp]);
// }