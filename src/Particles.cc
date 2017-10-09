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


#include "Particles.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4LeptonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4OpticalPhoton.hh"

// ******************************************************************************************
Particles::Particles(const G4String& name):  G4VPhysicsConstructor(name)
// ------------------------------------------------------------------------------------------
{ }

// ******************************************************************************************
Particles::~Particles()
// ------------------------------------------------------------------------------------------
{}

// ******************************************************************************************
void Particles::ConstructParticle()
// ------------------------------------------------------------------------------------------
{ 
  //
  // Define all the particles involved in the experimental set-up
  //

  G4LeptonConstructor lepton;
  lepton.ConstructParticle();
 
  G4BosonConstructor boson;
  boson.ConstructParticle();

  G4MesonConstructor meson;
  meson.ConstructParticle();

  G4BaryonConstructor baryon;
  baryon.ConstructParticle();

  G4ShortLivedConstructor shortLived;
  shortLived.ConstructParticle();

  G4IonConstructor ion;
  ion.ConstructParticle();

}
// ******************************************************************************************
