// ====================================================================================
//   PhantomAnalysisMessenger.cc
// ====================================================================================

#include "PhantomAnalysisMessenger.hh"
#include "PhantomAnalysis.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"


// ====================================================================================
PhantomAnalysisMessenger::PhantomAnalysisMessenger(PhantomAnalysis* myPha):myPhantom (myPha)
//-------------------------------------------------------------------------------------
{
  dir = new G4UIdirectory("/analysis/");
  dir-> SetGuidance("Analysis");

}

// ====================================================================================
PhantomAnalysisMessenger::~PhantomAnalysisMessenger()
//-------------------------------------------------------------------------------------
{

  delete dir;

}

// ====================================================================================
void PhantomAnalysisMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
//-------------------------------------------------------------------------------------
{

}

