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

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"

// **************************************************************************************
DetectorMessenger::DetectorMessenger(DetectorConstruction* detector)
:detector(detector)
//---------------------------------------------------------------------------------------
 
{
    changeThePhantomDir = new G4UIdirectory("/changePhantom/");
    changeThePhantomDir -> SetGuidance("Command to change the Phantom Size/position");

  // Change Phantom size
     changeThePhantomSizeCmd = new G4UIcmdWith3VectorAndUnit("/changePhantom/size", this);
     changeThePhantomSizeCmd -> SetGuidance("Insert sizes X Y and Z"
					 "\n   0 or negative values mean <<Don't change it!>>");
     changeThePhantomSizeCmd -> SetParameterName("PhantomSizeAlongX","PhantomSizeAlongY","PhantomSizeAlongZ", false);
     changeThePhantomSizeCmd -> SetDefaultUnit("mm");
     changeThePhantomSizeCmd -> SetUnitCandidates("nm um mm cm"); 
     changeThePhantomSizeCmd -> AvailableForStates(G4State_Idle);


  // Change Phantom Radious
     changeThePhantomRadiusCmd = new G4UIcmdWithADoubleAndUnit("/changePhantom/radius", this);
     changeThePhantomRadiusCmd -> SetGuidance("Insert radius");
     changeThePhantomRadiusCmd -> SetParameterName("PhantomRadius", false);
     changeThePhantomRadiusCmd -> SetDefaultUnit("cm");
     changeThePhantomRadiusCmd -> SetUnitCandidates("nm um mm cm"); 
     changeThePhantomRadiusCmd -> AvailableForStates(G4State_Idle);

  // Change Phantom Radious
     changeThePhantomZHalfCmd = new G4UIcmdWithADoubleAndUnit("/changePhantom/ZHalfLength", this);
     changeThePhantomZHalfCmd -> SetGuidance("Insert ZHalf");
     changeThePhantomZHalfCmd -> SetParameterName("phantomZHalfLength", false);
     changeThePhantomZHalfCmd -> SetDefaultUnit("cm");
     changeThePhantomZHalfCmd -> SetUnitCandidates("nm um mm cm"); 
     changeThePhantomZHalfCmd -> AvailableForStates(G4State_Idle);

  // Change Phantom material 
     changeThePhantomMaterialCmd = new G4UIcmdWithAString("/changePhantom/material", this);
     changeThePhantomMaterialCmd -> SetGuidance("Change the Phantom material"); 
     changeThePhantomMaterialCmd -> SetParameterName("PhantomMaterial", false);
     changeThePhantomMaterialCmd -> SetDefaultValue("Water");
     changeThePhantomMaterialCmd -> AvailableForStates(G4State_Idle);

  // Change Phantom 
     changeThePhantomCmd = new G4UIcmdWithAString("/changePhantom/Shape", this);
     changeThePhantomCmd -> SetGuidance("Change the Phantom"); 
     changeThePhantomCmd -> SetParameterName("phantomTub", false);
     changeThePhantomCmd -> SetDefaultValue("Clinder");
     changeThePhantomCmd -> AvailableForStates(G4State_Idle);

  // Change Phantom position
     changeThePhantomPositionCmd = new G4UIcmdWith3VectorAndUnit("/changePhantom/position", this);
     changeThePhantomPositionCmd -> SetGuidance("Insert X Y and Z dimensions for the position of the center of the Phantom"
					     " respect to that of the \"World\""); 
     changeThePhantomPositionCmd -> SetParameterName("PositionAlongX","PositionAlongY","PositionAlongZ", false);
     changeThePhantomPositionCmd -> SetDefaultUnit("mm");
     changeThePhantomPositionCmd -> SetUnitCandidates("um mm cm m"); 
     changeThePhantomPositionCmd -> AvailableForStates(G4State_Idle);
  
  // Update the whole Phantom/Detector Geometry
     changeTheUpdataDir = new G4UIdirectory("/change/");
     changeTheUpdataDir -> SetGuidance("Command to change the Phantom/Detector Size/position");

     updateCmd = new G4UIcmdWithoutParameter("/change/update",this);
     updateCmd->SetGuidance("Update Phantom/Detector geometry.");
     updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
     updateCmd->SetGuidance("if you changed geometrical value(s).");
     updateCmd->AvailableForStates(G4State_Idle);

  // Change detector size
     changeTheDetectorDir = new G4UIdirectory("/changeDetector/");
     changeTheDetectorDir -> SetGuidance("Command to change the Detector's Size/position/Voxels");
    
     changeTheDetectorSizeCmd = new G4UIcmdWith3VectorAndUnit("/changeDetector/size",this);
     changeTheDetectorSizeCmd -> SetGuidance("Insert sizes for X Y and Z dimensions of the Detector"
					  "\n   0 or negative values mean <<Don't change it>>");
     changeTheDetectorSizeCmd -> SetParameterName("DetectorSizeAlongX", "DetectorSizeAlongY", "DetectorSizeAlongZ", false);
     changeTheDetectorSizeCmd -> SetDefaultUnit("mm");
     changeTheDetectorSizeCmd -> SetUnitCandidates("nm um mm cm"); 
     changeTheDetectorSizeCmd -> AvailableForStates(G4State_Idle);

  // Change Phantom material 
     changeTheDetectorMaterialCmd = new G4UIcmdWithAString("/changeDetector/material", this);
     changeTheDetectorMaterialCmd -> SetGuidance("Change the detector material"); 
     changeTheDetectorMaterialCmd -> SetParameterName("DetectorMaterial", false);
     changeTheDetectorMaterialCmd -> SetDefaultValue("NaI");
     changeTheDetectorMaterialCmd -> AvailableForStates(G4State_Idle);

  // Change the detector position
     changeTheDetectorToPhantomPositionCmd = new G4UIcmdWith3VectorAndUnit("/changeDetector/position",this);
     changeTheDetectorToPhantomPositionCmd -> SetGuidance("Insert X Y and Z displacements between Detector and Phantom"
						       "\nNegative values mean <<Don't change it!>>"); 
     changeTheDetectorToPhantomPositionCmd -> SetParameterName("DisplacementAlongX","DisplacementAlongY","DisplacementAlongZ", false);
     changeTheDetectorToPhantomPositionCmd -> SetDefaultUnit("mm");
     changeTheDetectorToPhantomPositionCmd -> SetUnitCandidates("nm um mm cm"); 
     changeTheDetectorToPhantomPositionCmd -> AvailableForStates(G4State_Idle);
    
  // Change voxels by its size
     changeTheDetectorVoxelCmd = new G4UIcmdWith3VectorAndUnit("/changeDetector/voxelSize",this);
     changeTheDetectorVoxelCmd -> SetGuidance("Insert Voxel sizes for X Y and Z dimensions"
					   "\n   0 or negative values mean <<Don't change it!>>");
     changeTheDetectorVoxelCmd -> SetParameterName("VoxelSizeAlongX", "VoxelSizeAlongY", "VoxelSizeAlongZ", false);
     changeTheDetectorVoxelCmd -> SetDefaultUnit("mm");
     changeTheDetectorVoxelCmd -> SetUnitCandidates("nm um mm cm");
     changeTheDetectorVoxelCmd -> AvailableForStates(G4State_Idle);

     changeTheDetectorPosCmd = new G4UIcmdWithAString("/changeDetector/insidethephantom", this);
     changeTheDetectorPosCmd->SetGuidance("Choose whether inside or outside the Phantom");
     changeTheDetectorPosCmd->SetGuidance("either 'Yes' or 'No'");
     changeTheDetectorPosCmd->SetParameterName("MoveOutsidethePhantom", false);
     changeTheDetectorPosCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

}

// **************************************************************************************
DetectorMessenger::~DetectorMessenger()
//---------------------------------------------------------------------------------------
{
   delete changeThePhantomDir;
   delete changeTheUpdataDir; 
   delete changeThePhantomSizeCmd; 
   delete changeThePhantomRadiusCmd;
   delete changeThePhantomPositionCmd; 
   delete changeThePhantomMaterialCmd;
   delete changeThePhantomZHalfCmd;
   delete changeThePhantomCmd;
   delete updateCmd;
   delete changeTheDetectorDir; 
   delete changeTheDetectorSizeCmd;
   delete changeTheDetectorMaterialCmd; 
   delete changeTheDetectorToPhantomPositionCmd; 
   delete changeTheDetectorVoxelCmd; 
   delete changeTheDetectorPosCmd;

}

// **************************************************************************************
void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
//---------------------------------------------------------------------------------------
{	

    if( command == changeThePhantomSizeCmd){
      G4ThreeVector size = changeThePhantomSizeCmd -> GetNew3VectorValue(newValue);
      detector -> SetPhantomSize(size.getX(),size.getY(),size.getZ());

    }else if( command == changeThePhantomRadiusCmd){
      detector -> SetPhantomRadius(changeThePhantomRadiusCmd -> GetNewDoubleValue(newValue));

    }else if( command == changeThePhantomZHalfCmd){
      detector -> SetPhantomZHalfLength(changeThePhantomZHalfCmd -> GetNewDoubleValue(newValue));

    }else if (command == changeThePhantomPositionCmd ){
      G4ThreeVector size = changeThePhantomPositionCmd -> GetNew3VectorValue(newValue);
      detector -> SetPhantomPosition(size);
   
    }else if (command == changeThePhantomMaterialCmd){
      detector -> SetPhantomMaterial(newValue);

    }else if (command == changeThePhantomCmd){
      detector -> SetPhantom(newValue);

    }else if (command == changeTheDetectorMaterialCmd){
      detector -> SetDetectorMaterial(newValue);

    }else if (command == changeTheDetectorSizeCmd){
      G4ThreeVector size = changeTheDetectorSizeCmd  -> GetNew3VectorValue(newValue);
      detector -> SetDetectorSize(size.getX(),size.getY(),size.getZ());

    }else if (command == changeTheDetectorToPhantomPositionCmd){
      G4ThreeVector size = changeTheDetectorToPhantomPositionCmd-> GetNew3VectorValue(newValue);
      detector -> SetDetectorToPhantomPosition(size);

    }else if (command == changeTheDetectorVoxelCmd){
      G4ThreeVector size = changeTheDetectorVoxelCmd  -> GetNew3VectorValue(newValue);
      detector -> SetVoxelSize(size.getX(),size.getY(),size.getZ());

    }else if (command == updateCmd){
      detector -> UpdateGeometry();

    }else if( command == changeTheDetectorPosCmd ){
      detector->SetDetector(newValue);}

}



