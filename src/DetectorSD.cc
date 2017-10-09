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
// $Id: DetectorSD.cc; 
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy
// **************************************************************************************

#include "DetectorSD.hh"
#include "DetectorHit.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "EventAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "RootAnalysis.hh"
#include "Matrix.hh"

#include "G4HadronicProcess.hh"
#include "G4HadronicProcessStore.hh"
#include "G4SystemOfUnits.hh"

// **************************************************************************************
DetectorSD::DetectorSD(G4String name, EventAction* evt)
 :G4VSensitiveDetector(name), eventAct(evt)
// --------------------------------------------------------------------------------------
{ 
  G4String HCname;
  collectionName.insert(HCname="DetectorHitsCollection");
  HitsCollection = NULL; 
  G4String sensitiveDetectorName = name;

}

// **************************************************************************************
DetectorSD::~DetectorSD()
// --------------------------------------------------------------------------------------
{ }

// **************************************************************************************
void DetectorSD::Initialize(G4HCofThisEvent*)
// --------------------------------------------------------------------------------------
{
  HitsCollection = new DetectorHitsCollection(sensitiveDetectorName, collectionName[0]);
}

// **************************************************************************************
G4bool DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
// --------------------------------------------------------------------------------------
{
  if(!ROhist) return false;

  //RootAnalysis* analysis = RootAnalysis::getInstance();
     Matrix* matrix = Matrix::GetInstance();

     theTrack = aStep  ->  GetTrack();
     parentID = aStep->GetTrack()->GetParentID();
     preStepPoint = aStep->GetPreStepPoint();
     postStepPoint = aStep->GetPostStepPoint();
     particleDef = theTrack -> GetDefinition();
     particleName =  particleDef -> GetParticleName();  
     stepNum= theTrack->GetCurrentStepNumber();
     energyAtPreStep = aStep->GetPreStepPoint()->GetKineticEnergy();
     energyAtPosStep = aStep -> GetPostStepPoint() -> GetKineticEnergy();
     coordOfPreStep  = aStep->GetPreStepPoint()->GetPosition();
     coordOfPostStep = aStep->GetPostStepPoint()->GetPosition();
     InitialKinE = theTrack->GetVertexKineticEnergy();
     G4String volume = aStep -> GetTrack() -> GetVolume()->GetName();
     trackID = theTrack -> GetTrackID();
   //G4int eventID = G4RunManagerKernel::GetRunManagerKernel()->GetEventManager()->GetConstCurrentEvent()->GetEventID();
   //G4double kineticEnergy =  aStep -> GetPreStepPoint() -> GetKineticEnergy();
     G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
     G4String createProcessVolume = theTrack->GetLogicalVolumeAtVertex()->GetName(); 

  // Get creation process 
     creatorProcessName = "---";                
     if (trackID > 1) { creatorProcessName = aStep->GetTrack()->GetCreatorProcess()->GetProcessName(); }

  // Post process name
     if (aStep -> GetPostStepPoint() -> GetProcessDefinedStep() != NULL)
     postProcessName = aStep -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();

  // Read voxel indexes: i is the x index, k is the z index
     G4int k  = ROhist -> GetReplicaNumber(0);
     G4int i  = ROhist -> GetReplicaNumber(2);
     G4int j  = ROhist -> GetReplicaNumber(1);


  // The following condition calls the 'EnergyDepositedPerEvent' if a particle makes a step inside the detector
     if	(aStep -> GetTrack() -> GetVolume()->GetName() == "DetectorPhys" )
        {EnergyDepositedPerEvent(aStep, ROhist);}

  // Increment Fluences & accumulate energy spectra
  // Hit voxels are marked with track_id throught hitTrack matrix
     if (matrix)
       {
            // hitTrack must be cleared at every eventAction!
            G4int* hitTrack = matrix -> GetHitTrack(i,j,k); 
            if ( *hitTrack != trackID )
	       {
	        *hitTrack = trackID;
	        // To Fill fluence data for every single nuclide 
	        // if ( Z>= 1)            //  exclude e-, neutrons, gamma, ...
                // if (A==1 && Z==1)       // primary and sec. protons 
	        // if ( Z== 1)
                // if (stepNum==1)
                // if (creatorProcessName =="hadElastic" && stepNum==1)
                // if (creatorProcessName =="NeutronInelastic" && stepNum==1)
                // if (creatorProcessName == "RadioactiveDecay" && stepNum==1)
                // if ((creatorProcessName == "ProtonInelastic")&& stepNum==1)

	           matrix-> Fill(trackID, particleDef, i, j, k, 0, true);   
                }
       
            if(energyDeposit != 0)
               {
	        // To fill a dose matrix for every single nuclide. 
	        // if ( Z==1 )
	        // if (A==1 && Z==1)         // primary and sec. protons 
                // if (trackID==1)
	        // if ( Z>=1 )               //  exclude e-, neutrons, gamma, ...
                // if (stepNum==1)
                // if (creatorProcessName  =="hadElastic" && stepNum==1)
                // if (creatorProcessName  =="NeutronInelastic" && stepNum==1)
                // if (creatorProcessName  == "RadioactiveDecay" && stepNum==1)
                // if ((creatorProcessName == "ProtonInelastic")&& stepNum==1)

                   matrix -> Fill(trackID, particleDef, i, j, k, energyDeposit);

	        // Create a hit with the information of position is in the detector     
	           DetectorHit* detectorHit = new DetectorHit();       
	           detectorHit -> SetEdepAndPosition(i, j, k, energyDeposit); 
	           HitsCollection -> insert(detectorHit);
               }
       }

 return true;

}

// **************************************************************************************
void DetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
// --------------------------------------------------------------------------------------
{

  //RootAnalysis* analysis = RootAnalysis::getInstance();
     static G4int HCID = -1;
     if(HCID < 0) { HCID = GetCollectionID(0);}
     HCE -> AddHitsCollection(HCID,HitsCollection);
   

}

// **************************************************************************************
void DetectorSD::EnergyDepositedPerEvent(const G4Step* aStep, G4TouchableHistory *ROhist)
// --------------------------------------------------------------------------------------
{	
  //G4int k  = ROhist -> GetReplicaNumber(0);
  //G4int i  = ROhist -> GetReplicaNumber(2);
  //G4int j  = ROhist -> GetReplicaNumber(1);
    G4double edep = aStep -> GetTotalEnergyDeposit();
    eventAct -> SumEnergy(edep/MeV);
}

// **************************************************************************************
