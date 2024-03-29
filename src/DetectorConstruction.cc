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

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SubtractionSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "StepMax.hh"
#include "G4NistManager.hh"

#include "DetectorConstruction.hh"
#include "DetectorROGeometry.hh"
#include "DetectorMessenger.hh"
#include "DetectorSD.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "RootAnalysis.hh"
#include "NozzleMaterial.hh"
#include "RunAction.hh"
#include "PhantomAnalysis.hh"
#include "Matrix.hh"

#include "G4SystemOfUnits.hh"



#include <cmath>

//************************************************************************************************************
DetectorConstruction::DetectorConstruction(G4VPhysicalVolume* physicalTreatmentRoom)
  : matrix(0), motherPhys(physicalTreatmentRoom), detectorSD(0), detectorROGeometry(0), phantom(0), detector(0),  
    phantomLogicalVolume(0), phantomTubLogicalVolume(0), detectorLogicalVolume(0), phantomPhysicalVolume(0),
    detectorPhysicalVolume(0),aRegion(0),aaRegion(0)
// -----------------------------------------------------------------------------------------------------------
{
  // NOTE! that the DetectorConstruction class
  // does NOT inherit from G4VUserDetectorConstruction G4 class
  // So the Construct() mandatory virtual method is inside another geometric class
  // (like the passiveProtonBeamLIne, ...)

  // Messenger to change parameters of the phantom/detector geometry
     detectorMessenger = new DetectorMessenger(this);
     nozzleMaterial = new NozzleMaterial();

  // Define the materials of the experimental set-up
     nozzleMaterial -> DefineMaterials();  

  // Default detector voxels size
  // 200 slabs along the beam direction (X)
     sizeOfVoxelAlongX = 40*cm; 
     sizeOfVoxelAlongY = 40 *cm; 
     sizeOfVoxelAlongZ = 40 *cm; 
     phantomRadius    = 10 *cm;
     phantomZHalfLength= 15 *cm;

  // Define here the material of the water phantom and of the detector
     Lung = G4NistManager::Instance()->FindOrBuildMaterial("G4_LUNG_ICRP");
     SoftTissue = G4NistManager::Instance()->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");

     SetPhantomMaterial("Water"); 
     SetDetectorMaterial("NaI"); 
     SetDetectorSize(40.*cm, 40.*cm, 40.*cm);
     SetPhantomSize(40. *cm, 40. *cm, 40. *cm);
     SetPhantomPosition(G4ThreeVector(0. *cm, 0. *cm, 0. *cm));
     SetDetectorToPhantomPosition(G4ThreeVector(0. *cm, 0. *cm, 100. *cm));

	calSheetSizeX = 120*mm;
	calSheetSizeY = 120*mm;
	calSheetSizeZ = 0*mm;

  // Write virtual parameters to the real ones and check for consistency      
     UpdateGeometry();
        
}

//************************************************************************************************************
DetectorConstruction::~DetectorConstruction()
// -----------------------------------------------------------------------------------------------------------
{ 
  delete detectorROGeometry;  
  delete detectorMessenger;
  delete nozzleMaterial;
  delete matrix;  
}

void DetectorConstruction::ConstructCalibrationSheet()
{
	if(calSheetSizeZ>0){
	// calibration sheet infront of the detector
	calSheet = new G4Box("CalSheet", calSheetSizeX/2, calSheetSizeY/2, calSheetSizeZ/2);
	calSheetLogicalVolume = new G4LogicalVolume(calSheet, nozzleMaterial->GetMat("Perspex3"), "CalSheetLog");
	calSheetPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0,0,phantomPosition.getZ()-phantomSizeZ/2-5*cm-5*mm), "CalSheet", calSheetLogicalVolume, motherPhys, false, 0); 
	}
}

//************************************************************************************************************
void DetectorConstruction::ConstructPhantom()
// -----------------------------------------------------------------------------------------------------------
{


  // Definition of the solid volume of the Phantom
     phantom = new G4Box("Phantom", phantomSizeX/2, phantomSizeY/2, phantomSizeZ/2);
     phantomTub = new G4Tubs("PhantomTub", 0.0/2*cm, phantomRadius, phantomZHalfLength, 0, 360*deg);

  // Definition of the logical volume of the Phantom
     phantomLogicalVolume = new G4LogicalVolume(phantom, phantomMaterial,"phantomLog", 0, 0, 0);
     phantomTubLogicalVolume = new G4LogicalVolume(phantomTub, phantomMaterial,"phantomTubLog", 0, 0, 0);
  
  // Definition of the physics volume of the Phantom
     //phantomPhysicalVolume = new G4PVPlacement(0,phantomPosition,"phantomPhys",phantomLogicalVolume,motherPhys,false, 0);

  // Visualisation attributes of the phantom
     skyBlue = new G4VisAttributes( G4Colour(135/255. , 206/255. ,  235/255. ));
     skyBlue -> SetVisibility(true);
     skyBlue -> SetForceSolid(true);
     //skyBlue -> SetForceWireframe(true);
    // phantomLogicalVolume -> SetVisAttributes(skyBlue);

    if (!PhRegion)
       {
         PhRegion = new G4Region("phantom_Region");
         phantomLogicalVolume -> SetRegion(PhRegion);
         PhRegion -> AddRootLogicalVolume(phantomLogicalVolume);
       }

    if (!PhtubeRegion)
       {
         PhtubeRegion = new G4Region("phantomTub_Region");
         phantomTubLogicalVolume -> SetRegion(PhtubeRegion);
         PhtubeRegion -> AddRootLogicalVolume(phantomTubLogicalVolume);
       }

}

//************************************************************************************************************
void DetectorConstruction::ConstructDetector()
// -----------------------------------------------------------------------------------------------------------
{
	
  // Definition of the solid volume of the Detector
     detector = new G4Box("Detector", detectorSizeX/2, detectorSizeY/2, detectorSizeZ/2);
     detectorLogicalVolume = new G4LogicalVolume(detector,detectorMaterial,"DetectorLog", 0,0,0);
     // detectorPhysicalVolume = new G4PVPlacement(0, detectorPosition,"DetectorPhys", detectorLogicalVolume,motherPhys,false,0);

     red = new G4VisAttributes(G4Colour(255/255., 0/255. ,0/255.));
     red -> SetVisibility(true);
     red -> SetForceSolid(true);
    // red -> SetForceWireframe(true);
     detectorLogicalVolume -> SetVisAttributes(red);

  // Cut per Region, A smaller cut is fixed in the phantom to calculate the energy deposit with the required accuracy 
     if (!aRegion)
       {
         aRegion = new G4Region("Detector_Region");
         detectorLogicalVolume -> SetRegion(aRegion);
         aRegion -> AddRootLogicalVolume(detectorLogicalVolume);
       }

}

//************************************************************************************************************
void  DetectorConstruction::ConstructSensitiveDetector(G4ThreeVector detectorToWorldPosition)
// -----------------------------------------------------------------------------------------------------------
{  
  // Install new Sensitive Detector and ROGeometry which should be safe in C++ also if we have a NULL pointer
     delete detectorROGeometry; 
  // Sensitive Detector and ReadOut geometry definition
     G4SDManager* sensitiveDetectorManager = G4SDManager::GetSDMpointer();
     G4RunManager *runManager = G4RunManager::GetRunManager();
     nozzleMaterial -> DefineMaterials();  // Define the materials of the experimental set-up
     EventAction* evt = (EventAction*) runManager -> GetUserEventAction();
     G4String sensitiveDetectorName = "Detector"; 

  if (!detectorSD)
    {
      // The sensitive detector is instantiated
      detectorSD = new DetectorSD(sensitiveDetectorName, evt);
    }
  // The Read Out Geometry is instantiated
     static G4String ROGeometryName = "DetectorROGeometry";
     detectorROGeometry = new DetectorROGeometry(ROGeometryName,detectorToWorldPosition,
					          detectorSizeX/2,detectorSizeY/2,detectorSizeZ/2,
					             numberOfVoxelsAlongX, numberOfVoxelsAlongY,numberOfVoxelsAlongZ);

     G4cout << "Instantiating new Read Out Geometry \"" << ROGeometryName << "\""<< G4endl;

  // This will invoke Build() DetectorROGeometry virtual method 
     detectorROGeometry -> BuildROGeometry();

  // Attach ROGeometry to SDetector
     detectorSD -> SetROgeometry(detectorROGeometry);

     if (!sensitiveDetectorManager -> FindSensitiveDetector(sensitiveDetectorName, false))
     {
      G4cout << "Registering new DetectorSD \"" << sensitiveDetectorName << "\""<< G4endl;
      // Register user SD
      sensitiveDetectorManager -> AddNewDetector(detectorSD);
      // Attach SD to detector logical volume
      detectorLogicalVolume -> SetSensitiveDetector(detectorSD);
     }
}

//************************************************************************************************************
void  DetectorConstruction::ParametersCheck()
// -----------------------------------------------------------------------------------------------------------
{
  // Check Detector sizes respect to the voxel ones

  if ( detectorSizeX < sizeOfVoxelAlongX) {
      G4Exception("DetectorConstruction::ParametersCheck()",
		"Hadrontherapy0001", FatalException, 
		"Error:  Detector X size must be bigger or equal than that of Voxel X!");
  }
  if ( detectorSizeY < sizeOfVoxelAlongY) {
      G4Exception(" DetectorConstruction::ParametersCheck()",
		"Hadrontherapy0002", FatalException, 
		"Error:  Detector Y size must be bigger or equal than that of Voxel Y!");
  }
  if ( detectorSizeZ < sizeOfVoxelAlongZ) {
      G4Exception(" DetectorConstruction::ParametersCheck()", 
		"Hadrontherapy0003", FatalException,
		"Error:  Detector Z size must be bigger or equal than that of Voxel Z!");
  }

     G4cout << "                                   "<< G4endl;
     G4cout << "  Detector Geometry has been Successfully built !!!\n"; 
     G4cout << "                                   "<< G4endl;
}

//************************************************************************************************************
void DetectorConstruction::UpdateGeometry()
// -----------------------------------------------------------------------------------------------------------
{
      ParametersCheck();

      G4GeometryManager::GetInstance() -> OpenGeometry();

      if (phantom ||phantomTub){
      phantom -> SetXHalfLength(phantomSizeX/2);
      phantom -> SetYHalfLength(phantomSizeY/2);
      phantom -> SetZHalfLength(phantomSizeZ/2);
      phantomTub -> SetOuterRadius(phantomRadius);
      phantomTub -> SetZHalfLength(phantomZHalfLength);
      phantomPhysicalVolume -> SetTranslation(phantomPosition);

      }else ConstructPhantom();

	if(calSheet) {
		calSheet->SetXHalfLength(calSheetSizeX/2);
		calSheet->SetYHalfLength(calSheetSizeY/2);
		calSheet->SetZHalfLength(calSheetSizeZ/2);
		calSheetPhysicalVolume->SetTranslation(G4ThreeVector(0,0,phantomPosition.getZ()-phantomSizeZ/2-5*cm-5*mm));
	} else ConstructCalibrationSheet();


  // Set the detector 
      SetDetectorPosition();

      if (detector){

      detector -> SetXHalfLength(detectorSizeX/2);
      detector -> SetYHalfLength(detectorSizeY/2);
      detector -> SetZHalfLength(detectorSizeZ/2);
      detectorPhysicalVolume -> SetTranslation(detectorPosition);

      }else ConstructDetector();

  // Here there is the ricalculation of the number of voxels of detector
  // after the detector dimensions have been modifie
  // Round to nearest integer number of voxel 
     numberOfVoxelsAlongX = lrint(detectorSizeX / sizeOfVoxelAlongX);
     sizeOfVoxelAlongX = ( detectorSizeX / numberOfVoxelsAlongX );

     numberOfVoxelsAlongY = lrint(detectorSizeY / sizeOfVoxelAlongY);
     sizeOfVoxelAlongY = ( detectorSizeY / numberOfVoxelsAlongY );

     numberOfVoxelsAlongZ = lrint(detectorSizeZ / sizeOfVoxelAlongZ);
     sizeOfVoxelAlongZ = ( detectorSizeZ / numberOfVoxelsAlongZ );
 
     ConstructSensitiveDetector(GetDetectorToWorldPosition());

  // Calculation of the volume of each voxel
     volumeOfVoxel = (sizeOfVoxelAlongX * sizeOfVoxelAlongY * sizeOfVoxelAlongZ);
     voxelDensity =   (detectorMaterial -> GetDensity());
     voxelMaterialName =   detectorMaterial -> GetName(); 
     totalVoxelsNumber = numberOfVoxelsAlongX*numberOfVoxelsAlongY*numberOfVoxelsAlongZ;

  // Calculation of the mass of each voxel
     massOfVoxel = voxelDensity*volumeOfVoxel;

  // This will clear the existing matrix (together with all data inside it)! 
     matrix = Matrix::GetInstance(numberOfVoxelsAlongX,numberOfVoxelsAlongY,
					    numberOfVoxelsAlongZ, massOfVoxel);  

  // Inform the kernel about the new geometry
     G4RunManager::GetRunManager() -> GeometryHasBeenModified();
     G4RunManager::GetRunManager() -> PhysicsHasBeenModified();

     PrintParameters();


}

//************************************************************************************************************
// End of detector construction







// For Messangers

// Shield the detector (see DetectorShield.cc class)

//************************************************************************************************************
void DetectorConstruction::SetDetector(G4String name)
// -----------------------------------------------------------------------------------------------------------
{
     if (name =="Yes") phyVolume = phantomPhysicalVolume;
     else phyVolume=motherPhys;
     detectorPhysicalVolume = new G4PVPlacement(0, detectorPosition,"DetectorPhys", detectorLogicalVolume,phyVolume,false,0);
}

//************************************************************************************************************
void DetectorConstruction::SetPhantom(G4String phantomshape)
// -----------------------------------------------------------------------------------------------------------
{
    pphantomShape = phantomshape;

     if (pphantomShape == "Cylinder") logVolume = phantomTubLogicalVolume ;
     else  logVolume = phantomLogicalVolume;
     phantomPhysicalVolume = new G4PVPlacement(0,phantomPosition,"phantomPhys", logVolume, motherPhys,false, 0);
     phantomTubLogicalVolume -> SetVisAttributes(skyBlue);
     phantomLogicalVolume    -> SetVisAttributes(skyBlue);
}

//************************************************************************************************************
G4bool DetectorConstruction::SetPhantomMaterial(G4String Pmaterial)
// -----------------------------------------------------------------------------------------------------------
{  
      G4Material* pMat = nozzleMaterial->GetMat(Pmaterial);
      phantomMaterial  = pMat;
      ppmaterial=Pmaterial;

      if ( phantomLogicalVolume) 
	{
	  phantomLogicalVolume ->  SetMaterial(pMat);
	  G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
	  G4RunManager::GetRunManager() -> GeometryHasBeenModified();

          G4cout << "                                   "<< G4endl;
          G4cout << "  The Phantom material has been changed to " << Pmaterial <<" !!! " <<G4endl;
          G4cout << "                                   "<< G4endl;
	}  

       if (phantomTubLogicalVolume) 
	{
	  phantomTubLogicalVolume ->  SetMaterial(pMat);
	  G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
	  G4RunManager::GetRunManager() -> GeometryHasBeenModified();

          G4cout << "                                   "<< G4endl;
          G4cout << "  The Phantom material has been changed to " << Pmaterial <<" !!! " <<G4endl;
          G4cout << "                                   "<< G4endl;
	} 
    else
    {
      G4cout << "                                   "<< G4endl;
      G4cout << "WARNING: material \"" << Pmaterial << "\" doesn't exist in defind material list" << G4endl; 
      G4cout << "Check NozzleMaterial.cc" << G4endl; 
      G4cout << "                                   "<< G4endl;
      return false;
    }
  return true;
}
//************************************************************************************************************
G4bool DetectorConstruction::SetDetectorMaterial(G4String dmaterial)
// -----------------------------------------------------------------------------------------------------------
{  

     G4Material* dMat = nozzleMaterial->GetMat(dmaterial);
     detectorMaterial = dMat;

        if (detectorLogicalVolume) 
	{
	  detectorLogicalVolume -> SetMaterial(dMat); 
	  G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
	  G4RunManager::GetRunManager() -> GeometryHasBeenModified();
          G4cout << "                                   "<< G4endl;
          G4cout << "  The Detector material has been changed to " << dmaterial <<" !!! " <<G4endl;
          G4cout << "                                   "<< G4endl;
	}
    
  else
    {
      G4cout << "                                   "<< G4endl;
      G4cout << "WARNING: material \"" << dmaterial << "\" doesn't exist in defind material list" << G4endl; 
      G4cout << "Check NozzleMaterial.cc" << G4endl; 
      G4cout << "                                   "<< G4endl;
      return false;
    }
  return true;
}

//************************************************************************************************************
void DetectorConstruction::SetPhantomSize(G4double sizeX, G4double sizeY, G4double sizeZ)
// -----------------------------------------------------------------------------------------------------------
{
  if (sizeX > 0.) phantomSizeX = sizeX;
  if (sizeY > 0.) phantomSizeY = sizeY;
  if (sizeZ > 0.) phantomSizeZ = sizeZ;
}

//************************************************************************************************************
void DetectorConstruction::SetPhantomRadius(G4double radius)
// -----------------------------------------------------------------------------------------------------------
{
  if (radius > 0.) phantomRadius = radius;
}

//************************************************************************************************************
void DetectorConstruction::SetPhantomZHalfLength(G4double HalfLength)
// -----------------------------------------------------------------------------------------------------------
{
  if (HalfLength > 0.) phantomZHalfLength = HalfLength;
}

//************************************************************************************************************
void DetectorConstruction::SetDetectorSize(G4double sizeX, G4double sizeY, G4double sizeZ)
// -----------------------------------------------------------------------------------------------------------
{
  if (sizeX > 0.) {detectorSizeX = sizeX;}
  if (sizeY > 0.) {detectorSizeY = sizeY;}
  if (sizeZ > 0.) {detectorSizeZ = sizeZ;}
  SetVoxelSize(sizeOfVoxelAlongX, sizeOfVoxelAlongY, sizeOfVoxelAlongZ);
}

//************************************************************************************************************
void DetectorConstruction::SetVoxelSize(G4double sizeX, G4double sizeY, G4double sizeZ)
// -----------------------------------------------------------------------------------------------------------
{
  if (sizeX > 0.) {sizeOfVoxelAlongX = sizeX;}
  if (sizeY > 0.) {sizeOfVoxelAlongY = sizeY;}
  if (sizeZ > 0.) {sizeOfVoxelAlongZ = sizeZ;}
}

//************************************************************************************************************
void DetectorConstruction::SetPhantomPosition(G4ThreeVector pos)
// -----------------------------------------------------------------------------------------------------------
{
  phantomPosition = pos;
}


//************************************************************************************************************
void DetectorConstruction::SetDetectorToPhantomPosition(G4ThreeVector displacement)
// -----------------------------------------------------------------------------------------------------------
{
  detectorToPhantomPosition = displacement;
}

//************************************************************************************************************
void DetectorConstruction::PrintParameters()
// -----------------------------------------------------------------------------------------------------------
{

  G4cout << "  __________________________________"<< G4endl;
  G4cout << "                                   "<< G4endl;
  G4cout << "            Phantom Size "<< G4endl;
  G4cout << "  __________________________________"<< G4endl;
  G4cout << "                                   "<< G4endl;
  G4cout << "   Phantom Material          : "<< phantomMaterial-> GetName() << G4endl;
  G4cout << "   Phantom Density           : "<< (phantomMaterial-> GetDensity())/(g/cm3)<<" g/cm3 " << G4endl;
  G4cout << "                                    "<< G4endl;
  if (pphantomShape == "Cylinder"){
  G4cout << "   Phantom Radius            : "<< G4BestUnit( phantomTub -> GetOuterRadius(), "Length") << G4endl;
  G4cout << "   Phantom ZSize             : "<< G4BestUnit( phantomTub -> GetZHalfLength(), "Length")  << G4endl;
  }else{
  G4cout << "   Phantom Size X            : "<< G4BestUnit( phantom -> GetXHalfLength()*2., "Length") << G4endl;
  G4cout << "   Phantom Size Y            : "<< G4BestUnit( phantom -> GetYHalfLength()*2., "Length") << G4endl;
  G4cout << "   Phantom Size Z            : "<< G4BestUnit( phantom -> GetZHalfLength()*2., "Length")  << G4endl;
  }
  G4cout << "                                    "<< G4endl;
  G4cout << "   Displacement from Centre  "<< G4endl;
  G4cout << "   In X direction            : "<<G4BestUnit(phantomPosition.getX(),"Length")<< G4endl;
  G4cout << "   In Y direction            : "<<G4BestUnit(phantomPosition.getY(),"Length")<< G4endl;
  G4cout << "   In Z direction            : "<<G4BestUnit(phantomPosition.getZ(),"Length") << G4endl;
  G4cout << "  __________________________________"<< G4endl;
  G4cout << "                                   "<< G4endl;
  G4cout << "         Detector information"           << G4endl;
  G4cout << "  __________________________________"<< G4endl;
  G4cout << "                              "<< G4endl;
  G4cout << "   Detector Size X           : "<<G4BestUnit( detector -> GetXHalfLength()*2., "Length")<< G4endl;
  G4cout << "   Detector Size Y           : "<<G4BestUnit( detector -> GetYHalfLength()*2., "Length")<< G4endl;
  G4cout << "   Detector Size Z           : "<<G4BestUnit( detector -> GetZHalfLength()*2., "Length")<< G4endl;
  G4cout << "                                    "<< G4endl;
  G4cout << "   Number of Voxels along X  : "<< numberOfVoxelsAlongX << G4endl;
  G4cout << "   Number of Voxels along Y  : "<< numberOfVoxelsAlongY << G4endl;
  G4cout << "   Number of Voxels along Z  : "<< numberOfVoxelsAlongZ << G4endl;
  G4cout << "                                    "<< G4endl;
  G4cout << "   X sizes of the Voxels     : "<< G4BestUnit(sizeOfVoxelAlongX, "Length") << G4endl;
  G4cout << "   Y sizes of the Voxels     : "<< G4BestUnit(sizeOfVoxelAlongY, "Length") << G4endl;
  G4cout << "   Z sizes of the Voxels     : "<< G4BestUnit(sizeOfVoxelAlongZ, "Length") << G4endl;
  G4cout << "   Number of Voxels (Total)  : "<< totalVoxelsNumber << G4endl;
  G4cout << "                                    "<< G4endl;
  G4cout << "   Voxel Material            : "<< voxelMaterialName << G4endl;
  G4cout << "   Voxel Volume              : "<<volumeOfVoxel/cm3<<" cm3 "<< G4endl;
  G4cout << "   Voxel Mass                : "<<massOfVoxel/g<<" g "<< G4endl;
  G4cout << "   Voxel Density             : "<<voxelDensity/(g/cm3)<<" g/cm3 "<< G4endl;
  G4cout << "                                    "<< G4endl;
  G4cout << "   Displacement from Centre  "<< G4endl;
  G4cout << "   In X direction            : "<<G4BestUnit(detectorToPhantomPosition.getX(),"Length")<< G4endl;
  G4cout << "   In Y direction            : "<<G4BestUnit(detectorToPhantomPosition.getY(),"Length")<< G4endl;
  G4cout << "   In Z direction            : "<<G4BestUnit(detectorToPhantomPosition.getZ(),"Length")<< G4endl;
  G4cout << "  __________________________________"<< G4endl;
  G4cout << "                                    "<< G4endl;


// send Phatom geometrical informations to the Root
   
     RootAnalysis* analysis = RootAnalysis::getInstance();
     if (pphantomShape == "Cylinder"){
     analysis -> PhantomGeometricalCharacteristics( phantomTub -> GetOuterRadius()*2./mm, phantomTub -> GetOuterRadius()*2./mm, 
                                                    phantomTub -> GetZHalfLength()*2./mm);
     }else {
     analysis -> PhantomGeometricalCharacteristics( phantom -> GetXHalfLength()*2./mm, phantom -> GetYHalfLength()*2./mm, 
                                                     phantom -> GetZHalfLength()*2./mm);}

     PhantomAnalysis* PA = PhantomAnalysis::GetPhantomAnalysis();
     PA-> TargetMaterial(phantomMaterial,phantom -> GetZHalfLength()*2./mm);


}


