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
// SteppingAction.hh;
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy

#include "G4SteppingManager.hh"
#include "G4TrackVector.hh"
#include "SteppingAction.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4UserEventAction.hh"
#include "G4TouchableHistory.hh"
#include "RootAnalysis.hh"
#include "RunAction.hh"
#include "PhantomAnalysis.hh"
#include "DetectorAnalysis.hh"
#include <stdio.h>
#include <math.h>
#include "G4HadronicProcess.hh"

// **************************************************************************************
SteppingAction::SteppingAction( RunAction *run)
// --------------------------------------------------------------------------------------
{
  runAction = run;

  channelEventID=0.;
  gammaventID=0.;
  alphaEventID=0.;
  neutronEventID=0.;
  He3EventID=0.;
  deuteronEventID=0.;
  tritonEventID=0.;

   ED=0.;
}

// **************************************************************************************
SteppingAction::~SteppingAction()
// --------------------------------------------------------------------------------------
{
}

// **************************************************************************************
void SteppingAction::UserSteppingAction(const G4Step* aStep)
// --------------------------------------------------------------------------------------
{ 
  // get pointer for RootAnalysis
   //RootAnalysis* analysis = RootAnalysis::getInstance();

  // get pointer for PhantomAnalysis
     PhantomAnalysis* phantomAnalysis = PhantomAnalysis::GetPhantomAnalysis();

  // get pointer for DetectorAnalysis
     DetectorAnalysis* detAnalysis = DetectorAnalysis::GetDetectorAnalysis();

  // Only record events inside the Phantom volume
     if ((aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "phantomPhys")
         &&(aStep -> GetPostStepPoint() -> GetProcessDefinedStep() != NULL))
         {phantomAnalysis->storePhantomData(*aStep);}

  // Only record events inside the Detector volume
     if ((aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "DetectorPhys")
         &&(aStep -> GetPostStepPoint() -> GetProcessDefinedStep() != NULL))
         {detAnalysis->storeDetectorData(*aStep);}


} 

// **************************************************************************************


				
