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

#include "GeometryController.hh"
#include "DetectorConstruction.hh"
#include "PassiveProtonBeamLine.hh"
#include "OpenBeamLine.hh"
#include "G4RunManager.hh"

// **************************************************************************************
GeometryController::GeometryController()
//---------------------------------------------------------------------------------------
{}

// **************************************************************************************
GeometryController::~GeometryController()
//---------------------------------------------------------------------------------------
{}

// **************************************************************************************
void GeometryController::SetGeometry(G4String name)
//---------------------------------------------------------------------------------------
{
    G4cout <<"Activating geometry " << name << G4endl;

    if(name == "default")
    registerGeometry(new PassiveProtonBeamLine());
    else if(name == "Openbeam")
    registerGeometry(new OpenBeamLine());
    else G4cout <<"Unknown geometry: " << name << ". Geometry not changed." << G4endl;
}
	
// **************************************************************************************
void GeometryController::registerGeometry(G4VUserDetectorConstruction *detector)
//---------------------------------------------------------------------------------------
{
  G4RunManager *runManager = G4RunManager::GetRunManager();
  runManager->SetUserInitialization(detector);
  runManager->GeometryHasBeenModified();
}

