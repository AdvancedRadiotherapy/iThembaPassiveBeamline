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


#include "RunAction.hh"
#include "EventAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "DetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4Timer.hh"
#include "RunAction.hh"
#include "RootAnalysis.hh"
#include "NozzleMaterial.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "PhantomAnalysis.hh"
#include "DetectorAnalysis.hh"
#include "G4HadronicProcessStore.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iomanip>
//****************************************************************************
RunAction::RunAction(G4String name, G4long val):
header(name), seed(val)
//----------------------------------------------------------------------------
{

}

//****************************************************************************
RunAction::~RunAction()
//----------------------------------------------------------------------------
{ 
}

//****************************************************************************
void RunAction::BeginOfRunAction(const G4Run* aRun)
//----------------------------------------------------------------------------
{ 	

  G4RunManager::GetRunManager()-> SetRandomNumberStore(true);
  G4cout << "Run " << aRun -> GetRunID() << " starts ..." << G4endl;

// Get link to RootAnalysis to open files (first run)
  RootAnalysis* analysis = RootAnalysis::getInstance();
  if (aRun->GetRunID() == 0) {analysis->openFiles(header, seed);}

  PhantomAnalysis* PA = PhantomAnalysis::GetPhantomAnalysis();
  PA->BeginOfRun();

  DetectorAnalysis* DA = DetectorAnalysis::GetDetectorAnalysis();
  DA->BeginOfRun();

}

//****************************************************************************
void RunAction::EndOfRunAction(const G4Run* aRun)
//----------------------------------------------------------------------------
{
     G4int NbOfEvents = aRun->GetNumberOfEvent();
     //G4int RunID = aRun -> GetRunID();

     PhantomAnalysis* PA = PhantomAnalysis::GetPhantomAnalysis();
     PA-> EndOfRun(NbOfEvents);

     DetectorAnalysis* DA = DetectorAnalysis::GetDetectorAnalysis();
     DA-> EndOfRun(NbOfEvents);

  // show Rndm status
     CLHEP::HepRandom::showEngineStatus();

}


