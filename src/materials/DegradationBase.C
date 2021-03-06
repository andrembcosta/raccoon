//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "DegradationBase.h"

defineADLegacyParams(DegradationBase);

template <ComputeStage compute_stage>
InputParameters
DegradationBase<compute_stage>::validParams()
{
  InputParameters params = ADMaterial<compute_stage>::validParams();
  params.addCoupledVar("d", "phase-field damage variable");
  params.addCoupledVar("d_relaxed", "relaxed phase-field damage variable");
  params.addParam<MaterialPropertyName>(
      "degradation_name", "g", "name of the material that holds the degradation function value");
  params.addParam<Real>("residual_degradation", 1e-6, "residual degradation");
  params.addParam<bool>("lag_degradation",
                        false,
                        "whether to use the last converged damage variable to compute "
                        "degradation (the derivative of degradation is always NOT lagged)");
  return params;
}

template <ComputeStage compute_stage>
DegradationBase<compute_stage>::DegradationBase(const InputParameters & parameters)
  : ADMaterial<compute_stage>(parameters),
    _d(adCoupledValue("d")),
    _d_old(isParamValid("d_relaxed") ? coupledValue("d_relaxed") : coupledValueOld("d")),
    _g_name(getParam<MaterialPropertyName>("degradation_name")),
    _g(declareADProperty<Real>(_g_name)),
    _dg_dd(declareADProperty<Real>(
        derivativePropertyNameFirst(_g_name, this->getVar("d", 0)->name()))),
    _eta(getParam<Real>("residual_degradation")),
    _lag(getParam<bool>("lag_degradation"))
{
}

template <ComputeStage compute_stage>
void
DegradationBase<compute_stage>::computeQpProperties()
{
  computeDegradation();
  postComputeDegradation();
}

template <ComputeStage compute_stage>
void
DegradationBase<compute_stage>::postComputeDegradation()
{
  _g[_qp] = _g[_qp] * (1.0 - _eta) + _eta;
  _dg_dd[_qp] = _dg_dd[_qp] * (1.0 - _eta);
}

adBaseClass(DegradationBase);
