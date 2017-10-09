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
//   PhantomAnalysis.hh
// ====================================================================
#ifndef PHANTOM_ANALYSIS_H
#define PHANTOM_ANALYSIS_H 

#include <vector>
#include <map>
#include <iomanip>
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4UserRunAction.hh"
#include "G4Step.hh"


class DetectorHit;
class PhantomAnalysisMessenger;
class G4Track;
class G4Step;



class PhantomAnalysis {


public:
  ~PhantomAnalysis();

  static PhantomAnalysis* GetPhantomAnalysis();
  void storePhantomData(const G4Step& aStep);
  void TargetMaterial(G4Material* pMat, G4double PZSize);
  
  void BeginOfEvent();
  void BeginOfRun();
  void EndOfEvent();
  void EndOfRun(G4int NofEvent);

  void  SetKillEvent(G4String name)  {killEvent = name;};


private:
     PhantomAnalysis();
     static PhantomAnalysis* thePhantomAnalysis;
     PhantomAnalysisMessenger* messenger;

     G4double dx;
     G4ParticleDefinition* particle;
     G4String particleName;
     G4int eventID;
     G4int trackID;
     G4double tracklength;
     G4int parentID;
     G4int stepNum;
     G4double dE;
     G4StepPoint* preStepVol;
     G4StepPoint* endPoint;
     G4double InitialKinE;
     G4int PhantomVerbose;
     G4String creatorProcessName;
     G4double time;
     G4double kineticEnergy;
     
     G4String killEvent;

     G4double PrimaryDE;
     G4double PrimaryDX;
     G4double PrimaryDEDX;
     G4double TotalDEDX;
     G4double StoppingPower;

     G4Material* material;
     G4double PhantomLength;
     G4double density;
     G4double TotalsigmaRange;
     G4int count;

     std::vector<G4double> Energy;
     std::vector<G4double> ProjectedRange;

     G4int channelEventID;
     G4int channelTrackID;
     G4double reactionTime;
     G4int Chcount;
     G4double gammaEg;
     G4int SPVerbose;


};


#endif
