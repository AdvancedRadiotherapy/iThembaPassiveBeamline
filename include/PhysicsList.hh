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


#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4EmConfigurator.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class StepMax;
class PhysicsListMessenger;

class PhysicsList: public G4VModularPhysicsList
{
public:

  PhysicsList();
  virtual ~PhysicsList();

  void ConstructParticle();

  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);
  void SetCutForProton(G4double);
  void SetDetectorCut(G4double cut);
  void SetTargetCut(G4double cut);
  void AddPhysicsList(const G4String& name);
  void ConstructProcess();

  void AddStepMax();
  StepMax* GetStepMaxProcess() {return stepMaxProcess;};
  void AddPackage(const G4String& name);

private:

  G4EmConfigurator em_config;

  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;

  G4bool helIsRegistered;
  G4bool bicIsRegistered;
  G4bool biciIsRegistered;
  G4bool locIonIonInelasticIsRegistered;
  G4bool radioactiveDecayIsRegistered;

  G4bool electronIsRegistered;
  G4bool positronIsRegistered;
  G4bool photonIsRegistered;
  G4bool ionIsRegistered;
  G4bool protonHadronicIsRegistered;
  G4bool chargedParticleIsRegistered;
  G4bool muonIsRegistered;
  G4bool decayIsRegistered;

  G4String                             emName;
  G4VPhysicsConstructor*               emPhysicsList;
  G4VPhysicsConstructor*               decPhysicsList;
  G4VPhysicsConstructor*               raddecayList;
  std::vector<G4VPhysicsConstructor*>  hadronPhys;

  StepMax* stepMaxProcess;

  PhysicsListMessenger* pMessenger;
};

#endif
