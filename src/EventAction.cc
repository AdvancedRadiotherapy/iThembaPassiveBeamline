//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: EventAction.cc
//
//
// -------------------------------------------------------------------

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4VVisManager.hh"

#include "EventAction.hh"
#include "DetectorHit.hh"
#include "DetectorConstruction.hh"
#include "EventActionMessenger.hh"
#include "RunAction.hh"
#include "PhantomAnalysis.hh"
#include "DetectorAnalysis.hh"

#include "RootAnalysis.hh"
#include "Matrix.hh"
#include "Randomize.hh"


// **************************************************************************************
EventAction::EventAction():drawFlag("all" ), printModulo(1000),
pointerEventMessenger(0)
//---------------------------------------------------------------------------------------
{ 
  hitsCollectionID = -1;
  pointerEventMessenger = new EventActionMessenger(this);

}

// **************************************************************************************
EventAction::~EventAction()
//---------------------------------------------------------------------------------------
{
  delete pointerEventMessenger;
}

// **************************************************************************************
void EventAction::BeginOfEventAction(const G4Event* evt)
//---------------------------------------------------------------------------------------
{ 

   evtNb = evt -> GetEventID();
   if (evtNb%printModulo == 1000) { G4cout << "### Event " << evtNb << " start." << G4endl; }

 // Detector Analysis
    DetectorAnalysis* DA = DetectorAnalysis::GetDetectorAnalysis();
    DA -> BeginOfEvent();

    G4SDManager* pSDManager = G4SDManager::GetSDMpointer();
    if(hitsCollectionID == -1)
    hitsCollectionID = pSDManager -> GetCollectionID("DetectorHitsCollection");

    TotalEnergyDepossit = 0.0;

 // Phantom Analysis
    PhantomAnalysis* PA = PhantomAnalysis::GetPhantomAnalysis();
    PA -> BeginOfEvent();


}

// **************************************************************************************
void EventAction::EndOfEventAction(const G4Event* evt)
//---------------------------------------------------------------------------------------
{ 
  //G4int evtNb = evt -> GetEventID();

    if(hitsCollectionID < 0)
    return;

    G4HCofThisEvent* HCE = evt -> GetHCofThisEvent();

  //RootAnalysis* analysis = RootAnalysis::getInstance();
    Matrix* matrix = Matrix::GetInstance();

  // clear list of hitted voxel	
     if (matrix) matrix -> ClearHitTrack(); 

  // voxel and associated energy deposit in the detector at the end of the event
     if(HCE)
     {
      DetectorHitsCollection* CHC = (DetectorHitsCollection*)(HCE -> GetHC(hitsCollectionID));
      if(CHC)
	{
	      G4int HitCount = CHC -> entries();
	      for (G4int h = 0; h < HitCount; h++)
		{
		  G4int i = ((*CHC)[h]) -> GetXID();
		  G4int j = ((*CHC)[h]) -> GetYID();
		  G4int k = ((*CHC)[h]) -> GetZID();
		  G4double energyDeposit = ((*CHC)[h]) -> GetEdep();
                  TotalEnergyDepossit +=((*CHC)[h]) -> GetEdep();
		  if(matrix) matrix -> Fill(i, j, k, energyDeposit);

		} 
	 }
      }

  // Phantom Analysis event
     PhantomAnalysis* PA = PhantomAnalysis::GetPhantomAnalysis();
     PA-> EndOfEvent();

  // Detector Analysis event
     DetectorAnalysis* DA   = DetectorAnalysis::GetDetectorAnalysis();
     DA  -> EndOfEvent();

}

// **************************************************************************************
