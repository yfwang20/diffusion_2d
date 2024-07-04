#include "Fission_Twogroups_Transientproblem_group2.h"
registerMooseObject("diffusion_2DApp", Fission_Twogroups_Transientproblem_group2);

InputParameters Fission_Twogroups_Transientproblem_group2::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addParam<Real>("coefficient", 1.0, "Sign for eigenvalue problem.");
    params.addRequiredParam<Real>("keff", "keff form eigenproblem.");
    params.addRequiredCoupledVar("otherflux_1", "Couple other flux.");
    return params;
}

Fission_Twogroups_Transientproblem_group2::Fission_Twogroups_Transientproblem_group2(const InputParameters & parameters)
    :   Kernel(parameters),
        _beta(getMaterialProperty<Real>("beta")),
        _kai(getMaterialProperty<Real>("kai_group2")),
        _fission_cross_section_v_local(getMaterialProperty<Real>("fission_cross_section_v_group2")),
        _fission_cross_section_v_other(getMaterialProperty<Real>("fission_cross_section_v_group1")),
        _otherflux(coupledValue("otherflux_1")),
        _keff(getParam<Real>("keff")),
        _coefficient(getParam<Real>("coefficient")),
        _otherflux_var(coupled("otherflux_1"))
{
}

Real Fission_Twogroups_Transientproblem_group2::computeQpResidual()
{
    return _coefficient * _test[_i][_qp] * (1 - _beta[_qp]) * _kai[_qp] * (_fission_cross_section_v_local[_qp] * _u[_qp] + _fission_cross_section_v_other[_qp] * _otherflux[_qp]) / _keff;
}

Real Fission_Twogroups_Transientproblem_group2::computeQpJacobian()
{
    return _coefficient * _test[_i][_qp] * (1 - _beta[_qp]) * _kai[_qp] * (_fission_cross_section_v_local[_qp] * _phi[_j][_qp]) / _keff;
}

Real Fission_Twogroups_Transientproblem_group2::computeQpOffDiagJacobian(unsigned int jvar)
{   
    if(jvar == _otherflux_var)
    {
        return _coefficient * _test[_i][_qp] * (1 - _beta[_qp]) * _kai[_qp] * 
        (_fission_cross_section_v_other[_qp] * _phi[_j][_qp]) / _keff;
    }
    return 0.0;
}