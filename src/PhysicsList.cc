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
// This is the *BASIC* version of Hadrontherapy, a Geant4-based application
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy
//
// Visit the Hadrontherapy web site (http://www.lns.infn.it/link/Hadrontherapy) to request 
// the *COMPLETE* version of this program, together with its documentation;
// Hadrontherapy (both basic and full version) are supported by the Italian INFN
// Institute in the framework of the MC-INFN Group
//
//
// Hadrontherapy Users are recommended to use the prepared macro files in order to activate the 
// most appropriate physics for hadrontherapy applications.
// As one can easily see the physics we suggest is contained in the
// 'QGSP_BIC_EMY' list adding to the decay processes (activated as default).
//
//
//    ******                     SUGGESTED PHYSICS                 *********
//
//    AT MOMENT, IF ACCURATE RESULTS ARE NEEDED, WE STRONGLY RECOMMEND: 
//    1. The use of the macro 'hadron_therapy.mac', that is connected with the PhysicsList.cc file.
//    2. the QGSP_BIC_EMY Reference Physics Lists (define the PHYSLIST eviroment variable):
//       export PHYSLIST=QGSP_BIC_EMY
//       User must considered that, in this second case, radioactive processes are not activated 
 
#include "G4RunManager.hh"
#include "G4Region.hh"
#include "G4UserLimits.hh"
#include "G4RegionStore.hh"
#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"
#include "StepMax.hh"
#include "G4PhysListFactory.hh"
#include "G4VPhysicsConstructor.hh"
#include "Particles.hh"
#include "G4SystemOfUnits.hh"


// Physic lists (contained inside the Geant4 source code, in the 'physicslists folder')
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"
#include "G4OpticalPhysics.hh"
#include "GammaPhysics.hh"


//*****************************************************************************************
PhysicsList::PhysicsList() : G4VModularPhysicsList(),
			     electronIsRegistered(false), 
			     positronIsRegistered(false), 
			     photonIsRegistered(false), 
			     ionIsRegistered(false),
			     protonHadronicIsRegistered(false),
			     muonIsRegistered(false),
			     decayIsRegistered(false)
//-----------------------------------------------------------------------------------------
{
  G4LossTableManager::Instance();
  defaultCutValue = 1.0*mm;

  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;
  cutForProton    = defaultCutValue;

  helIsRegistered  = false;
  bicIsRegistered  = false;
  biciIsRegistered = false;
  locIonIonInelasticIsRegistered = false;
  radioactiveDecayIsRegistered = false;

  stepMaxProcess  = 0;

  pMessenger = new PhysicsListMessenger(this);

  SetVerboseLevel(1);

  //add new units for cross sections
   
    new G4UnitDefinition( "mm2/g", "mm2/g","Surface/Mass", mm2/g);
    new G4UnitDefinition( "um2/mg", "um2/mg","Surface/Mass", um*um/mg);  

  // Defaults Physics List  
  // If no physics is called by the macro file 

  // EM physics
     emPhysicsList = new G4EmStandardPhysics_option3(1);
     emName = G4String("emstandard_opt3");

  // Decay physics and all particles
     decPhysicsList = new G4DecayPhysics();
     raddecayList   = new G4RadioactiveDecayPhysics();

    G4cout << "  __________________________________"<< G4endl;
    G4cout << "                                    "<< G4endl;
    G4cout << "         Default Physics List           "<< G4endl;
    G4cout << "  __________________________________"<< G4endl;
    G4cout << "                                    "<< G4endl;
    G4cout << "   G4EmStandardPhysics_option3      "<< G4endl;
    G4cout << "   G4DecayPhysics                   "<< G4endl;
    G4cout << "   G4RadioactiveDecayPhysics        "<< G4endl;
    G4cout << "                                    "<< G4endl;
    G4cout << "   The "<<"Default Physics List has been activated !!!!! "<< G4endl;
    G4cout << "  __________________________________"<< G4endl;
    G4cout << "                                    "<< G4endl;  


    // Register all the particles involved in the experimental set-up
    //RegisterPhysics( new Particles("particles") );
}

//*****************************************************************************************
PhysicsList::~PhysicsList()
//-----------------------------------------------------------------------------------------
{
  delete pMessenger;
  delete emPhysicsList;
  delete decPhysicsList;
  delete raddecayList;

  for(size_t i=0; i<hadronPhys.size(); i++) {delete hadronPhys[i];}
}

//*****************************************************************************************
void PhysicsList::ConstructParticle()
//-----------------------------------------------------------------------------------------
{
  decPhysicsList->ConstructParticle();
}

//*****************************************************************************************
void PhysicsList::ConstructProcess()
//-----------------------------------------------------------------------------------------
{
  // transportation
     AddTransportation();

  // electromagnetic physics list
     emPhysicsList->ConstructProcess();
     em_config.AddModels();

  // decay physics list
     decPhysicsList->ConstructProcess();
     raddecayList->ConstructProcess();

  // hadronic physics lists
     for(size_t i=0; i<hadronPhys.size(); i++) {
     hadronPhys[i] -> ConstructProcess();
    }

  // step limitation (as a full process)  
     AddStepMax();
}

//*****************************************************************************************
void PhysicsList::AddPhysicsList(const G4String& name)
//-----------------------------------------------------------------------------------------
{

  if (verboseLevel>1) {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;

  }
  if (name == emName) return;

  // EM Physics List

  if (name == "standard_opt3") {
      emName = name;
      delete emPhysicsList;


    G4cout << "                                    "<< G4endl;
    G4cout << "   G4EmStandardPhysics_option3 has been deleted from default list !!!!"<<G4endl;
    G4cout << "                                    "<< G4endl;

    emPhysicsList = new G4EmStandardPhysics_option3();
    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();

   G4cout << "  __________________________________"<< G4endl;
   G4cout << "                                    "<< G4endl;
   G4cout << "             Physics List           "<< G4endl;
   G4cout << "  __________________________________"<< G4endl;
   G4cout << "                                    "<< G4endl;
   G4cout << "   G4EmStandardPhysics_option3 "<< "Activated !!!!"<<G4endl;

  }if (name == "standard_opt4") {
      emName = name;
      delete emPhysicsList;


    G4cout << "                                    "<< G4endl;
    G4cout << "   G4EmStandardPhysics_option3 has been deleted from default list !!!!"<<G4endl;
    G4cout << "                                    "<< G4endl;

    emPhysicsList = new G4EmStandardPhysics_option4();
    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();

   G4cout << "  __________________________________"<< G4endl;
   G4cout << "                                    "<< G4endl;
   G4cout << "             Physics List           "<< G4endl;
   G4cout << "  __________________________________"<< G4endl;
   G4cout << "                                    "<< G4endl;
   G4cout << "   G4EmStandardPhysics_option4 "<< "Activated !!!!"<<G4endl;


  } else if (name == "LowE_Livermore") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmLivermorePhysics();
    G4RunManager::GetRunManager()-> PhysicsHasBeenModified();
    G4cout << "THE FOLLOWING ELECTROMAGNETIC PHYSICS LIST HAS BEEN ACTIVATED: G4EmLivermorePhysics" << G4endl;

  } else if (name == "LowE_Penelope") {
    emName = name;
    delete emPhysicsList;
    emPhysicsList = new G4EmPenelopePhysics();
    G4RunManager::GetRunManager()-> PhysicsHasBeenModified();
    G4cout << "THE FOLLOWING ELECTROMAGNETIC PHYSICS LIST HAS BEEN ACTIVATED: G4EmPenelopePhysics" << G4endl;


  } else if (name == "QGSP_BIC_EMY") {

    AddPhysicsList("standard_opt4");
    hadronPhys.push_back( new G4HadronPhysicsQGSP_BIC());
    hadronPhys.push_back( new G4EmExtraPhysics());
    hadronPhys.push_back( new G4HadronElasticPhysics());
    hadronPhys.push_back( new G4StoppingPhysics());
    hadronPhys.push_back( new G4IonBinaryCascadePhysics());
    hadronPhys.push_back( new G4NeutronTrackingCut());
    G4RunManager::GetRunManager()-> PhysicsHasBeenModified();

    G4cout << "                                    "<< G4endl;
    G4cout << "   G4EmStandardPhysics_option4      "<< G4endl;
    G4cout << "   G4EmExtraPhysics                 "<< G4endl;
    G4cout << "   G4HadronElasticPhysics           "<< G4endl;
    G4cout << "   G4QStoppingPhysics               "<< G4endl;
    G4cout << "   G4IonBinaryCascadePhysics        "<< G4endl;
    G4cout << "   G4NeutronTrackingCut             "<< G4endl;
    G4cout << "                                    "<< G4endl;
    G4cout << "   The "<<name<<" has been activated !!!!! "<< G4endl;
    G4cout << "  __________________________________"<< G4endl;
    G4cout << "                                    "<< G4endl; 
 
    }
    else { 
    G4cout << "                                     "<< G4endl;
    G4cout << "   The PhysicsList < " << name << "> "<< G4endl;
    G4cout << "   is not defined !!!!               "<< G4endl;
    G4cout << "  __________________________________ "<< G4endl;
    G4cout << "                                     "<< G4endl;
    }

}

// cuts and stepmax setting 
//*****************************************************************************************
void PhysicsList::AddStepMax()
//-----------------------------------------------------------------------------------------
{
  // Step limitation seen as a process
  stepMaxProcess = new StepMax();

  theParticleIterator->reset();
  while ((*theParticleIterator)()){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (stepMaxProcess->IsApplicable(*particle) && pmanager)
      {
	pmanager ->AddDiscreteProcess(stepMaxProcess);
      }
  }
}

//*****************************************************************************************
void PhysicsList::SetCuts()
//-----------------------------------------------------------------------------------------
{
  if (verboseLevel >0){
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
     SetCutValue(cutForGamma, "gamma");
     SetCutValue(cutForElectron, "e-");
     SetCutValue(cutForPositron, "e+");
     SetCutValue(cutForProton, "proton");

  // Set cuts for detector
     SetDetectorCut(defaultCutValue); 
     if (verboseLevel>0) DumpCutValuesTable();

  // Set cuts for traget
     SetTargetCut(defaultCutValue); 
}

//*****************************************************************************************
void PhysicsList::SetCutForGamma(G4double cut)
//-----------------------------------------------------------------------------------------
{
  cutForGamma = cut;
  SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//*****************************************************************************************
void PhysicsList::SetCutForElectron(G4double cut)
//-----------------------------------------------------------------------------------------
{
  cutForElectron = cut;
  SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//*****************************************************************************************
void PhysicsList::SetCutForPositron(G4double cut)
//-----------------------------------------------------------------------------------------
{
  cutForPositron = cut;
  SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//*****************************************************************************************
void PhysicsList::SetCutForProton(G4double cut)
//-----------------------------------------------------------------------------------------
{
  cutForProton = cut;
  //SetParticleCuts(cutForProton, G4Proton::Proton());
}

//*****************************************************************************************
void PhysicsList::SetDetectorCut(G4double cut)
//-----------------------------------------------------------------------------------------
{
  G4String regionName = "Detector_Region";
  G4Region* Detregion = G4RegionStore::GetInstance()->GetRegion(regionName);

  G4ProductionCuts* cuts = new G4ProductionCuts ;
  cuts -> SetProductionCut(cut,G4ProductionCuts::GetIndex("gamma"));
  cuts -> SetProductionCut(cut,G4ProductionCuts::GetIndex("e-"));
  cuts -> SetProductionCut(cut,G4ProductionCuts::GetIndex("e+"));
  if(Detregion)Detregion -> SetProductionCuts(cuts);
}


//*****************************************************************************************
void PhysicsList::SetTargetCut(G4double cut)
//-----------------------------------------------------------------------------------------
{

  G4Region* phtuberegion = G4RegionStore::GetInstance()->GetRegion("phantomTub_Region");
  G4Region* phregion = G4RegionStore::GetInstance()->GetRegion("phantom_Region");

  G4ProductionCuts* cuts = new G4ProductionCuts ;
  cuts -> SetProductionCut(cut,G4ProductionCuts::GetIndex("gamma"));
  cuts -> SetProductionCut(cut,G4ProductionCuts::GetIndex("e-"));
  cuts -> SetProductionCut(cut,G4ProductionCuts::GetIndex("e+"));
  if(phtuberegion)phtuberegion -> SetProductionCuts(cuts);
  if(phregion) phregion -> SetProductionCuts(cuts);

}


