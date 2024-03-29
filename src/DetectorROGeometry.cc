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

#include "DetectorROGeometry.hh"
#include "DummySD.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"

/////////////////////////////////////////////////////////////////////////////
DetectorROGeometry::DetectorROGeometry(G4String aString,
								 G4ThreeVector detectorToWorldPosition,
								 G4double detectorDimX,
								 G4double detectorDimY,
								 G4double detectorDimZ,
								 G4int numberOfVoxelsX,
								 G4int numberOfVoxelsY,
								 G4int numberOfVoxelsZ):
   
  G4VReadOutGeometry(aString),
  detectorToWorldPosition(detectorToWorldPosition),
  detectorSizeX(detectorDimX),
  detectorSizeY(detectorDimY),
  detectorSizeZ(detectorDimZ),
  numberOfVoxelsAlongX(numberOfVoxelsX),
  numberOfVoxelsAlongY(numberOfVoxelsY),
  numberOfVoxelsAlongZ(numberOfVoxelsZ)
{
}

/////////////////////////////////////////////////////////////////////////////
DetectorROGeometry::~DetectorROGeometry()
{
}

/////////////////////////////////////////////////////////////////////////////
G4VPhysicalVolume* DetectorROGeometry::Build()
{
  // A dummy material is used to fill the volumes of the readout geometry.
  // (It will be allowed to set a NULL pointer in volumes of such virtual
  // division in future, since this material is irrelevant for tracking.)

  G4Material* dummyMat = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);

  G4double worldSizeX = 200.0 *cm;
  G4double worldSizeY = 200.0 *cm;
  G4double worldSizeZ = 200.0 *cm;

  G4double halfDetectorSizeX = detectorSizeX;
  G4double halfDetectorSizeY = detectorSizeY;
  G4double halfDetectorSizeZ = detectorSizeZ;

  // World volume of ROGeometry ...
  G4Box* ROWorld = new G4Box("ROWorld",
			     worldSizeX,
			     worldSizeY,
			     worldSizeZ);
  
  G4LogicalVolume* ROWorldLog = new G4LogicalVolume(ROWorld, dummyMat, 
						    "ROWorldLog", 0,0,0);
  
  G4VPhysicalVolume* ROWorldPhys = new G4PVPlacement(0,G4ThreeVector(), 
						     "ROWorldPhys", 
						     ROWorldLog, 
						     0,false,0);

  // Detector ROGeometry 
  G4Box *RODetector = new G4Box("RODetector", 
				halfDetectorSizeX, 
				halfDetectorSizeY, 
				halfDetectorSizeZ);

  G4LogicalVolume *RODetectorLog = new G4LogicalVolume(RODetector,
						       dummyMat,
						       "RODetectorLog",
						       0,0,0);
  
  G4VPhysicalVolume *RODetectorPhys = new G4PVPlacement(0,
							detectorToWorldPosition,
							"DetectorPhys",
							RODetectorLog,
							ROWorldPhys,
							false,0);
  
  
  // Division along X axis: the detector is divided in slices along the X axis
  G4double halfXVoxelSizeX = halfDetectorSizeX/numberOfVoxelsAlongX;
  G4double halfXVoxelSizeY = halfDetectorSizeY;
  G4double halfXVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelXThickness = 2*halfXVoxelSizeX;

  G4Box *RODetectorXDivision = new G4Box("RODetectorXDivision",
					 halfXVoxelSizeX,
					 halfXVoxelSizeY,
					 halfXVoxelSizeZ);
  
  G4LogicalVolume *RODetectorXDivisionLog = new G4LogicalVolume(RODetectorXDivision,
								dummyMat,
								"RODetectorXDivisionLog",
								0,0,0);

  G4VPhysicalVolume *RODetectorXDivisionPhys = new G4PVReplica("RODetectorXDivisionPhys",
							       RODetectorXDivisionLog,
							       RODetectorPhys,
							       kXAxis,
							       numberOfVoxelsAlongX,
							       voxelXThickness);

  // Division along Y axis: the slices along the X axis are divided along the Y axis

  G4double halfYVoxelSizeX = halfXVoxelSizeX;
  G4double halfYVoxelSizeY = halfDetectorSizeY/numberOfVoxelsAlongY;
  G4double halfYVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelYThickness = 2*halfYVoxelSizeY;

  G4Box *RODetectorYDivision = new G4Box("RODetectorYDivision",
					 halfYVoxelSizeX, 
					 halfYVoxelSizeY,
					 halfYVoxelSizeZ);

  G4LogicalVolume *RODetectorYDivisionLog = new G4LogicalVolume(RODetectorYDivision,
								dummyMat,
								"RODetectorYDivisionLog",
								0,0,0);
 
  G4VPhysicalVolume *RODetectorYDivisionPhys = new G4PVReplica("RODetectorYDivisionPhys",
							       RODetectorYDivisionLog,
							       RODetectorXDivisionPhys,
							       kYAxis,
							       numberOfVoxelsAlongY,
							       voxelYThickness);
  
  // Division along Z axis: the slices along the Y axis are divided along the Z axis

  G4double halfZVoxelSizeX = halfXVoxelSizeX;
  G4double halfZVoxelSizeY = halfYVoxelSizeY;
  G4double halfZVoxelSizeZ = halfDetectorSizeZ/numberOfVoxelsAlongZ;
  G4double voxelZThickness = 2*halfZVoxelSizeZ;
 
  G4Box *RODetectorZDivision = new G4Box("RODetectorZDivision",
					 halfZVoxelSizeX,
					 halfZVoxelSizeY, 
					 halfZVoxelSizeZ);
 
  G4LogicalVolume *RODetectorZDivisionLog = new G4LogicalVolume(RODetectorZDivision,
								dummyMat,
								"RODetectorZDivisionLog",
								0,0,0);
 
  RODetectorZDivisionPhys = new G4PVReplica("RODetectorZDivisionPhys",
					    RODetectorZDivisionLog,
					    RODetectorYDivisionPhys,
					    kZAxis,
					    numberOfVoxelsAlongZ,
					    voxelZThickness);

  DummySD *dummySD = new DummySD;
  RODetectorZDivisionLog -> SetSensitiveDetector(dummySD);

  return ROWorldPhys;
}



