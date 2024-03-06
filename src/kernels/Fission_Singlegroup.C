#include "Fission_Singlegroup.h"
registerMooseObject("diffusion_2DApp", Fission_Singlegroup);

InputParameters Fission_Singlegroup::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addParam<Real>("coefficient", 1.0, "Sign for eigenvalue problem.");
    return params;
}

Fission_Singlegroup::Fission_Singlegroup(const InputParameters & parameters)
    :   Kernel(parameters),
        _fission_cross_section_v(getMaterialProperty<Real>("fission_cross_section_v")),
        _coefficient(getParam<Real>("coefficient"))
{
}

Real Fission_Singlegroup::computeQpResidual()
{
    return _coefficient * _test[_i][_qp] * (_fission_cross_section_v[_qp] * _u[_qp]);
}

Real Fission_Singlegroup::computeQpJacobian()
{
    return _coefficient * _test[_i][_qp] * (_fission_cross_section_v[_qp] * _phi[_j][_qp]);
}