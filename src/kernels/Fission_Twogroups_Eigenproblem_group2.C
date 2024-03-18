#include "Fission_Twogroups_Eigenproblem_group2.h"
registerMooseObject("diffusion_2DApp", Fission_Twogroups_Eigenproblem_group2);

InputParameters Fission_Twogroups_Eigenproblem_group2::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addParam<Real>("coefficient", 1.0, "Sign for eigenvalue problem.");
    params.addRequiredCoupledVar("otherflux_1", "Couple other flux.");
    return params;
}

Fission_Twogroups_Eigenproblem_group2::Fission_Twogroups_Eigenproblem_group2(const InputParameters & parameters)
    :   Kernel(parameters),
        _kai(getMaterialProperty<Real>("kai_group2")),
        _fission_cross_section_v_local(getMaterialProperty<Real>("fission_cross_section_v_group2")),
        _fission_cross_section_v_other(getMaterialProperty<Real>("fission_cross_section_v_group1")),
        _otherflux(coupledValue("otherflux_1")),
        _coefficient(getParam<Real>("coefficient"))
{
}

Real Fission_Twogroups_Eigenproblem_group2::computeQpResidual()
{
    return _coefficient * _test[_i][_qp] * _kai[_qp] * (_fission_cross_section_v_local[_qp] * _u[_qp] + _fission_cross_section_v_other[_qp] * _otherflux[_qp]);
}

Real Fission_Twogroups_Eigenproblem_group2::computeQpJacobian()
{
    return _coefficient * _test[_i][_qp] * _kai[_qp] * (_fission_cross_section_v_local[_qp] * _phi[_j][_qp]);
}