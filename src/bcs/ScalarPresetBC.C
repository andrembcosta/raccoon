//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ScalarPresetBC.h"

registerMooseObject("raccoonApp", ScalarPresetBC);

template <>
InputParameters
validParams<ScalarPresetBC>()
{
  InputParameters params = validParams<PresetNodalBC>();
  params.addRequiredCoupledVar("scalar_var", "scalar variable");
  return params;
}

ScalarPresetBC::ScalarPresetBC(const InputParameters & parameters)
  : PresetNodalBC(parameters), _scalar_val(coupledScalarValue("scalar_var"))
{
}

Real
ScalarPresetBC::computeQpValue()
{
  return _scalar_val[0];
}
