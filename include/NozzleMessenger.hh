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
// Author:    Stephen Peterson          - swpeters@mdanderson.org
//            MD Anderson Cancer Center - Department of Radiation Physics
//            1515 Holcombe Blvd #94    - Houston, TX  77030
// Comments:  Model of scanning proton beam at MD Anderson PTC-H
//
// ********************************************************************

#ifndef NozzleMessenger_h
#define NozzleMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PassiveProtonBeamLine;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

// ********************************************************************
class NozzleMessenger: public G4UImessenger
{
  public:
    NozzleMessenger(PassiveProtonBeamLine*);
   ~NozzleMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    PassiveProtonBeamLine*            myNozzle;
    
    G4UIdirectory*             nozzleDir;
  
    G4UIcmdWithADoubleAndUnit* XFieldCmd;
    G4UIcmdWithADoubleAndUnit* YFieldCmd;
    G4UIcmdWithADoubleAndUnit* XSpotCmd;
    G4UIcmdWithADoubleAndUnit* YSpotCmd;
    G4UIcmdWithADoubleAndUnit* ZSpotCmd;
    G4UIcmdWithAString*        RemTubCmd;
    G4UIcmdWithAString*        RemRIonCmd;
    G4UIcmdWithAString*        RemYStMagCmd;
    G4UIcmdWithAString*        RemMulWirCmd;
    G4UIcmdWithAString*        RemXStMagCmd;
    G4UIcmdWithAString*        RemRanTriCmd;
    G4UIcmdWithAString*        RemLEPlaCmd;
    G4UIcmdWithAString*        RemWedgeCmd;
    G4UIcmdWithAString*        RemMutLaFraCmd;
    G4UIcmdWithAString*        RemRanModCmd;
    G4UIcmdWithAString*        RemRanModiThCmd;
    G4UIcmdWithAString*        RemRanMonCmd;
    G4UIcmdWithAString*        RemOccRinCmd;
    G4UIcmdWithAString*        RemShiColCmd;
    G4UIcmdWithAString*        RemQuMonIonCmd;
    G4UIcmdWithAString*        RemFinColCmd;
    G4UIcmdWithADoubleAndUnit* wedgeYPositionCmd;

};

// ********************************************************************
#endif

