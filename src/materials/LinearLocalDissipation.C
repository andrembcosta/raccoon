//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "LinearLocalDissipation.h"

registerADMooseObject("raccoonApp", LinearLocalDissipation);

defineADLegacyParams(LinearLocalDissipation);

template <ComputeStage compute_stage>
InputParameters
LinearLocalDissipation<compute_stage>::validParams()
{
  InputParameters params = ADMaterial<compute_stage>::validParams();
  params.addClassDescription("computes the local dissipation function of the linear form, $d$");
  params.addRequiredCoupledVar("d", "phase-field damage variable");
  params.addParam<MaterialPropertyName>(
      "local_dissipation_name", "w", "name of the material that holds the local dissipation");
  return params;
}

template <ComputeStage compute_stage>
LinearLocalDissipation<compute_stage>::LinearLocalDissipation(const InputParameters & parameters)
  : ADMaterial<compute_stage>(parameters),
    _d(adCoupledValue("d")),
    _w_name(getParam<MaterialPropertyName>("local_dissipation_name")),
    _w(declareADProperty<Real>(_w_name)),
    _dw_dd(
        declareADProperty<Real>(derivativePropertyNameFirst(_w_name, this->getVar("d", 0)->name())))
{
}

template <ComputeStage compute_stage>
void
LinearLocalDissipation<compute_stage>::computeQpProperties()
{
  ADReal d = _d[_qp];

  _w[_qp] = d;
  _dw_dd[_qp] = 1.0;
}
