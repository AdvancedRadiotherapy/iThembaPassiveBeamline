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
// ====================================================================================
// PhantomAnalasis.cc
// ====================================================================================
#include "PhantomAnalysis.hh"
#include "PhantomAnalysisMessenger.hh"
#include "RootAnalysis.hh"
#include <iomanip>

#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TrackVector.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"
#include "G4EmCalculator.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4HadronicProcessStore.hh"
#include "G4Gamma.hh"
#include "G4UnitsTable.hh"

PhantomAnalysis* PhantomAnalysis::thePhantomAnalysis = 0;

// ====================================================================================
PhantomAnalysis* PhantomAnalysis::GetPhantomAnalysis()
//-------------------------------------------------------------------------------------
{
  if (thePhantomAnalysis == 0) {thePhantomAnalysis = new PhantomAnalysis();} 
  else { return thePhantomAnalysis;}

  return thePhantomAnalysis;
}

// ====================================================================================
PhantomAnalysis::PhantomAnalysis() :PhantomVerbose(0)
//-------------------------------------------------------------------------------------
{
  messenger = new PhantomAnalysisMessenger(this);

}

// ====================================================================================
PhantomAnalysis::~PhantomAnalysis()
//-------------------------------------------------------------------------------------
{
  delete messenger;
}

// ====================================================================================
void PhantomAnalysis::BeginOfEvent()
//-------------------------------------------------------------------------------------
{

}

// ====================================================================================
void PhantomAnalysis::storePhantomData(const G4Step& aStep)
//-------------------------------------------------------------------------------------
{
     RootAnalysis* analysis = RootAnalysis::getInstance();

     const G4Track* aTrack  = aStep.GetTrack();
     dx             = aStep.GetStepLength();
     dE             = aStep.GetTotalEnergyDeposit();
     particle       = aTrack->GetDefinition();
     particleName   = aTrack->GetDefinition()->GetParticleName();
     eventID        = G4RunManagerKernel::GetRunManagerKernel()->GetEventManager()->GetConstCurrentEvent()->GetEventID();
     trackID        = aTrack->GetTrackID();
     tracklength    = aTrack->GetTrackLength();
     parentID       = aTrack->GetParentID();
     stepNum        = aTrack->GetCurrentStepNumber();
     preStepVol     = aStep.GetPreStepPoint();
     endPoint    = aStep.GetPostStepPoint();
     InitialKinE    = aTrack->GetVertexKineticEnergy();
     G4ThreeVector direction = aTrack->GetMomentumDirection();       
     time = aStep.GetPreStepPoint()->GetGlobalTime() ;
     kineticEnergy =  aStep.GetPreStepPoint() -> GetKineticEnergy();

  // Storing step data (step coordinates, volume names)
     G4ThreeVector coordOfPreStep  = aStep.GetPreStepPoint()->GetPosition();
     G4ThreeVector coordOfPostStep = aStep.GetPostStepPoint()->GetPosition();
     G4String postProcessName = aStep.GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
   //G4SteppingManager*  fpSteppingManager;

  // Storing step data (step energy, momentum, scattering angle)
   //G4double energyAtPreStep = aStep.GetPreStepPoint()->GetKineticEnergy();

  G4TouchableHandle touchable = aStep.GetPreStepPoint()->GetTouchableHandle();
  G4ThreeVector localPosition = touchable->GetHistory()->GetTopTransform().TransformPoint(coordOfPostStep);

  // Get creation process 
     creatorProcessName = "---";                
     if (trackID > 1) { creatorProcessName = aStep.GetTrack()->GetCreatorProcess()->GetProcessName(); }

  // Record depth dose data
     analysis->TragetDoseDistribution(dE, localPosition);//coordOfPostStep);

}

// ====================================================================================
void PhantomAnalysis::EndOfEvent() 
//-------------------------------------------------------------------------------------
{
}

// ====================================================================================
void PhantomAnalysis::BeginOfRun() 
//-------------------------------------------------------------------------------------
{
    
}

// ====================================================================================
void PhantomAnalysis::EndOfRun(G4int NofEvent)
//-------------------------------------------------------------------------------------
{

}

//****************************************************************************
void PhantomAnalysis::TargetMaterial(G4Material* pMat, G4double PZSize)
//----------------------------------------------------------------------------
{
  material = pMat;
  PhantomLength=PZSize;
  density = material->GetDensity();
}





