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
// ----------------------------------------------------------------------------
//                 GEANT 4 - Hadrontherapy example
// ----------------------------------------------------------------------------
// Code developed by:
//
// G.A.P. Cirrone(a)*, F. Di Rosa(a), S. Guatelli(b), G. Russo(a)
// 
// (a) Laboratori Nazionali del Sud 
//     of the National Institute for Nuclear Physics, Catania, Italy
// (b) National Institute for Nuclear Physics Section of Genova, genova, Italy
// 
// * cirrone@lns.infn.it
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
#include "Modulator37.hh"
#include "NozzleMaterial.hh"
#include "G4Transform3D.hh"
#include "G4ios.hh"
#include <fstream>
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

// *******************************************************************************************************************
Modulator37::Modulator37():physiMotherMod(0),    logicColler(0),
						 solidMod0(0),         logicMod0(0),          physiMod0(0),
						 solidMod1(0),         logicMod1(0),          physiMod1(0),
						 solidMod2(0),         logicMod2(0),          physiMod2(0),
						 solidMod3(0),         logicMod3(0),          physiMod3(0),
						 solidMod4(0),         logicMod4(0),          physiMod4(0),
						 solidMod5(0),         logicMod5(0),          physiMod5(0),
						 solidMod6(0),         logicMod6(0),          physiMod6(0),
						 //solidMod7(0),         logicMod7(0),          physiMod7(0),
						 solidMod20(0),        logicMod20(0),         physiMod20(0),
						 solidMod21(0),        logicMod21(0),         physiMod21(0),
						 solidMod22(0),        logicMod22(0),         physiMod22(0),
						 solidMod23(0),        logicMod23(0),         physiMod23(0),
						 solidMod24(0),        logicMod24(0),         physiMod24(0),
						 solidMod25(0),        logicMod25(0),         physiMod25(0),
						 solidMod26(0),        logicMod26(0),         physiMod26(0),
						 //solidMod27(0),        logicMod27(0),         physiMod27(0),
						 solidMod30(0),        logicMod30(0),         physiMod30(0),
						 solidMod31(0),        logicMod31(0),         physiMod31(0),
						 solidMod32(0),        logicMod32(0),         physiMod32(0),
						 solidMod33(0),        logicMod33(0),         physiMod33(0),
						 solidMod34(0),        logicMod34(0),         physiMod34(0),
						 solidMod35(0),        logicMod35(0),         physiMod35(0),
						 solidMod36(0),        logicMod36(0),         physiMod36(0),
						 //solidMod37(0),        logicMod37(0),         physiMod37(0),
						 solidMod40(0),        logicMod40(0),         physiMod40(0),
						 solidMod41(0),        logicMod41(0),         physiMod41(0),
						 solidMod42(0),        logicMod42(0),         physiMod42(0),
						 solidMod43(0),        logicMod43(0),         physiMod43(0),
						 solidMod44(0),        logicMod44(0),         physiMod44(0),
						 solidMod45(0),        logicMod45(0),         physiMod45(0),
						 solidMod46(0),        logicMod46(0),         physiMod46(0)
						// solidMod47(0),        logicMod47(0),         physiMod47(0),
						 
{
  nozzleMaterial  = new NozzleMaterial();
  rm = new G4RotationMatrix(); 
  G4double phi = 0. *deg;     
  rm -> rotateY(phi); 
}
// *******************************************************************************************************************
Modulator37::~Modulator37() 
//--------------------------------------------------------------------------------------------------------------------
{
  delete rm;
  delete nozzleMaterial;
}
// *******************************************************************************************************************
void Modulator37::BuildModulator(G4VPhysicalVolume* motherVolume)
//--------------------------------------------------------------------------------------------------------------------
{
    Air = nozzleMaterial -> GetMat("Air");
    G4Material* ModMater = nozzleMaterial -> GetMat("Perspex3");
    G4Material* CollerMater = nozzleMaterial -> GetMat("Aluminum");

    G4VisAttributes* aluminum = new G4VisAttributes( G4Colour(235/255.,0/255.,0/255.));
    aluminum   -> SetVisibility(true);            
    aluminum  -> SetForceSolid(true);


    G4double innerRadiusOfEachBlade  = 45 *mm;
    G4double outerRadiusOfEachBlade  = 150 *mm;
    G4double thicknessOfEachBlade  = 5.0*mm;

  // Mother of the modulator wheel  
     G4ThreeVector positionMotherMod = G4ThreeVector(0. *mm, 0. *mm, 0. *mm);
     G4Box* solidMotherMod = new G4Box("MotherMod", 15.0 *cm, 15.0 *cm, 5.0 *cm);
     G4LogicalVolume * logicMotherMod = new G4LogicalVolume(solidMotherMod, Air,"MotherMod",0,0,0);
     physiMotherMod = new G4PVPlacement(rm,positionMotherMod,  "MotherMod", logicMotherMod, motherVolume, false,0);              
 
  // central metal collar ring: inner 22, outer 45 mm

    G4ThreeVector positionColler = G4ThreeVector(0*mm,0*mm,19.0*mm);
    G4Tubs* solidColler = new G4Tubs("Coller", 22.0*mm, 45.0*mm, 49/2*mm,	 0 *deg,  360*deg);
    logicColler = new G4LogicalVolume(solidColler, CollerMater, "Coller",0,0,0);
    new G4PVPlacement(0, positionColler, logicColler, "Coller",logicMotherMod, false, 0);   
    logicColler -> SetVisAttributes(aluminum);

//----------------------------------------------------------
// Mother volume of first quarter of the modulator 
//----------------------------------------------------------

  G4double hightOfMotherTube = 43.5 *mm;
  G4double startAngleOfTheMotherTube  = 45 *deg;
  G4double spanningAngleOfTheMotherTube  = 90 *deg;
  
  G4RotationMatrix rm2;
  rm2.rotateZ(0 *deg);
 
  G4ThreeVector positionMod0 = G4ThreeVector(0*mm,0*mm,0*mm);  
  solidMod0 = new G4Tubs("Mod0",
			 innerRadiusOfEachBlade , 
			 outerRadiusOfEachBlade ,
			 hightOfMotherTube,
			 startAngleOfTheMotherTube , 
			 spanningAngleOfTheMotherTube );
  
  logicMod0 = new G4LogicalVolume(solidMod0, Air, "Mod0",0,0,0);  
  physiMod0 = new G4PVPlacement(G4Transform3D(rm2, positionMod0), 
				logicMod0,"Mod0",logicMotherMod,false,0);            
 
//----------------------------------------------------------
// First modulator slice (1st quarter)
//----------------------------------------------------------
 
  G4double startAngleOfTheTube1 = (45.0+17.245)*deg;
  G4double spanningAngleOfTheTube1 = 55.51*deg;
 
  G4ThreeVector positionMod1 = G4ThreeVector(0*mm,0*mm,41.0*mm);
  solidMod1 = new G4Tubs("Mod1",
			 innerRadiusOfEachBlade , 
			 outerRadiusOfEachBlade ,
			 thicknessOfEachBlade ,
			 startAngleOfTheTube1, 
			 spanningAngleOfTheTube1);
			       
  logicMod1 = new G4LogicalVolume(solidMod1, ModMater, "Mod1",0,0,0);
  physiMod1 = new G4PVPlacement(0, positionMod1, logicMod1, "Mod1",logicMod0, false, 0);            				      
				      
//----------------------------------------------------------
// Second modulator slice (1st quarter)
//----------------------------------------------------------
  
  G4double startAngleOfTheTube2 = (45.0+17.245+7.32)*deg;
  G4double spanningAngleOfTheTube2 = 40.87*deg;

  G4ThreeVector positionMod2 = G4ThreeVector(0*mm,0*mm,36.0*mm);
  solidMod2 = new G4Tubs("Mod2",
			 innerRadiusOfEachBlade , 
			 outerRadiusOfEachBlade ,
			 thicknessOfEachBlade ,
			 startAngleOfTheTube2, 
			 spanningAngleOfTheTube2);

  logicMod2 = new G4LogicalVolume(solidMod2, ModMater, "Mod2",0,0,0);
  physiMod2 = new G4PVPlacement(0,positionMod2, logicMod2, "Mod2", logicMod0, false, 0);            

//----------------------------------------------------------
// 3rd modulator slice (1st quarter)
//----------------------------------------------------------
 
  G4double startAngleOfTheTube3 = (45.0+17.245+7.32+5.37)*deg;
  G4double spanningAngleOfTheTube3 = 30.13*deg;
   
  G4ThreeVector positionMod3 = G4ThreeVector(0*mm,0*mm,31.0*mm);
  solidMod3 = new G4Tubs("Mod3",
			 innerRadiusOfEachBlade , 
			 outerRadiusOfEachBlade ,
			 thicknessOfEachBlade ,
			 startAngleOfTheTube3, 
			 spanningAngleOfTheTube3);

  logicMod3 = new G4LogicalVolume(solidMod3, ModMater, "Mod3",0,0,0);
  physiMod3 = new G4PVPlacement(0, positionMod3, logicMod3,  "Mod3",logicMod0, false,0);            

//----------------------------------------------------------
// 4th modulator slice (1st quarter)
//----------------------------------------------------------
 
  G4double startAngleOfTheTube4 = (45.0+17.245+7.32+5.37+4.42)*deg;
  G4double spanningAngleOfTheTube4 = 21.29*deg;
      
  G4ThreeVector positionMod4 = G4ThreeVector(0*mm,0*mm,26*mm);
  solidMod4 = new G4Tubs("Mod4",
			 innerRadiusOfEachBlade , 
			 outerRadiusOfEachBlade ,
			 thicknessOfEachBlade ,
			 startAngleOfTheTube4, 
			 spanningAngleOfTheTube4);

  logicMod4 = new G4LogicalVolume(solidMod4, ModMater, "Mod4",0,0,0);
  physiMod4 = new G4PVPlacement(0, positionMod4, logicMod4,"Mod4", logicMod0,false,0);              

//----------------------------------------------------------
// 5th modulator slice (1st quarter)
//----------------------------------------------------------
 
  G4double startAngleOfTheTube5 = (45.0+17.245+7.32+5.37+4.42+3.9)*deg;
  G4double spanningAngleOfTheTube5 = 13.49*deg;
      
  G4ThreeVector positionMod5 = G4ThreeVector(0*mm,0*mm,21.0*mm);
  solidMod5 = new G4Tubs("Mod5",
			 innerRadiusOfEachBlade , 
			 outerRadiusOfEachBlade ,
			 thicknessOfEachBlade ,
			 startAngleOfTheTube5, 
			 spanningAngleOfTheTube5);

  logicMod5 = new G4LogicalVolume(solidMod5, ModMater, "Mod5",0,0,0);
  physiMod5 = new G4PVPlacement(0, positionMod5, logicMod5, "Mod5", logicMod0, false,  0);             
  
//----------------------------------------------------------
// 6th modulator slice (1st quarter)
//----------------------------------------------------------
 
  G4double startAngleOfTheTube6 = (45.0+17.245+7.32+5.37+4.42+3.9+3.42)*deg;    
  G4double spanningAngleOfTheTube6 =    6.65*deg;  
      
  G4ThreeVector positionMod6 = G4ThreeVector(0*mm,0*mm,16.0*mm);
  solidMod6 = new G4Tubs("Mod6",
			 innerRadiusOfEachBlade , 
			 outerRadiusOfEachBlade ,
			 thicknessOfEachBlade ,
			 startAngleOfTheTube6, 
			 spanningAngleOfTheTube6);

  logicMod6 = new G4LogicalVolume(solidMod6, ModMater, "Mod6",0,0,0);
  physiMod6 = new G4PVPlacement(0,positionMod6, logicMod6, "Mod6", logicMod0,false,0);              

//----------------------------------------------------------
// Mother volume of the second modulator quarter
//----------------------------------------------------------
      
  G4RotationMatrix rm20;
  rm20.rotateZ(90 *deg);
  
  G4ThreeVector positionMod20 = G4ThreeVector(0*cm,0*cm,0*cm);  
  solidMod20 = new G4Tubs("Mod20",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  hightOfMotherTube,
			  startAngleOfTheMotherTube , 
			  spanningAngleOfTheMotherTube );
  
  logicMod20 = new G4LogicalVolume(solidMod20, Air, "Mod0",0,0,0);    
  physiMod20 = new G4PVPlacement(G4Transform3D(rm20, positionMod20), 
				 logicMod20,"Mod20",logicMotherMod,false,0);            
 
//----------------------------------------------------------
// 1st modulator slice (2nd quarter)
//----------------------------------------------------------

  G4ThreeVector positionMod21 = G4ThreeVector(0*mm,0*mm,41.*mm);
  solidMod21 = new G4Tubs("Mod21",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube1, 
			  spanningAngleOfTheTube1);
  
  logicMod21 = new G4LogicalVolume(solidMod21, ModMater, "Mod21",0,0,0);  
  physiMod21 = new G4PVPlacement(0, positionMod21, logicMod21, "Mod21", logicMod20, false, 0);              
    
//----------------------------------------------------------
// 2nd modulator slice (2nd quarter)
//----------------------------------------------------------
  
  G4ThreeVector positionMod22 = G4ThreeVector(0*mm,0*mm,36.0*mm); 
  solidMod22 = new G4Tubs("Mod22",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube2, 
			  spanningAngleOfTheTube2);
  
  logicMod22 = new G4LogicalVolume(solidMod22, ModMater, "Mod22",0,0,0);  
  physiMod22 = new G4PVPlacement(0, positionMod22, logicMod22, "Mod22", logicMod20, false, 0);              
    
//----------------------------------------------------------
// 3rd modulator slice (2nd quarter)
//----------------------------------------------------------
 
  G4ThreeVector positionMod23 = G4ThreeVector(0*mm,0*mm,31.0*mm);
  solidMod23 = new G4Tubs("Mod23",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube3, 
			  spanningAngleOfTheTube3);

  logicMod23 = new G4LogicalVolume(solidMod23, ModMater, "Mod23",0,0,0);
  physiMod23 = new G4PVPlacement(0,positionMod23,logicMod23,"Mod23",logicMod20, false,0);              
 
//----------------------------------------------------------
// 4th modulator slice (2nd quarter)
//----------------------------------------------------------
      
  G4ThreeVector positionMod24 = G4ThreeVector(0*mm,0*mm,26.0*mm);
  solidMod24 = new G4Tubs("Mod24",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube4, 
			  spanningAngleOfTheTube4);

  logicMod24 = new G4LogicalVolume(solidMod24, ModMater, "Mod24",0,0,0); 
  physiMod24 = new G4PVPlacement(0,positionMod24,logicMod24,"Mod24", logicMod20,false,0);              

//----------------------------------------------------------
// 5th modulator slice (2nd quarter)
//----------------------------------------------------------
   
  G4ThreeVector positionMod25 = G4ThreeVector(0*mm,0*mm,21.0*mm);
  solidMod25 = new G4Tubs("Mod25",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube5, 
			  spanningAngleOfTheTube5);
  
  logicMod25 = new G4LogicalVolume(solidMod25, ModMater, "Mod25",0,0,0);
  physiMod25 = new G4PVPlacement(0,positionMod25,logicMod25, "Mod25",logicMod20,false,0);              
 
//----------------------------------------------------------
// 6th modulator slice (2nd quarter)
//----------------------------------------------------------
    
  G4ThreeVector positionMod26 = G4ThreeVector(0*mm,0*mm,16.0*mm);
  solidMod26 = new G4Tubs("Mod26",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube6, 
			  spanningAngleOfTheTube6);

  logicMod26 = new G4LogicalVolume(solidMod26, ModMater, "Mod26",0,0,0);
  physiMod26 = new G4PVPlacement(0,positionMod26, logicMod26, "Mod26", logicMod20, false, 0);             

//----------------------------------------------------------
// Mother volume of the Third modulator quarter
//----------------------------------------------------------
      
  G4RotationMatrix rm30;
  rm30.rotateZ(180 *deg);
  
  G4ThreeVector positionMod30 = G4ThreeVector(0*cm,0*cm,0*cm);
  solidMod30 = new G4Tubs("Mod30",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  hightOfMotherTube,
			  startAngleOfTheMotherTube , 
			  spanningAngleOfTheMotherTube );
  
  logicMod30 = new G4LogicalVolume(solidMod30, Air, "Mod0",0,0,0); 
  physiMod30 = new G4PVPlacement(G4Transform3D(rm30, positionMod30), 
				 logicMod30,    
				 "Mod30",       
				 logicMotherMod, 
				 false,         
				 0);            
  
//----------------------------------------------------------
// 1st modulator slice (3rd quarter)
//----------------------------------------------------------

  G4ThreeVector positionMod31 = G4ThreeVector(0*mm,0*mm,41.*mm);
  solidMod31 = new G4Tubs("Mod31",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube1, 
			  spanningAngleOfTheTube1);
  
  logicMod31 = new G4LogicalVolume(solidMod31, ModMater, "Mod31",0,0,0);  
  physiMod31 = new G4PVPlacement(0,positionMod31, logicMod31,  "Mod31", logicMod30,false, 0);              
    
//----------------------------------------------------------
// 2nd modulator slice (3rd quarter)
//----------------------------------------------------------
  
  G4ThreeVector positionMod32 = G4ThreeVector(0*mm,0*mm,36.0*mm);
  solidMod32 = new G4Tubs("Mod32",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube2, 
			  spanningAngleOfTheTube2);
  
  logicMod32 = new G4LogicalVolume(solidMod32, ModMater, "Mod32",0,0,0); 
  physiMod32 = new G4PVPlacement(0, positionMod32, logicMod32,"Mod32", logicMod30, false, 0);             
    
//----------------------------------------------------------
// 3rd modulator slice (3rd quarter)
//----------------------------------------------------------
 
  G4ThreeVector positionMod33 = G4ThreeVector(0*mm,0*mm,31.0*mm);
  solidMod33 = new G4Tubs("Mod33",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube3, 
			  spanningAngleOfTheTube3);

  logicMod33 = new G4LogicalVolume(solidMod33, ModMater, "Mod33",0,0,0);
  physiMod33 = new G4PVPlacement(0,positionMod33,logicMod33,"Mod33", logicMod30,false, 0);             

//----------------------------------------------------------
// 4th modulator slice (3rd quarter)
//----------------------------------------------------------
     
  G4ThreeVector positionMod34 = G4ThreeVector(0*mm,0*mm,26.0*mm);
  solidMod34 = new G4Tubs("Mod34",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube4, 
			  spanningAngleOfTheTube4);

  logicMod34 = new G4LogicalVolume(solidMod34, ModMater, "Mod34",0,0,0);
  physiMod34 = new G4PVPlacement(0,positionMod34,logicMod34,"Mod34",logicMod30,false, 0);             

//----------------------------------------------------------
// 5th modulator slice (3rd quarter)
//----------------------------------------------------------
    
  G4ThreeVector positionMod35 = G4ThreeVector(0*mm,0*mm,21.0*mm);
  solidMod35 = new G4Tubs("Mod35",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube5, 
			  spanningAngleOfTheTube5);
  
  logicMod35 = new G4LogicalVolume(solidMod35, ModMater, "Mod35",0,0,0);
  physiMod35 = new G4PVPlacement(0, positionMod35,logicMod35, "Mod35", logicMod30, false, 0);              

//----------------------------------------------------------
// 6th modulator slice (3rd quarter)
//----------------------------------------------------------    
  G4ThreeVector positionMod36 = G4ThreeVector(0*mm,0*mm,16.0*mm);
  solidMod36 = new G4Tubs("Mod36",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube6, 
			  spanningAngleOfTheTube6);

  logicMod36 = new G4LogicalVolume(solidMod36, ModMater, "Mod36",0,0,0);
  physiMod36 = new G4PVPlacement(0, positionMod36, logicMod36,"Mod36", logicMod30, false, 0);              

//----------------------------------------------------------
// Mother volume of the Fourth modulator quarter
//----------------------------------------------------------   

  G4RotationMatrix rm40;
  rm40.rotateZ(270 *deg);
  
  G4ThreeVector positionMod40 = G4ThreeVector(0*cm,0*cm,0*cm);  
  solidMod40 = new G4Tubs("Mod40",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  hightOfMotherTube,
			  startAngleOfTheMotherTube , 
			  spanningAngleOfTheMotherTube );
  
  logicMod40 = new G4LogicalVolume(solidMod40, Air, "Mod0",0,0,0); 
  physiMod40 = new G4PVPlacement(G4Transform3D(rm40, positionMod40), 
				 logicMod40,"Mod40",logicMotherMod,false,0);            
  
//----------------------------------------------------------
// 1st modulator slice (4th quarter)
//----------------------------------------------------------
 
  G4ThreeVector positionMod41 = G4ThreeVector(0*mm,0*mm,41.*mm);
  solidMod41 = new G4Tubs("Mod41",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube1, 
			  spanningAngleOfTheTube1);
  
  logicMod41 = new G4LogicalVolume(solidMod41, ModMater, "Mod41",0,0,0);  
  physiMod41 = new G4PVPlacement(0, positionMod41, logicMod41, "Mod41", logicMod40, false, 0);           
   
//----------------------------------------------------------
// 2nd modulator slice (4th quarter)
//----------------------------------------------------------
  
  G4ThreeVector positionMod42 = G4ThreeVector(0*mm,0*mm,36.0*mm);
  solidMod42 = new G4Tubs("Mod42",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube2, 
			  spanningAngleOfTheTube2);
  
  logicMod42 = new G4LogicalVolume(solidMod42, ModMater, "Mod42",0,0,0);  
  physiMod42 = new G4PVPlacement(0, positionMod42,logicMod42, "Mod42",logicMod40,false, 0);               
  
//----------------------------------------------------------
// 3rd modulator slice (4th quarter)
//----------------------------------------------------------
 
  G4ThreeVector positionMod43 = G4ThreeVector(0*mm,0*mm,31.0*mm);
  solidMod43 = new G4Tubs("Mod43",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube3, 
			  spanningAngleOfTheTube3);

  logicMod43 = new G4LogicalVolume(solidMod43, ModMater, "Mod43",0,0,0);
  physiMod43 = new G4PVPlacement(0, positionMod43,logicMod43, "Mod43",logicMod40, false, 0);             

//----------------------------------------------------------
// 4th modulator slice (4th quarter)
//----------------------------------------------------------
      
  G4ThreeVector positionMod44 = G4ThreeVector(0*mm,0*mm,26.0*mm);
  solidMod44 = new G4Tubs("Mod34",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube4, 
			  spanningAngleOfTheTube4);

  logicMod44 = new G4LogicalVolume(solidMod44, ModMater, "Mod44",0,0,0);
  physiMod44 = new G4PVPlacement(0, positionMod44, logicMod44, "Mod44", logicMod40, false, 0);             

//----------------------------------------------------------
// 5th modulator slice (4th quarter)
//----------------------------------------------------------
    
  G4ThreeVector positionMod45 = G4ThreeVector(0*mm,0*mm,21.0*mm);
  solidMod45 = new G4Tubs("Mod45",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube5, 
			  spanningAngleOfTheTube5);
  
  logicMod45 = new G4LogicalVolume(solidMod45, ModMater, "Mod45",0,0,0);
  physiMod45 = new G4PVPlacement(0,positionMod45,logicMod45,"Mod45",logicMod40,false, 0);              
  
//----------------------------------------------------------
// 6th modulator slice (4th quarter)
//----------------------------------------------------------
    
  G4ThreeVector positionMod46 = G4ThreeVector(0*mm,0*mm,16.0*mm);
  solidMod46 = new G4Tubs("Mod46",
			  innerRadiusOfEachBlade , 
			  outerRadiusOfEachBlade ,
			  thicknessOfEachBlade ,
			  startAngleOfTheTube6, 
			  spanningAngleOfTheTube6);

  logicMod46 = new G4LogicalVolume(solidMod46, ModMater, "Mod46",0,0,0);
  physiMod46 = new G4PVPlacement(0,positionMod46,logicMod46,"Mod46", logicMod40, false, 0);              

//----------------------------------------------------------


  G4VisAttributes * red = new G4VisAttributes( G4Colour(255/255. ,0/255. ,0/255.));
  red-> SetVisibility(true);
  red-> SetForceSolid(true);

  G4VisAttributes * red1 = new G4VisAttributes( G4Colour(235/255. ,0/255. ,0/255.));
  red1-> SetVisibility(true);
  red1-> SetForceSolid(true);

  logicMotherMod -> SetVisAttributes(G4VisAttributes::Invisible);

  logicMod0 ->SetVisAttributes(G4VisAttributes::Invisible);
  logicMod20 ->SetVisAttributes(G4VisAttributes::Invisible);
  logicMod30 -> SetVisAttributes(G4VisAttributes::Invisible);
  logicMod40 ->SetVisAttributes(G4VisAttributes::Invisible);

  logicMod1 -> SetVisAttributes(red);
  logicMod2 -> SetVisAttributes(red1);
  logicMod3 -> SetVisAttributes(red);
  logicMod4 -> SetVisAttributes(red1);
  logicMod5 -> SetVisAttributes(red);
  logicMod6 -> SetVisAttributes(red1);
 //logicMod7 -> SetVisAttributes(red);

  logicMod21 -> SetVisAttributes(red);
  logicMod22 -> SetVisAttributes(red1);
  logicMod23 -> SetVisAttributes(red);
  logicMod24 -> SetVisAttributes(red1);
  logicMod25 -> SetVisAttributes(red);
  logicMod26 -> SetVisAttributes(red1);
 // logicMod27 -> SetVisAttributes(red);
  
  logicMod31 -> SetVisAttributes(red);
  logicMod32 -> SetVisAttributes(red1);
  logicMod33 -> SetVisAttributes(red);
  logicMod34 -> SetVisAttributes(red1);
  logicMod35 -> SetVisAttributes(red);
  logicMod36 -> SetVisAttributes(red1);
//  logicMod37 -> SetVisAttributes(red);
  
  logicMod41 -> SetVisAttributes(red);
  logicMod42 -> SetVisAttributes(red1);
  logicMod43 -> SetVisAttributes(red);
  logicMod44 -> SetVisAttributes(red1);
  logicMod45 -> SetVisAttributes(red);
  logicMod46 -> SetVisAttributes(red1);
 // logicMod47 -> SetVisAttributes(red);
  
}

// **************************************************************************************
void Modulator37::SetModulatorAngle(G4double angle)
// --------------------------------------------------------------------------------------
{
  G4double rotationAngle = angle;
  rm -> rotateZ(rotationAngle);
  physiMotherMod -> SetRotation(rm);  
  G4cout << "The Modulator has been rotated by  "<< rotationAngle/deg << " deg" << G4endl;
  G4RunManager::GetRunManager()-> GeometryHasBeenModified(); 
}
// **************************************************************************************

