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


#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trd.hh"
#include "G4Hype.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "G4NistElementBuilder.hh"
#include "G4SubtractionSolid.hh"
#include "DetectorConstruction.hh"
#include "OpenBeamLine.hh"
#include "NozzleMaterial.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
//#include "PassiveProtonBeamLineMessenger.hh"

//*******************************************************************************************
OpenBeamLine::OpenBeamLine(): detector(0), physicalTreatmentRoom(0),
physiBeamLineSupport(0)
//-------------------------------------------------------------------------------------------

{

   nozzleMaterial  = new NozzleMaterial();
	
}
//*******************************************************************************************
OpenBeamLine::~OpenBeamLine()
//-------------------------------------------------------------------------------------------

{
	delete detector;
        delete nozzleMaterial;
}

//*******************************************************************************************
G4VPhysicalVolume* OpenBeamLine::Construct()
//-------------------------------------------------------------------------------------------
{ 

	SetDefaultDimensions();
        SetDefaultMaterials();
        SetDefaultColors();	
	ConstructOpenBeamLine();
        	
     // DetectorConstruction builds ONLY the phantom and the detector with its associated ROGeometry
	detector = new DetectorConstruction(physicalTreatmentRoom); 
	
	return physicalTreatmentRoom;
}

//*******************************************************************************************
void OpenBeamLine::SetDefaultDimensions()
//-------------------------------------------------------------------------------------------
{
}

//*******************************************************************************************
void OpenBeamLine::SetDefaultColors()
//-------------------------------------------------------------------------------------------
{
	white = new G4VisAttributes( G4Colour());
	white -> SetVisibility(true);
	white -> SetForceSolid(true);
	
	blue = new G4VisAttributes(G4Colour(0. ,0. ,1.));
	blue -> SetVisibility(true);
	blue -> SetForceSolid(true);
	
	gray = new G4VisAttributes( G4Colour(0.5, 0.5, 0.5 ));
	gray-> SetVisibility(true);
	gray-> SetForceSolid(true);
	
	red = new G4VisAttributes(G4Colour(1. ,0. ,0.));
	red-> SetVisibility(true);
	red-> SetForceSolid(true);
	
	yellow = new G4VisAttributes(G4Colour(1., 1., 0. ));
	yellow-> SetVisibility(true);
	yellow-> SetForceSolid(true);
	
	green = new G4VisAttributes( G4Colour(25/255. , 255/255. ,  25/255. ));
	green -> SetVisibility(true);
	green -> SetForceSolid(true);
	
	darkGreen = new G4VisAttributes( G4Colour(0/255. , 100/255. ,  0/255. ));
	darkGreen -> SetVisibility(true);
	darkGreen -> SetForceSolid(true);
	
	darkOrange3 = new G4VisAttributes( G4Colour(205/255. , 102/255. ,  000/255. ));
	darkOrange3 -> SetVisibility(true);
	darkOrange3 -> SetForceSolid(true);
	
	skyBlue = new G4VisAttributes( G4Colour(135/255. , 206/255. ,  235/255. ));
	skyBlue -> SetVisibility(true);
	skyBlue -> SetForceSolid(true);		
}

//*******************************************************************************************
void OpenBeamLine::SetDefaultMaterials()
//-------------------------------------------------------------------------------------------
{
        nozzleMaterial -> DefineMaterials();
        Air       = nozzleMaterial -> GetMat("Air");
        Vacuum    = nozzleMaterial -> GetMat("Vacuum");
        Lead      = nozzleMaterial -> GetMat("Lead");
        Perspex   = nozzleMaterial -> GetMat("Perspex3");
        Water     = nozzleMaterial -> GetMat("Water");
}
//*******************************************************************************************
void OpenBeamLine::ConstructOpenBeamLine()
//-------------------------------------------------------------------------------------------

{ 
  // Treatment room (World volume)    
     const G4double worldX = 6.0 *m;
     const G4double worldY = 6.0 *m;
     const G4double worldZ = 14.0 *m;

     G4Box* treatmentRoom = new G4Box("TreatmentRoom",worldX,worldY,worldZ);
     G4LogicalVolume* logicTreatmentRoom = new G4LogicalVolume(treatmentRoom, Air, "logicTreatmentRoom", 0,0,0);
     physicalTreatmentRoom = new G4PVPlacement(0, G4ThreeVector(), "physicalTreatmentRoom", logicTreatmentRoom, 0,false,0);
     logicTreatmentRoom -> SetVisAttributes (G4VisAttributes::Invisible);
	
}



