//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "ADMaterial.h"
#include "DerivativeMaterialPropertyNameInterface.h"

// Forward Declarations
template <ComputeStage>
class LinearLocalDissipation;

declareADValidParams(LinearLocalDissipation);

template <ComputeStage compute_stage>
class LinearLocalDissipation : public ADMaterial<compute_stage>,
                               public DerivativeMaterialPropertyNameInterface
{
public:
  static InputParameters validParams();

  LinearLocalDissipation(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  /// coupled damage variable
  const ADVariableValue & _d;

  /// name of local dissipation
  const MaterialPropertyName _w_name;

  /// local dissipation
  ADMaterialProperty(Real) & _w;

  /// local dissipation derivative
  ADMaterialProperty(Real) & _dw_dd;

  usingMaterialMembers;
};
