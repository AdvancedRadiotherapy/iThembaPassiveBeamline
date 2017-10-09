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


#include "GeometryMessenger.hh"
#include "GeometryController.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

// *******************************************************************************************
GeometryMessenger::GeometryMessenger(GeometryController* controller)
  :hadrontherapyGeometryController(controller)
// -------------------------------------------------------------------------------------------

{
  changeTheGeometryDir = new G4UIdirectory("/geometrySetup/");
  changeTheGeometryDir -> SetGuidance("Geometry setup");

  changeTheGeometryCmd = new G4UIcmdWithAString("/geometrySetup/selectGeometry",this);
  changeTheGeometryCmd -> SetGuidance("Select the geometry you wish to use");
  changeTheGeometryCmd -> SetParameterName("Geometry",false);
  changeTheGeometryCmd -> AvailableForStates(G4State_PreInit); 
}

// *******************************************************************************************
GeometryMessenger::~GeometryMessenger()
// -------------------------------------------------------------------------------------------
{ 
  delete changeTheGeometryDir;
  delete changeTheGeometryCmd;
}

// *******************************************************************************************
void GeometryMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
// -------------------------------------------------------------------------------------------
{ 
  if( command == changeTheGeometryCmd )
    { hadrontherapyGeometryController -> SetGeometry (newValue);}
}
