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
// ====================================================================
//   DetectorAnalysis.hh
//
// ====================================================================
#ifndef OPENDETECTOR_ANALYSIS_H
#define OPENDETECTOR_ANALYSIS_H 

#include <vector>
#include <map>
#include <iomanip>
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4UserRunAction.hh"
#include "G4Step.hh"



class G4Track;
class G4Step;



class DetectorAnalysis {


public:
  ~DetectorAnalysis();

  static DetectorAnalysis* GetDetectorAnalysis();
  void storeDetectorData(const G4Step& aStep);

  
  void BeginOfEvent();
  void BeginOfRun();
  void EndOfEvent();
  void EndOfRun(G4int NofEvent);


private:
     DetectorAnalysis();
     static DetectorAnalysis* theDetectorAnalysis;
     void SumEnergy(G4double de){NaIEngDepositPerEvent += de;};
     void SumparfromtargetEnergy(G4double de){NaIparEngfromtargetDepositPerEvent += de;};
     void SumGamEnergy(G4double de){NaIGamEngDepositPerEvent += de;};
     void SumPromptGamEnergy(G4double de){NaIPromptGamEngDepositPerEvent += de;};
     void SumPGEnergy(G4double de){NaIPGEngDepositPerEvent += de;};
     void SumNeutronEnergy(G4double de){NaINeutronEngDepositPerEvent += de;};
     void SumNeutronfromtarEnergy(G4double de){NaINeutronEngfromtarDepositPerEvent += de;};

     void print();

  
     G4double NaIEngDepositPerEvent;
     G4double NaIparEngfromtargetDepositPerEvent;
     G4double NaIGamEngDepositPerEvent;
     G4double NaIPromptGamEngDepositPerEvent;
     G4double NaIPGEngDepositPerEvent;
     G4double NaINeutronEngDepositPerEvent;
     G4double NaINeutronEngfromtarDepositPerEvent;

     G4ParticleDefinition* particle;
     G4String particleName;
     G4int eventID;
     G4int trackID;
     G4double tracklength;
     G4int parentID;
     G4int stepNum;
     G4double energyDeposit;
     G4StepPoint* preStepPoint;
     G4StepPoint* postStepPoint;
     G4double InitialKinE;
     G4int DetectorVerbose;
     G4String creatorProcessName;
     G4double kineticEnergy;
     G4int detevent;

     G4int parEvent;
     G4int gammaEvent;
     G4int promptgammaEvent;
     G4int PGEvent;
     G4int neutronEvent;
     G4int neutronfromtarEvent;



};


#endif
