#include "diffusion_2DApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
diffusion_2DApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

diffusion_2DApp::diffusion_2DApp(InputParameters parameters) : MooseApp(parameters)
{
  diffusion_2DApp::registerAll(_factory, _action_factory, _syntax);
}

diffusion_2DApp::~diffusion_2DApp() {}

void 
diffusion_2DApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<diffusion_2DApp>(f, af, s);
  Registry::registerObjectsTo(f, {"diffusion_2DApp"});
  Registry::registerActionsTo(af, {"diffusion_2DApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
diffusion_2DApp::registerApps()
{
  registerApp(diffusion_2DApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
diffusion_2DApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  diffusion_2DApp::registerAll(f, af, s);
}
extern "C" void
diffusion_2DApp__registerApps()
{
  diffusion_2DApp::registerApps();
}
