//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "SideIntegralPostprocessor.h"
#include "RankTwoTensor.h"

// Forward Declarations
class PhaseFieldJIntegral;

template <>
InputParameters validParams<PhaseFieldJIntegral>();

class PhaseFieldJIntegral : public SideIntegralPostprocessor
{
public:
  PhaseFieldJIntegral(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;

  /// base name of stress
  const std::string _base_name;
  /// stress tensor
  const MaterialProperty<RankTwoTensor> & _stress;
  /// degraded eleastic energy
  const MaterialProperty<Real> & _E_elastic;
  /// number of displacement variables provided
  const unsigned int _ndisp;
  /// du_dx
  const VariableGradient & _grad_disp_0;
  /// du_dy
  const VariableGradient & _grad_disp_1;
  /// du_dz
  const VariableGradient & _grad_disp_2;
  /// direction of J integral
  const RealVectorValue _t;
};
