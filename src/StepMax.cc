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


#include "StepMax.hh"
#include "StepMaxMessenger.hh"

//*******************************************************************************************
StepMax::StepMax(const G4String& processName): G4VDiscreteProcess(processName),MaxChargedStep(DBL_MAX)
//-------------------------------------------------------------------------------------------
{
  pMess = new StepMaxMessenger(this);
}
 
//*******************************************************************************************
StepMax::~StepMax()
//-------------------------------------------------------------------------------------------
{ 
 delete pMess; 
}

//*******************************************************************************************
G4bool StepMax::IsApplicable(const G4ParticleDefinition& particle) 
//-------------------------------------------------------------------------------------------
{ 
  return (particle.GetPDGCharge() != 0.);
}

//*******************************************************************************************
void StepMax::SetMaxStep(G4double step)
//-------------------------------------------------------------------------------------------
{
  MaxChargedStep = step;
}

//*******************************************************************************************
void StepMax::SetMaxWorldStep(G4double step)
//-------------------------------------------------------------------------------------------
{
  MaxWorldChargedStep = step;
}


//*******************************************************************************************
G4double StepMax::PostStepGetPhysicalInteractionLength(const G4Track& aTrack,
                                                  G4double,G4ForceCondition* condition )
//-------------------------------------------------------------------------------------------
{
  // condition is set to "Not Forced"
     *condition = NotForced;
  
  // set the sepmax all the volume inside the World
     G4double ProposedStep = DBL_MAX;

  // set setmax only inside the Phantom
     if((MaxChargedStep > 0.) &&(aTrack.GetVolume() != 0) && (aTrack.GetVolume()->GetName() == "phantomPhys"))
      ProposedStep = MaxChargedStep;   

  // set setmax only inside the Detector
     if((MaxChargedStep > 0.) &&(aTrack.GetVolume() != 0) && (aTrack.GetVolume()->GetName() == "DetectorPhys"))    
      ProposedStep = MaxWorldChargedStep;   

     return ProposedStep;
}

//*******************************************************************************************
G4VParticleChange* StepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
//-------------------------------------------------------------------------------------------
{
   // do nothing
   aParticleChange.Initialize(aTrack);
   return &aParticleChange;
}
//-------------------------------------------------------------------------------------------

