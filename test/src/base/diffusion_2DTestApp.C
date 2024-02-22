//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "diffusion_2DTestApp.h"
#include "diffusion_2DApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
diffusion_2DTestApp::validParams()
{
  InputParameters params = diffusion_2DApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

diffusion_2DTestApp::diffusion_2DTestApp(InputParameters parameters) : MooseApp(parameters)
{
  diffusion_2DTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

diffusion_2DTestApp::~diffusion_2DTestApp() {}

void
diffusion_2DTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  diffusion_2DApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"diffusion_2DTestApp"});
    Registry::registerActionsTo(af, {"diffusion_2DTestApp"});
  }
}

void
diffusion_2DTestApp::registerApps()
{
  registerApp(diffusion_2DApp);
  registerApp(diffusion_2DTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
diffusion_2DTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  diffusion_2DTestApp::registerAll(f, af, s);
}
extern "C" void
diffusion_2DTestApp__registerApps()
{
  diffusion_2DTestApp::registerApps();
}
