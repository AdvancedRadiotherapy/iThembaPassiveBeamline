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
// $Id: DetectorSD.hh; 
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy

#ifndef DetectorSD_h
#define DetectorSD_h 1

#include "G4VSensitiveDetector.hh"
#include "DetectorHit.hh"
#include "EventAction.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class DetectorSD : public G4VSensitiveDetector

{
public:
      DetectorSD(G4String name, EventAction*);
     ~DetectorSD();

      std::ofstream ofs;
      void Initialize(G4HCofThisEvent*);
 
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);
      void EnergyDepositedPerEvent(const G4Step*, G4TouchableHistory*);

private:
     DetectorHitsCollection *HitsCollection;
     G4String sensitiveDetectorName;	
     EventAction* eventAct;
     G4String postProcessName; 

     G4int parentID;
     G4StepPoint* preStepPoint;
     G4StepPoint* postStepPoint;
     G4ParticleDefinition *particleDef;
     G4String particleName;
     G4int stepNum;
     G4double energyAtPreStep;
     G4double energyAtPosStep;
     G4ThreeVector coordOfPreStep;
     G4ThreeVector coordOfPostStep;
     G4String creatorProcessName;
     G4double InitialKinE;
     G4int trackID;
     G4Track * theTrack;
     G4int verbose;
     G4int PGEvent;
     G4int neutronEvent;
 
};
#endif


