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
// DetectorConstruction.hh; 
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy//
// or contact cirrone@lns.infn.it

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class DetectorROGeometry;
class DetectorMessenger;
class DetectorSD;
class Matrix;
class DetectorConstruction;
class NozzleMaterial;

class DetectorConstruction 

{
public:

  DetectorConstruction(G4VPhysicalVolume*);
  ~DetectorConstruction();


private: 

  void ConstructPhantom();
  void ConstructDetector();
  void ConstructSensitiveDetector(G4ThreeVector positionToWORLD);
  void ParametersCheck();
  DetectorConstruction();

public: 

  // Get detector position relative to WORLD
     inline G4ThreeVector GetDetectorToWorldPosition()
     {return detectorPosition;}

  // Get displacement phantom 
     inline G4ThreeVector GetDetectorToPhantomPosition()
     {return G4ThreeVector(detectorPosition.getX(),detectorPosition.getY(),detectorPosition.getZ());}

  // Calculate (and set) detector position by displacement, phantom and detector sizes
     inline void SetDetectorPosition()
     {
      detectorPosition.setX(detectorToPhantomPosition.getX());
      detectorPosition.setY(detectorToPhantomPosition.getY());
      detectorPosition.setZ(detectorToPhantomPosition.getZ());   
     }

 
  /////////////////////////////////////////////////////////////////////////////
    G4bool SetPhantomMaterial(G4String Pmaterial);
    G4bool SetDetectorMaterial(G4String dmaterial);
    void SetPhantomPosition(G4ThreeVector);
    void SetVoxelSize(G4double sizeX, G4double sizeY, G4double sizeZ);
    void SetDetectorSize(G4double sizeX, G4double sizeY, G4double sizeZ);
    void SetPhantomSize(G4double sizeX, G4double sizeY, G4double sizeZ);
    void SetPhantomRadius(G4double radius );
    void SetDetectorToPhantomPosition(G4ThreeVector DetectorToPhantomPosition);
    void UpdateGeometry();
    void PrintParameters();
    void SetPhantom(G4String phantomshape);
    void SetPhantomZHalfLength(G4double HalfLength);

    void  SetDetector(G4String name);
    void  SetDetectorCollimator(G4String vararg);
	
	void ConstructCalibrationSheet();
  
private:

    DetectorMessenger* detectorMessenger; 

    G4VisAttributes*   skyBlue;
    G4VisAttributes*   red;
    G4VisAttributes*   yellow;
    NozzleMaterial*    nozzleMaterial;
    Matrix*            matrix;

    G4VPhysicalVolume* motherPhys;

    DetectorSD*         detectorSD; 
    DetectorROGeometry* detectorROGeometry; 
    
    G4Box *phantom , *detector, *phantomWindowSolidVolume;
    G4Tubs *phantomTub;
    G4LogicalVolume *phantomLogicalVolume,*phantomTubLogicalVolume, *detectorLogicalVolume, *phantomWindowLogicalVolume, *logVolume; 
    G4VPhysicalVolume *phantomWindowPhysicalVolume, *phyVolume;
    G4VPhysicalVolume *phantomPhysicalVolume, *detectorPhysicalVolume;  
    G4double phantomSizeX; 
    G4double phantomSizeY; 
    G4double phantomSizeZ;

    G4double phantomRadius;
    G4double phantomZHalfLength;

    G4double detectorSizeX; 
    G4double detectorSizeY; 
    G4double detectorSizeZ;

	G4double calSheetSizeX;
	G4double calSheetSizeY;
	G4double calSheetSizeZ;
	G4Box* calSheet;
	G4LogicalVolume* calSheetLogicalVolume;
	G4VPhysicalVolume* calSheetPhysicalVolume;

    G4ThreeVector phantomPosition, detectorPosition, detectorToPhantomPosition; 
    G4double sizeOfVoxelAlongX; 
    G4double sizeOfVoxelAlongY; 
    G4double sizeOfVoxelAlongZ; 

    G4int numberOfVoxelsAlongX; 
    G4int numberOfVoxelsAlongY;
    G4int numberOfVoxelsAlongZ;  

    G4double volumeOfVoxel, massOfVoxel, voxelDensity;
    G4String voxelMaterialName;
    G4int totalVoxelsNumber;
    G4Material *phantomMaterial, *detectorMaterial, *phantomWindowMaterial;
    G4Material *Lung, *SoftTissue;
    G4Region* aRegion;
    G4Region* aaRegion;
    G4Region* PhRegion;
    G4Region* PhtubeRegion;
    G4String ppmaterial;
    G4String pphantomShape;
};
#endif
