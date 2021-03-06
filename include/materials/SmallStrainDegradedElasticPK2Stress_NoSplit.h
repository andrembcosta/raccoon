//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "ADDegradedStressBase.h"

template <ComputeStage>
class SmallStrainDegradedElasticPK2Stress_NoSplit;

declareADValidParams(SmallStrainDegradedElasticPK2Stress_NoSplit);

template <ComputeStage compute_stage>
class SmallStrainDegradedElasticPK2Stress_NoSplit : public ADDegradedStressBase<compute_stage>
{
public:
  static InputParameters validParams();

  SmallStrainDegradedElasticPK2Stress_NoSplit(const InputParameters & parameters);

protected:
  virtual void computeQpStress() override;

  usingDegradedStressBaseMembers
};
