//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "PresetNodalBC.h"
#include "RankFourTensor.h"

// Forward Declarations
class ModeISurfingPresetBC;

template <>
InputParameters validParams<ModeISurfingPresetBC>();

class ModeISurfingPresetBC : public PresetNodalBC
{
public:
  ModeISurfingPresetBC(const InputParameters & parameters);

protected:
  /**
   * Evaluate the surfing BC at the current quadrature point and timestep.
   */
  virtual Real computeQpValue() override;

  const VariableValue & _xc;
  const VariableValue & _yc;
  const unsigned int _component;
  const Real _Gc;
  const Real _E;
  const Real _nu;
};
