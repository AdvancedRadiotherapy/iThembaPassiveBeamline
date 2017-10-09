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
// PassiveProtonBeamLineMessenger.cc;
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy

#include "PassiveProtonBeamLineMessenger.hh"
#include "PassiveProtonBeamLine.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

//*******************************************************************************************
PassiveProtonBeamLineMessenger::PassiveProtonBeamLineMessenger(PassiveProtonBeamLine* beamLine)
:passiveProton(beamLine)
//-------------------------------------------------------------------------------------------

{

    modulatorDir = new G4UIdirectory("/modulator/");
    modulatorDir -> SetGuidance("Command to rotate the modulator wheel");

    beamLineDir = new G4UIdirectory("/beamLine/");
    beamLineDir -> SetGuidance("set specification of range shifter"); 

    modulatorAngleCmd = new G4UIcmdWithADoubleAndUnit("/modulator/angle",this);
    modulatorAngleCmd -> SetGuidance("Set Modulator Angle");
    modulatorAngleCmd -> SetParameterName("Size",false);
    modulatorAngleCmd -> SetRange("Size>=0.");
    modulatorAngleCmd -> SetUnitCategory("Angle");  
    modulatorAngleCmd -> AvailableForStates(G4State_Idle);

    rangeMonitorZPositionCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/RangeMonitor/move",this);
    rangeMonitorZPositionCmd -> SetGuidance("Set position of range Range Monitor");
    rangeMonitorZPositionCmd -> SetParameterName("Size",false);
    rangeMonitorZPositionCmd -> SetDefaultUnit("mm");  
    rangeMonitorZPositionCmd -> SetUnitCandidates("mm cm m");  
    rangeMonitorZPositionCmd -> AvailableForStates(G4State_Idle);

    wedgeYPositionCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/Set/Range",this);
    wedgeYPositionCmd -> SetGuidance("Set position of wedge");
    wedgeYPositionCmd -> SetParameterName("Size",false);
    wedgeYPositionCmd -> SetDefaultUnit("cm");  
    wedgeYPositionCmd -> SetUnitCandidates("mm cm m");  
    wedgeYPositionCmd -> AvailableForStates(G4State_Idle);

    innerRadiusFinalCollimatorCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/TreatmentCollimator/Diameter",this);
    innerRadiusFinalCollimatorCmd -> SetGuidance("Set size of inner radius ( max 100 mm)");
    innerRadiusFinalCollimatorCmd -> SetParameterName("Size",false);
    innerRadiusFinalCollimatorCmd -> SetDefaultUnit("mm");  
    innerRadiusFinalCollimatorCmd -> SetUnitCandidates("mm cm m");  
    innerRadiusFinalCollimatorCmd -> AvailableForStates(G4State_Idle);

}
//*******************************************************************************************
PassiveProtonBeamLineMessenger::~PassiveProtonBeamLineMessenger()
//-------------------------------------------------------------------------------------------
{ 
    delete beamLineDir; 
    delete modulatorDir; 
    delete modulatorAngleCmd;  
    delete rangeMonitorZPositionCmd;
    delete wedgeYPositionCmd;
    delete innerRadiusFinalCollimatorCmd;  
}

//*******************************************************************************************
void PassiveProtonBeamLineMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
//-------------------------------------------------------------------------------------------
{ 
    if( command == modulatorAngleCmd )
    { passiveProton -> SetModulatorAngle (modulatorAngleCmd -> GetNewDoubleValue(newValue));}

    else if( command == rangeMonitorZPositionCmd )
    { passiveProton -> BeamRangeMonitor(rangeMonitorZPositionCmd -> GetNewDoubleValue(newValue));}

    else if( command == wedgeYPositionCmd )
    { passiveProton -> Wedge (wedgeYPositionCmd -> GetNewDoubleValue(newValue));}

    else if( command == innerRadiusFinalCollimatorCmd )
    { passiveProton -> BeamFinalCollimator(innerRadiusFinalCollimatorCmd -> GetNewDoubleValue(newValue));}

}
//*******************************************************************************************

