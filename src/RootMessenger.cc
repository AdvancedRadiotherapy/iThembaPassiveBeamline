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
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"


// Specific libraries
#include "RootMessenger.hh"
#include "RootAnalysis.hh"
#include "Matrix.hh"

// ****************************************************************************
RootMessenger::RootMessenger(RootAnalysis* myRot):rootAnalysis(myRot)
// ----------------------------------------------------------------------------

{ 
    rootDir = new G4UIdirectory("/analysis/");
    rootDir->SetGuidance("set histogram.");
  
    fileRewriteCmd = new G4UIcmdWithAString("/analysis/allowFileRewriting", this);
    fileRewriteCmd->SetGuidance("set RootAnalysis to overwrite existing files, default is No.");
    fileRewriteCmd->SetGuidance("either 'Yes' or 'No'");
    fileRewriteCmd->SetParameterName("FileRewriting", false);
    fileRewriteCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    histVerbCmd = new G4UIcmdWithAnInteger("/analysis/verbose", this);
    histVerbCmd->SetGuidance("Set Verbose level for histogram analysis");
    histVerbCmd->SetGuidance(" 0 : Silent");
    histVerbCmd->SetGuidance(" 1 : Limited information");
    histVerbCmd->SetGuidance(" 2 : Detailed information");
    histVerbCmd->SetGuidance(" 3 : Very Detailed information");
    histVerbCmd->SetParameterName("HistogramVerbosity", false);
    histVerbCmd->SetRange("level>=0 && level<=3");

    secondaryCmd = new G4UIcmdWithABool("/analysis/detector/secondary", this);
    secondaryCmd -> SetParameterName("secondary", true);
    secondaryCmd -> SetGuidance("Set if dose/fluence for the secondary are written"); 
    secondaryCmd -> AvailableForStates(G4State_Idle, G4State_PreInit);
	
    DoseMatrixCmd = new G4UIcmdWithAString("/analysis/detector/writeDoseFile",this);
    DoseMatrixCmd->SetGuidance("Write the dose/fluence to an ASCII file");
    DoseMatrixCmd->SetDefaultValue("Dose.out");
    DoseMatrixCmd->SetParameterName("choice",true);


}

// ****************************************************************************
RootMessenger::~RootMessenger()
// ----------------------------------------------------------------------------
{
    delete rootDir;
    delete fileRewriteCmd;
    delete secondaryCmd; 
    delete DoseMatrixCmd;

}

// ****************************************************************************
void RootMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
// ----------------------------------------------------------------------------
{

    if( command == fileRewriteCmd ){
    rootAnalysis->SetFileRewriting(newValue);}

    if ( command == histVerbCmd ){
    rootAnalysis->SetHistogramVerbosity(histVerbCmd->GetNewIntValue(newValue)); }

    if (command == secondaryCmd)
    {
		if (Matrix::GetInstance())
		{Matrix::GetInstance() -> secondary = secondaryCmd -> GetNewBoolValue(newValue);}
    }

    if (command == DoseMatrixCmd) // Filename can be passed here TODO 
    { 
		if ( Matrix *pMatrix = Matrix::GetInstance() )
		{
			pMatrix -> TotalEnergyDeposit(); 
			pMatrix -> StoreDoseFluenceAscii(newValue);
		}
    }


}

// ****************************************************************************
