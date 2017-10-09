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
// DetectorAnalasis.cc
// ====================================================================================
#include "DetectorAnalysis.hh"
#include "RootAnalysis.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"


DetectorAnalysis* DetectorAnalysis::theDetectorAnalysis = 0;

// ====================================================================================
DetectorAnalysis* DetectorAnalysis::GetDetectorAnalysis()
//-------------------------------------------------------------------------------------
{
  if (theDetectorAnalysis == 0) {theDetectorAnalysis = new DetectorAnalysis();} 
  else { return theDetectorAnalysis;}

  return theDetectorAnalysis;
}

// ====================================================================================
DetectorAnalysis::DetectorAnalysis():DetectorVerbose(0)
//-------------------------------------------------------------------------------------
{

}

// ====================================================================================
DetectorAnalysis::~DetectorAnalysis()
//-------------------------------------------------------------------------------------
{

}

// ====================================================================================
void DetectorAnalysis::BeginOfEvent()
//-------------------------------------------------------------------------------------
{

}

// ====================================================================================
void DetectorAnalysis::storeDetectorData(const G4Step& aStep)
//-------------------------------------------------------------------------------------
{
  //RootAnalysis* analysis = RootAnalysis::getInstance();

     const G4Track* aTrack  = aStep.GetTrack();
     energyDeposit  = aStep.GetTotalEnergyDeposit();
     particle       = aTrack->GetDefinition();
     particleName   = aTrack->GetDefinition()->GetParticleName();
     eventID        = G4RunManagerKernel::GetRunManagerKernel()->GetEventManager()->GetConstCurrentEvent()->GetEventID();
     trackID        = aTrack->GetTrackID();
     tracklength    = aTrack->GetTrackLength();
     parentID       = aTrack->GetParentID();
     stepNum        = aTrack->GetCurrentStepNumber();
     preStepPoint   = aStep.GetPreStepPoint();
     postStepPoint  = aStep.GetPostStepPoint();
     InitialKinE    = aTrack->GetVertexKineticEnergy();
     kineticEnergy  =  aStep.GetPreStepPoint() -> GetKineticEnergy();

  // Storing step data (step coordinates, volume names)
     G4ThreeVector coordOfPreStep  = aStep.GetPreStepPoint()->GetPosition();
     G4ThreeVector coordOfPostStep = aStep.GetPostStepPoint()->GetPosition();
     G4String postProcessName = aStep.GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
     G4String createProcessVolume = aTrack->GetLogicalVolumeAtVertex()->GetName(); 

  // Storing step data (step energy, momentum, scattering angle)
   //G4double energyAtPreStep = aStep.GetPreStepPoint()->GetKineticEnergy();

  // Get creation process 
     creatorProcessName = "---";                
     if (trackID > 1) { creatorProcessName = aStep.GetTrack()->GetCreatorProcess()->GetProcessName(); }

}
// ====================================================================================
void DetectorAnalysis::EndOfEvent() 
//-------------------------------------------------------------------------------------
{

}

// ====================================================================================
void DetectorAnalysis::BeginOfRun() 
//-------------------------------------------------------------------------------------
{
 
}

// ====================================================================================
void DetectorAnalysis::EndOfRun(G4int NofEvent) 
//-------------------------------------------------------------------------------------
{
  
}

// ====================================================================================
void DetectorAnalysis::print() 
//-------------------------------------------------------------------------------------
{
  
}
//-------------------------------------------------------------------------------------





