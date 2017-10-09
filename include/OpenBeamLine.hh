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
	// OpenBeamLine.cc; 
	// 

#ifndef OpenBeamLine_H
#define OpenBeamLine_H 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

class G4VPhysicalVolume;
class DetectorConstruction;
class NozzleMaterial;

	//class OpenBeamLineBeamLineMessenger;

class OpenBeamLine : public G4VUserDetectorConstruction
{
public:
	
	//OpenBeamLineBeamLine(G4VPhysicalVolume*);
	OpenBeamLine();
	~OpenBeamLine();
	
	G4VPhysicalVolume* Construct();  
	void BeamLineSupport();
	

private:
	//passive proton line dimensions
	void SetDefaultDimensions(); 
	void ConstructOpenBeamLine();
        void SetDefaultMaterials();
        void SetDefaultColors();
        void Collimator();
        void ParallHoleCollimator();
        void PinHoleCollimator();
        void DetectorShielding();
	
	//OpenBeamLineBeamLineMessenger* passiveMessenger;  

	DetectorConstruction* detector;
        NozzleMaterial* nozzleMaterial; 
	
	G4VPhysicalVolume* physicalTreatmentRoom;
	G4VPhysicalVolume* physiBeamLineSupport; 
	G4VPhysicalVolume* physiBeamLineCover; 
	G4VPhysicalVolume* physiBeamLineCover2;
	
	G4VisAttributes* blue;
	G4VisAttributes* gray;
	G4VisAttributes* white;
	G4VisAttributes* red;
	G4VisAttributes* yellow;
	G4VisAttributes* green;
	G4VisAttributes* darkGreen;
	G4VisAttributes* darkOrange3;
	G4VisAttributes* skyBlue;
	
        G4Material* Air;
        G4Material* Vacuum;
        G4Material* Lead;
        G4Material* Perspex;
        G4Material* Water;
	
};
#endif

