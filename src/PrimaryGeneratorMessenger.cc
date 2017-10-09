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
// PrimaryGeneratorMessenger.hh;
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy



#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
:Action(Gun)
{ 

 beamParametersDir = new G4UIdirectory("/beam/");
 beamParametersDir -> SetGuidance("set parameters of beam");
 
 EnergyDir = new G4UIdirectory("/beam/energy/");  
 EnergyDir -> SetGuidance ("set energy of beam");  

 particlePositionDir = new G4UIdirectory("/beam/position/");  
 particlePositionDir -> SetGuidance ("set position of particle");  

 MomentumDir = new G4UIdirectory("/beam/momentum/");  
 MomentumDir -> SetGuidance ("set momentum of particle ");  

}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete beamParametersDir;
  delete EnergyDir;
  delete particlePositionDir;
  delete MomentumDir;

}  

/*
void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)                
{ }
*/