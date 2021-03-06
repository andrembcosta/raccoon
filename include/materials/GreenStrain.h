//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "ADComputeStrainBase.h"

template <ComputeStage>
class GreenStrain;

declareADValidParams(GreenStrain);

/**
 * GreenStrain defines a non-linear Green-Lagrange strain tensor
 */
template <ComputeStage compute_stage>
class GreenStrain : public ADComputeStrainBase<compute_stage>
{
public:
  static InputParameters validParams();

  GreenStrain(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  /// deformation gradient
  ADMaterialProperty(RankTwoTensor) & _F;

  usingComputeStrainBaseMembers;
};
