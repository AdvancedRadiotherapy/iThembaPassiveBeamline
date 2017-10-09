// **************************************************************************************
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


#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

// **************************************************************************************
PhysicsListMessenger::PhysicsListMessenger(PhysicsList* pPhys):pPhysicsList(pPhys)
//---------------------------------------------------------------------------------------
{
  physDir = new G4UIdirectory("/Physics/");
  physDir->SetGuidance("Commands to activate physics models and set cuts");
   
  gammaCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setGCut",this);  
  gammaCutCmd->SetGuidance("Set gamma cut.");
  gammaCutCmd->SetParameterName("Gcut",false);
  gammaCutCmd->SetUnitCategory("Length");
  gammaCutCmd->SetRange("Gcut>0.0");
  gammaCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  electCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setECut",this);  
  electCutCmd->SetGuidance("Set electron cut.");
  electCutCmd->SetParameterName("Ecut",false);
  electCutCmd->SetUnitCategory("Length");
  electCutCmd->SetRange("Ecut>0.0");
  electCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  protoCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setPCut",this);  
  protoCutCmd->SetGuidance("Set positron cut.");
  protoCutCmd->SetParameterName("Pcut",false);
  protoCutCmd->SetUnitCategory("Length");
  protoCutCmd->SetRange("Pcut>0.0");
  protoCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  allCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setCuts",this);  
  allCutCmd->SetGuidance("Set cut for all.");
  allCutCmd->SetParameterName("cut",false);
  allCutCmd->SetUnitCategory("Length");
  allCutCmd->SetRange("cut>0.0");
  allCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  allDetectorCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setDetectorCuts",this);  
  allDetectorCmd->SetGuidance("Set cut for all. into Detector");
  allDetectorCmd->SetParameterName("cut",false);
  allDetectorCmd->SetUnitCategory("Length");
  allDetectorCmd->SetRange("cut>0.0");
  allDetectorCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  allTragetCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setTargetCuts",this);  
  allTragetCmd->SetGuidance("Set cut for all. into Target");
  allTragetCmd->SetParameterName("cut",false);
  allTragetCmd->SetUnitCategory("Length");
  allTragetCmd->SetRange("cut>0.0");
  allTragetCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  pListCmd = new G4UIcmdWithAString("/Physics/addPhysics",this);  
  pListCmd->SetGuidance("Add physics list.");
  pListCmd->SetParameterName("PList",false);
  pListCmd->AvailableForStates(G4State_PreInit, G4State_Idle);  
}

// **************************************************************************************
PhysicsListMessenger::~PhysicsListMessenger()
//---------------------------------------------------------------------------------------
{
  delete gammaCutCmd;
  delete electCutCmd;
  delete protoCutCmd;
  delete allCutCmd;
  delete allDetectorCmd;
  delete allTragetCmd;
  delete pListCmd;
  delete physDir;    
}

// **************************************************************************************
void PhysicsListMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
//---------------------------------------------------------------------------------------
{       
  if( command == gammaCutCmd )
    { pPhysicsList->SetCutForGamma(gammaCutCmd->GetNewDoubleValue(newValue));}
     
  else if( command == electCutCmd )
    { pPhysicsList->SetCutForElectron(electCutCmd->GetNewDoubleValue(newValue));}
     
  else if( command == protoCutCmd )
    { pPhysicsList->SetCutForPositron(protoCutCmd->GetNewDoubleValue(newValue));}

  else if( command == allCutCmd )
    {
      G4double cut = allCutCmd->GetNewDoubleValue(newValue);
      pPhysicsList->SetCutForGamma(cut);
      pPhysicsList->SetCutForElectron(cut);
      pPhysicsList->SetCutForPositron(cut);
      pPhysicsList->SetCutForProton(cut);
    } 
  else if( command == allDetectorCmd)
    {
      G4double cut = allDetectorCmd -> GetNewDoubleValue(newValue);
      pPhysicsList -> SetDetectorCut(cut);
    }

  else if( command == allTragetCmd)
    {
      G4double cut = allTragetCmd -> GetNewDoubleValue(newValue);
      pPhysicsList -> SetTargetCut(cut);
    }

  else if( command == pListCmd )
    { pPhysicsList->AddPhysicsList(newValue);}

}
// **************************************************************************************
