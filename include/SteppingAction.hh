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

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "globals.hh"

class RunAction;

#ifndef G4NOHIST
 class HepTupleManager;
 class HepHistogram;
#endif

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(RunAction*);
	~SteppingAction();
	
	void UserSteppingAction(const G4Step*);
	
private:
        std::map<G4ParticleDefinition*,G4int> fParticleFlag;   
	RunAction* runAction;
	G4TouchableHistory *ROhist;
        const G4TrackVector* temp;
        G4int verbose;
        const G4Isotope* target;
        G4int channelEventID;
        G4int gammaventID;
        G4int alphaEventID;
        G4int neutronEventID;
        G4int He3EventID;
        G4int deuteronEventID, tritonEventID;

        G4double QQ;
        G4double ED;

};
#endif
