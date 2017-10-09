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

// General libraries
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "globals.hh"

// Specific libraries
#include "NozzleMessenger.hh"
#include "PassiveProtonBeamLine.hh"

// ****************************************************************************
NozzleMessenger::NozzleMessenger(PassiveProtonBeamLine* myNoz):myNozzle(myNoz)
// ----------------------------------------------------------------------------
{ 
    nozzleDir = new G4UIdirectory("/nozzle/");
    nozzleDir->SetGuidance("UI commands specific to the beam-scanning nozzle.");
    
    XFieldCmd = new G4UIcmdWithADoubleAndUnit("/nozzle/setXField",this);  
    XFieldCmd->SetGuidance("Define magnetic field.");
    XFieldCmd->SetGuidance("Magnetic field will be in X direction.");
    XFieldCmd->SetParameterName("Bx",false);
    XFieldCmd->SetUnitCategory("Magnetic flux density");
    XFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    YFieldCmd = new G4UIcmdWithADoubleAndUnit("/nozzle/setYField",this);  
    YFieldCmd->SetGuidance("Define magnetic field.");
    YFieldCmd->SetGuidance("Magnetic field will be in Y direction.");
    YFieldCmd->SetParameterName("By",false);
    YFieldCmd->SetUnitCategory("Magnetic flux density");
    YFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    XSpotCmd = new G4UIcmdWithADoubleAndUnit("/nozzle/setXSpotPosition",this);  
    XSpotCmd->SetGuidance("Define spot position in mm (x-direction).");
    XSpotCmd->SetParameterName("xSpot",false);
    XSpotCmd->SetUnitCategory("Length");
    XSpotCmd->SetDefaultUnit("mm");
    XSpotCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    YSpotCmd = new G4UIcmdWithADoubleAndUnit("/nozzle/setYSpotPosition",this);  
    YSpotCmd->SetGuidance("Define spot position in mm (y-direction).");
    YSpotCmd->SetParameterName("ySpot",false);
    YSpotCmd->SetUnitCategory("Length");
    YSpotCmd->SetDefaultUnit("mm");
    YSpotCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    ZSpotCmd = new G4UIcmdWithADoubleAndUnit("/nozzle/setZSpotPosition",this);  
    ZSpotCmd->SetGuidance("Define spot position in mm (z-direction).");
    ZSpotCmd->SetParameterName("zSpot",false);
    ZSpotCmd->SetUnitCategory("Length");
    ZSpotCmd->SetDefaultUnit("mm");
    ZSpotCmd->AvailableForStates(G4State_PreInit,G4State_Idle);                   

    RemTubCmd = new G4UIcmdWithAString("/nozzle/removeVacuumTube", this);
    RemTubCmd->SetGuidance("Choose whether to remove VacuumTube from simulation.");
    RemTubCmd->SetParameterName("RemoveVacuumTube", false);
    RemTubCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemRIonCmd = new G4UIcmdWithAString("/nozzle/removeReferenceIonizationChamber", this);
    RemRIonCmd->SetGuidance("Choose whether to remove ReferenceIonizationChamber from simulation.");
    RemRIonCmd->SetGuidance("either 'Yes' or 'No'");
    RemRIonCmd->SetParameterName("RemoveReferenceIonizationChamber", false);
    RemRIonCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemYStMagCmd = new G4UIcmdWithAString("/nozzle/removeYSteeringMagnets", this);
    RemYStMagCmd->SetGuidance("Choose whether to remove YSteeringMagnets from simulation.");
    RemYStMagCmd->SetGuidance("either 'Yes' or 'No'");
    RemYStMagCmd->SetParameterName("RemoveYSteeringMagnets", false);
    RemYStMagCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemMulWirCmd = new G4UIcmdWithAString("/nozzle/removeMultiWireIonizationChamber", this);
    RemMulWirCmd->SetGuidance("Choose whether to remove MultiWireIonizationChamber from simulation.");
    RemMulWirCmd->SetGuidance("either 'Yes' or 'No'");
    RemMulWirCmd->SetParameterName("RemoveMultiWireIonizationChamber", false);
    RemMulWirCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemXStMagCmd = new G4UIcmdWithAString("/nozzle/removeXSteeringMagnets", this);
    RemXStMagCmd->SetGuidance("Choose whether to remove XSteeringMagnets from simulation.");
    RemXStMagCmd->SetGuidance("either 'Yes' or 'No'");
    RemXStMagCmd->SetParameterName("RemoveXSteeringMagnets", false);
    RemXStMagCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemRanTriCmd = new G4UIcmdWithAString("/nozzle/removeRangeTrimmerPlate", this);
    RemRanTriCmd->SetGuidance("Choose whether to remove RangeTrimmerPlate from simulation.");
    RemRanTriCmd->SetGuidance("either 'Yes' or 'No'");
    RemRanTriCmd->SetParameterName("RemoveRangeTrimmerPlate", false);
    RemRanTriCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemLEPlaCmd = new G4UIcmdWithAString("/nozzle/removeLeadPlate", this);
    RemLEPlaCmd->SetGuidance("Choose whether to remove LeadPlate from simulation.");
    RemLEPlaCmd->SetParameterName("RemoveLeadPlate", false);
    RemLEPlaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemWedgeCmd = new G4UIcmdWithAString("/nozzle/removeWedge", this);
    RemWedgeCmd->SetGuidance("Choose whether to remove Wedge from simulation.");
    RemWedgeCmd->SetGuidance("either 'Yes' or 'No'");
    RemWedgeCmd->SetParameterName("RemoveWedge", false);
    RemWedgeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemMutLaFraCmd = new G4UIcmdWithAString("/nozzle/removeMultiLayerFaradayCup", this);
    RemMutLaFraCmd->SetGuidance("Choose whether to remove MultiLayerFaradayCup from simulation.");
    RemMutLaFraCmd->SetGuidance("either 'Yes' or 'No'");
    RemMutLaFraCmd->SetParameterName("RemoveMultiLayerFaradayCup", false);
    RemMutLaFraCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemRanModCmd = new G4UIcmdWithAString("/nozzle/removeRangeModulator", this);
    RemRanModCmd->SetGuidance("Choose whether to remove RangeModulator from simulation.");
    RemRanModCmd->SetGuidance("either 'Yes' or 'No'");
    RemRanModCmd->SetParameterName("RemoveRangeModulator", false);
    RemRanModCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemRanModiThCmd = new G4UIcmdWithAString("/nozzle/removeNewRangeMonitoriThemba", this);
    RemRanModiThCmd->SetGuidance("Choose whether to remove RangeModulator from simulation.");
    RemRanModiThCmd->SetGuidance("either 'Yes' or 'No'");
    RemRanModiThCmd->SetParameterName("RemoveNewRangeMonitoriThemba", false);
    RemRanModiThCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemRanMonCmd = new G4UIcmdWithAString("/nozzle/removeRangeMonitor", this);
    RemRanMonCmd->SetGuidance("Choose whether to remove RangeMonitor from simulation.");
    RemRanMonCmd->SetGuidance("either 'Yes' or 'No'");
    RemRanMonCmd->SetParameterName("RemoveRangeMonitor", false);
    RemRanMonCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemOccRinCmd = new G4UIcmdWithAString("/nozzle/removeOccludingRingAndCentralStopper", this);
    RemOccRinCmd->SetGuidance("Choose whether to remove OccludingRingAndCentralStopper from simulation.");
    RemOccRinCmd->SetGuidance("either 'Yes' or 'No'");
    RemOccRinCmd->SetParameterName("RemoveOccludingRingAndCentralStopper", false);
    RemOccRinCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemShiColCmd = new G4UIcmdWithAString("/nozzle/removeShieldingCollimators", this);
    RemShiColCmd->SetGuidance("Choose whether to remove ShieldingCollimators from simulation.");
    RemShiColCmd->SetGuidance("either 'Yes' or 'No'");
    RemShiColCmd->SetParameterName("RemoveShieldingCollimators", false);
    RemShiColCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemQuMonIonCmd = new G4UIcmdWithAString("/nozzle/removeQuadrantAndMonitorIonizationChamber", this);
    RemQuMonIonCmd->SetGuidance("Choose whether to remove QuadrantAndMonitorIonizationChamber from simulation.");
    RemQuMonIonCmd->SetGuidance("either 'Yes' or 'No'");
    RemQuMonIonCmd->SetParameterName("RemoveQuadrantAndMonitorIonizationChamber", false);
    RemQuMonIonCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    RemFinColCmd = new G4UIcmdWithAString("/nozzle/removeBeamFinalCollimator", this);
    RemFinColCmd->SetGuidance("Choose whether to remove BeamFinalCollimator from simulation.");
    RemFinColCmd->SetGuidance("either 'Yes' or 'No'");
    RemFinColCmd->SetParameterName("RemoveBeamFinalCollimator", false);
    RemFinColCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    wedgeYPositionCmd = new G4UIcmdWithADoubleAndUnit("/nozzle/Wedge/move",this);
    wedgeYPositionCmd -> SetGuidance("Set position of wedge");
    wedgeYPositionCmd -> SetParameterName("Size",false);
    wedgeYPositionCmd -> SetDefaultUnit("mm");  
    wedgeYPositionCmd -> SetUnitCandidates("mm cm m");  
    wedgeYPositionCmd -> AvailableForStates(G4State_Idle);

}

// ****************************************************************************
NozzleMessenger::~NozzleMessenger()
// ----------------------------------------------------------------------------
{
    delete XFieldCmd;
    delete YFieldCmd;
    delete XSpotCmd;
    delete YSpotCmd;
    delete ZSpotCmd;
    delete RemTubCmd;
    delete RemRIonCmd;
    delete RemYStMagCmd;
    delete RemMulWirCmd;
    delete RemXStMagCmd;
    delete RemRanTriCmd;
    delete RemLEPlaCmd;
    delete RemWedgeCmd;
    delete RemMutLaFraCmd;
    delete RemRanModCmd;
    delete RemRanMonCmd;
    delete RemOccRinCmd;
    delete RemShiColCmd;
    delete RemQuMonIonCmd;
    delete RemFinColCmd;
    delete nozzleDir;
    delete RemRanModiThCmd;
    delete wedgeYPositionCmd;
}

// ****************************************************************************
void NozzleMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
// ----------------------------------------------------------------------------
{

    if( command == XFieldCmd )
      { myNozzle->SetXMagField(XFieldCmd->GetNewDoubleValue(newValue));}

    if( command == YFieldCmd )
      { myNozzle->SetYMagField(YFieldCmd->GetNewDoubleValue(newValue));}

    if( command == XSpotCmd )
      { myNozzle->SetXSpotPosition(XSpotCmd->GetNewDoubleValue(newValue));}

    if( command == YSpotCmd )
      { myNozzle->SetYSpotPosition(YSpotCmd->GetNewDoubleValue(newValue));}

    if( command == ZSpotCmd )
      { myNozzle->SetZSpotPosition(ZSpotCmd->GetNewDoubleValue(newValue));}

    if( command == RemTubCmd )
      { myNozzle->SetRemoveVacuumTube(newValue);}

    if( command == RemRIonCmd )
      { myNozzle->SetRemoveReferenceIonizationChamber(newValue);}

    if( command == RemYStMagCmd )
      { myNozzle->SetRemoveYSteeringMagnets(newValue);}

    if( command == RemMulWirCmd )
      { myNozzle->SetRemoveMultiWireIonizationChamber(newValue);}

    if( command == RemXStMagCmd )
      { myNozzle->SetRemoveXSteeringMagnets(newValue);}

    if( command == RemRanTriCmd )
      { myNozzle->SetRemoveRangeTrimmerPlate(newValue);}

    if( command == RemLEPlaCmd )
      { myNozzle->SetRemoveLeadPlate(newValue);}

    if( command == RemWedgeCmd )
      { myNozzle->SetRemoveWedge(newValue);}

    if( command == RemMutLaFraCmd )
      { myNozzle->SetRemoveMultiLayerFaradayCup(newValue);}

    if( command == RemRanModCmd )
      { myNozzle->SetRemoveRangeModulator(newValue);}

    if( command == RemRanModiThCmd )
      { myNozzle->RemoveNewRangeMonitoriThemba(newValue);}

    if( command == RemRanMonCmd )
      { myNozzle->SetRemoveRangeMonitor(newValue);}

    if( command == RemOccRinCmd )
      { myNozzle->SetRemoveOccludingRingAndCentralStopper(newValue);}

    if( command == RemShiColCmd )
      { myNozzle->SetRemoveShieldingCollimators(newValue);}

    if( command == RemQuMonIonCmd )
      { myNozzle->SetRemoveQuadrantAndMonitorIonizationChamber(newValue);}

    if( command == RemFinColCmd )
      { myNozzle->SetRemoveBeamFinalCollimator(newValue);}

    if( command == wedgeYPositionCmd )
    { myNozzle -> SetWedgepostion (wedgeYPositionCmd -> GetNewDoubleValue(newValue));}
}

// ****************************************************************************
