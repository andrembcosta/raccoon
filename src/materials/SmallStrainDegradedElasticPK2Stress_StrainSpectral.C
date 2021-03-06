//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "SmallStrainDegradedElasticPK2Stress_StrainSpectral.h"

registerADMooseObject("raccoonApp", SmallStrainDegradedElasticPK2Stress_StrainSpectral);

defineADLegacyParams(SmallStrainDegradedElasticPK2Stress_StrainSpectral);

template <ComputeStage compute_stage>
InputParameters
SmallStrainDegradedElasticPK2Stress_StrainSpectral<compute_stage>::validParams()
{
  InputParameters params = ADDegradedStressBase<compute_stage>::validParams();
  params.addClassDescription("Compute degraded stress following small deformation elasticity "
                             "with a spectra-based active/inactive split");
  return params;
}

template <ComputeStage compute_stage>
SmallStrainDegradedElasticPK2Stress_StrainSpectral<
    compute_stage>::SmallStrainDegradedElasticPK2Stress_StrainSpectral(const InputParameters & parameters)
  : ADDegradedStressBase<compute_stage>(parameters)
{
}

template <ComputeStage compute_stage>
void
SmallStrainDegradedElasticPK2Stress_StrainSpectral<compute_stage>::computeQpStress()
{
  // Isotropic elasticity is assumed and should be enforced
  const Real lambda = _elasticity_tensor[_qp](0, 0, 1, 1);
  const Real mu = _elasticity_tensor[_qp](0, 1, 0, 1);

  // Identity tensor
  ADRankTwoTensor I2(RankTwoTensorType<compute_stage>::type::initIdentity);

  // spectral decomposition
  ADRankTwoTensor E = _mechanical_strain[_qp];
  ADRankTwoTensor Q;
  std::vector<ADReal> d;
  E.symmetricEigenvaluesEigenvectors(d, Q);

  // positive part
  D_pos.fillFromInputVector(Macaulay(d));
  ADRankTwoTensor E_pos = Q * D_pos * Q.transpose();

  ADReal trE = E.trace();
  ADReal trE_pos = Macaulay(trE);

  // PK1 stress
  ADRankTwoTensor S0 = lambda * trE * I2 + 2.0 * mu * E;
  ADRankTwoTensor S_pos = lambda * trE_pos * I2 + 2.0 * mu * E_pos;
  _stress[_qp] = S0 - (1.0 - _g[_qp]) * S_pos;

  // elastic driving energy
  _E_el_active[_qp] = 0.5 * lambda * trE_pos * trE_pos + mu * E_pos.doubleContraction(E_pos);
}
