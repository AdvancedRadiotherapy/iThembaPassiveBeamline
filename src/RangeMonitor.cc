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
// BeamMonitor.cc
// ----------------------------------------------------------------------------


#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "RangeMonitor.hh"
#include "NozzleMaterial.hh"
#include "G4Transform3D.hh"
#include "G4ios.hh"
#include <fstream>
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"


// *******************************************************************************************************************
RangeMonitor::RangeMonitor():physiMotherMod(0), logicSteelDisk(0),  logicOccludingRod(0),  logicMLFCmount(0),
logicOccludingRodMount(0), logicOccRod(0)
 					 
{
  nozzleMaterial  = new NozzleMaterial();
}
// *******************************************************************************************************************
RangeMonitor::~RangeMonitor() 
//--------------------------------------------------------------------------------------------------------------------
{
  delete nozzleMaterial;

}
// *******************************************************************************************************************
void RangeMonitor::BuildModulator(G4LogicalVolume* logicMotherMod)
//--------------------------------------------------------------------------------------------------------------------
{
  //G4Material* Air = nozzleMaterial -> GetMat("Air");
  //G4Material* Vacuum = nozzleMaterial -> GetMat("Vacuum");

    G4VisAttributes* vacuum = new G4VisAttributes( G4Colour(224/255., 223/255., 219/255.));
    vacuum  -> SetVisibility(false);            
    vacuum  -> SetForceSolid(false);

    G4Material* Brass = nozzleMaterial -> GetMat("Brass");
    G4VisAttributes* brass = new G4VisAttributes( G4Colour(181/255., 166/255., 66/255.));
    brass  -> SetVisibility(true);            
    brass  -> SetForceSolid(true);

    G4Material* Steel = nozzleMaterial -> GetMat("SS304");
    G4VisAttributes* steel = new G4VisAttributes( G4Colour(224/255., 223/255., 219/255.));
    steel  -> SetVisibility(true);            
    steel  -> SetForceSolid(true);
  /*
    G4Material* Aluminum = nozzleMaterial -> GetMat("Aluminum");
    G4VisAttributes* aluminum = new G4VisAttributes( G4Colour(235/255.,0/255.,0/255.));
    aluminum  -> SetVisibility(true);            
    aluminum  -> SetForceSolid(true);
  */
    G4Material* Lexan = nozzleMaterial -> GetMat("Lexan");
    G4VisAttributes* lexan = new G4VisAttributes( G4Colour(225/255., 190/255., 48/255.));
    lexan  -> SetVisibility(true);            
    lexan  -> SetForceSolid(true);

    G4Material* Copper = nozzleMaterial -> GetMat("Copper");
    G4VisAttributes* copper = new G4VisAttributes( G4Colour(208/255., 113/255., 49/255.));
    copper  -> SetVisibility(true);            
    copper  -> SetForceSolid(true);

  // L2 tool steel disk diameter 210 mm and thickness 0.65  
     G4double Z1=(-81.85/2-0.65/2)*mm;

     G4ThreeVector positionSteelDisk = G4ThreeVector(0*mm,0*mm,Z1);
     G4Tubs* steelDisk = new G4Tubs("SteelDisk", 0.0*mm, 210.0/2*mm, 0.65/2*mm,0 *deg,360*deg);
     logicSteelDisk = new G4LogicalVolume(steelDisk, Steel, "SteelDisk",0,0,0);
     new G4PVPlacement(0, positionSteelDisk, logicSteelDisk, "SteelDisk",logicMotherMod, false, 0);   
     logicSteelDisk -> SetVisAttributes(steel);

  // L2 tool steel raised MLFC mounting ring and energy degrader, intergral part of disk
  // Protrudes 4.35 mm from disk surface, outer diameter 72.22 mm, inner diameter 48.36 mm 
     G4double Z3=(-81.85/2+4.35/2)*mm;

     G4ThreeVector positionMLFCmount = G4ThreeVector(0*mm,0*mm,Z3);
     G4Tubs* mLFCmount = new G4Tubs("MLFCmount", 48.36/2*mm, 72.22/2*mm, 4.35/2*mm,0 *deg,360*deg);
     logicMLFCmount = new G4LogicalVolume(mLFCmount, Steel, "MLFCmount",0,0,0);
     new G4PVPlacement(0, positionMLFCmount, logicMLFCmount, "MLFCmount",logicMotherMod, false, 0);   
     logicMLFCmount -> SetVisAttributes(steel);


  // L2 tool steel raised occluding rod mounting platform (Protrudes 4.35 mm from disk surface, diameter 20 mm) 
     G4double Z2=(-81.85/2+4.35/2)*mm;

     G4ThreeVector positionOccludingRodMount = G4ThreeVector(0*mm,0*mm,Z2);
     G4Tubs* occludingRodMount = new G4Tubs("OccludingRodMount", 0.0*mm, 20.0/2*mm, 4.35/2*mm,0 *deg,360*deg);
     logicOccludingRodMount = new G4LogicalVolume(occludingRodMount, Steel, "OccludingRodMount",0,0,0);
     new G4PVPlacement(0, positionOccludingRodMount, logicOccludingRodMount, "OccludingRodMount",logicMotherMod, false, 0);   
     logicOccludingRodMount -> SetVisAttributes(steel);

  // Brass occluding rod with 4.35 mm deep recess in end to fit onto mounting platform
  // outer diameter 26.88 mm, inner diameter 20 mm 

     G4double Z4=(-81.85/2+4.35/2)*mm;

     G4ThreeVector positionOccludingRod = G4ThreeVector(0*mm,0*mm,Z4);
     G4Tubs* occludingRod = new G4Tubs("OccludingRod", 20.0/2*mm, 26.88/2*mm, 4.35/2*mm,0 *deg,360*deg);
     logicOccludingRod = new G4LogicalVolume(occludingRod, Brass, "OccludingRod",0,0,0);
     new G4PVPlacement(0, positionOccludingRod, logicOccludingRod, "OccludingRod",logicMotherMod, false, 0);   
     logicOccludingRod -> SetVisAttributes(brass);

     G4double Z5=(-81.85/2+4.35+77.5/2)*mm;

     G4ThreeVector positionOccRod = G4ThreeVector(0*mm,0*mm,Z5);
     G4Tubs* occRod = new G4Tubs("OccRod", 0.0*mm, 26.88/2*mm, 77.5/2*mm,0 *deg,360*deg);
     logicOccRod = new G4LogicalVolume(occRod, Brass, "OccRod",0,0,0);
     new G4PVPlacement(0, positionOccRod, logicOccRod, "OccRod",logicMotherMod, false, 0);   
     logicOccRod -> SetVisAttributes(brass);

  // Stack of alternating 1 mm thick Lexan (46) and 0.7 mm thick Cu (45) rings
  // Outer diameter 72.22 mm, inner diamter 48.36 mm, stack starts and ends with a Lexan ring

     G4double z6 = 0.0*mm;
     const G4int NbOfLexanRing=46;   
     G4double LexanThickness=1.0*mm;    
     
     G4ThreeVector* LexanRingPosition = new G4ThreeVector[NbOfLexanRing];
     for (G4int i = 0; i < NbOfLexanRing; i++) {
     z6 = -81.85/2+4.35 +1.0/2+(i*1.7);
     LexanRingPosition[i] = G4ThreeVector(0.0, 0.0, z6*mm); }
 
     G4Tubs* lexanRing= new G4Tubs("LexanRing",48.36/2*mm, 72.22/2*mm, LexanThickness/2, 0 *deg,360*deg);
     G4LogicalVolume* logicLexanRing = new G4LogicalVolume(lexanRing, Lexan,"LexanRing",0,0,0);
     for (G4int i = 0; i < NbOfLexanRing; i++) {
     new G4PVPlacement(0,LexanRingPosition[i], logicLexanRing, "LexanRing",logicMotherMod, false, i);} 
     logicLexanRing->SetVisAttributes(lexan);

     G4double z7 = 0.0*mm;
     const G4int NbOfCuRing=45;  
     G4double CuThickness=0.7*mm;    
  
     G4ThreeVector* CuRingPosition = new G4ThreeVector[NbOfCuRing];
     for (G4int i = 0; i < NbOfCuRing; i++) {
     z7 = -81.85/2+4.35 +1.0+0.7/2+(i*1.7);
     CuRingPosition[i] = G4ThreeVector(0.0, 0.0, z7*mm); }
 
     G4Tubs* cuRing= new G4Tubs("CuRing",48.36/2*mm, 72.22/2*mm, CuThickness/2, 0 *deg,360*deg);
     G4LogicalVolume* logicCuRing = new G4LogicalVolume(cuRing, Copper,"CuRing",0,0,0);
     for (G4int i = 0; i < NbOfCuRing; i++) {
     new G4PVPlacement(0,CuRingPosition[i], logicCuRing, "CuRing",logicMotherMod, false, i);} 
     logicCuRing->SetVisAttributes(copper);

  // Vacuum Chammber flange of 10 mm thick, inner diameter 160mm, outer diameter 210 mm
     
     // first chamber
     G4double Z6=(-81.85/2+10.0/2)*mm;

     G4ThreeVector positionFirstVacuumCham = G4ThreeVector(0*mm,0*mm,Z6);
     G4Tubs* firstVacuumCham = new G4Tubs("FirstVacuumCham", 160.0/2*mm, 210.0/2*mm, 10.0/2*mm,0 *deg,360*deg);
     G4LogicalVolume* logicFirstVacuumCham = new G4LogicalVolume(firstVacuumCham, Steel, "FirstVacuumCham",0,0,0);
     new G4PVPlacement(0, positionFirstVacuumCham, logicFirstVacuumCham, "FirstVacuumCham",logicMotherMod, false, 0);   
     logicFirstVacuumCham -> SetVisAttributes(steel);

     // Second chamber
     G4double Z7=(81.85/2-10.0/2)*mm;

     G4ThreeVector positionSecondVacuumCham = G4ThreeVector(0*mm,0*mm,Z7);
     G4Tubs* secondVacuumCham = new G4Tubs("SecondVacuumCham", 160.0/2*mm, 210.0/2*mm, 10.0/2*mm,0 *deg,360*deg);
     G4LogicalVolume* logicSecondVacuumCham = new G4LogicalVolume(secondVacuumCham, Steel, "SecondVacuumCham",0,0,0);
     new G4PVPlacement(0, positionSecondVacuumCham, logicSecondVacuumCham, "SecondVacuumCham",logicMotherMod, false, 0);   
     logicSecondVacuumCham -> SetVisAttributes(steel);

  // Vacuum Chammber Wall of 61.85 mm thick, inner diameter 160mm, outer diameter 170 mm
     
     G4double Z8=0.0*mm;

     G4ThreeVector positionVacuumChamWall = G4ThreeVector(0*mm,0*mm,Z8);
     G4Tubs* vacuumChamWall = new G4Tubs("VacuumChamWall", 160.0/2*mm, 170.0/2*mm, 61.85/2*mm,0 *deg,360*deg);
     G4LogicalVolume* logicVacuumChamWall = new G4LogicalVolume(vacuumChamWall, Steel, "VacuumChamWall",0,0,0);
     new G4PVPlacement(0, positionVacuumChamWall, logicVacuumChamWall, "VacuumChamWall",logicMotherMod, false, 0);   
     logicVacuumChamWall -> SetVisAttributes(steel);

  // L2 steel scattering plate and vacuum chamber wall 200 mm x 200 mm x 0.65 mm
     
     G4double Z9=(81.85/2+0.65/2)*mm;

     G4ThreeVector positionScattPlate = G4ThreeVector(0*mm,0*mm,Z9);
     G4Box* scattPlate = new G4Box("ScattPlate", 200.0/2 *mm, 200.0/2 *mm, 0.65/2 *mm);
     G4LogicalVolume* logicScattPlate = new G4LogicalVolume(scattPlate, Steel, "ScattPlate",0,0,0);
     new G4PVPlacement(0, positionScattPlate, logicScattPlate, "ScattPlate",logicMotherMod, false, 0);   
     logicScattPlate -> SetVisAttributes(steel);


}

