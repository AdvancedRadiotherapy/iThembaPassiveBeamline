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

#include "EventActionMessenger.hh"

#include "EventAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"

/////////////////////////////////////////////////////////////////////////////
EventActionMessenger::EventActionMessenger(EventAction* EvAct)
:eventAction(EvAct)
{
  eventDir = new G4UIdirectory("/event/");
  eventDir->SetGuidance("Permits controls on simulation events");
 
  DrawCmd = new G4UIcmdWithAString("/event/drawTracks",this);
  DrawCmd->SetGuidance("Draw the tracks in the event");
  DrawCmd->SetGuidance("  Choice : none,charged, all, neutral");
  DrawCmd->SetParameterName("choice",true);
  DrawCmd->SetDefaultValue("all");
  DrawCmd->SetCandidates("none charged all neutral");
  DrawCmd->AvailableForStates(G4State_Idle);
  
  PrintCmd = new G4UIcmdWithAnInteger("/event/printEventNumber",this);
  PrintCmd->SetGuidance("Print the event number of modulo n");
  PrintCmd->SetParameterName("EventNb",false);
  PrintCmd->SetRange("EventNb>0");
  PrintCmd->AvailableForStates(G4State_Idle);      
}

/////////////////////////////////////////////////////////////////////////////
EventActionMessenger::~EventActionMessenger()
{
  delete DrawCmd;
  delete PrintCmd;
  delete eventDir;         
}

/////////////////////////////////////////////////////////////////////////////
void EventActionMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{ 
  if(command == DrawCmd)
    {eventAction->SetDrawFlag(newValue);}
    
  if(command == PrintCmd)
    {eventAction->SetPrintModulo(PrintCmd->GetNewIntValue(newValue));}           
 }
