    // **************************************************************************************
    //
    // HADRONTHERAPY:  a Geant4-based application for proton/ion-therapy studies
    // _________________________________________________________________________
    //
    // This is the FULL version of the Hadrontherapy application.
    // It is based on the Geant4 toolkit classes and released under the GPL3 license.
    //
    // Its basic version is released and maintained inside the Geant4 code
    // as Advanced Example.
    //
	// To compile and run Hadrontherapy you only require the installation of Geant4 and,
	// if you wish, the ROOT ananlysis program.
    //
    // For more information see the documentation at http://sites.google.com/site/hadrontherapy/
    // or contact cirrone@lns.infn.it
    //
    // **************************************************************************************


#include "StepMaxMessenger.hh"
#include "StepMax.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

/////////////////////////////////////////////////////////////////////////////
StepMaxMessenger::StepMaxMessenger(StepMax* stepM)
:stepMax(stepM)
{ 
  StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/Step/waterPhantomStepMax",this);
  StepMaxCmd->SetGuidance("Set max allowed step length");
  StepMaxCmd->SetParameterName("mxStep",false);
  StepMaxCmd->SetRange("mxStep>0.");
  StepMaxCmd->SetUnitCategory("Length");


  StepWorldMaxCmd = new G4UIcmdWithADoubleAndUnit("/Step/detectorStepMax",this);
  StepWorldMaxCmd->SetGuidance("Set max allowed step length");
  StepWorldMaxCmd->SetParameterName("mxStep",false);
  StepWorldMaxCmd->SetRange("mxStep>0.");
  StepWorldMaxCmd->SetUnitCategory("Length");
}

/////////////////////////////////////////////////////////////////////////////
StepMaxMessenger::~StepMaxMessenger()
{
  delete StepMaxCmd;
  delete StepWorldMaxCmd;
}

/////////////////////////////////////////////////////////////////////////////
void StepMaxMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == StepMaxCmd)
    { stepMax->SetMaxStep(StepMaxCmd->GetNewDoubleValue(newValue));}

  if (command == StepWorldMaxCmd)
    { stepMax->SetMaxWorldStep(StepWorldMaxCmd->GetNewDoubleValue(newValue));}
}

