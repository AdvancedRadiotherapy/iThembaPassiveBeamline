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
//  PassiveProtonBeamLine.cc
// ********************************************************************


// General libraries
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4Region.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "globals.hh"
#include <iomanip>
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "G4NistElementBuilder.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4SystemOfUnits.hh"


// Specific libraries 
#include "DetectorConstruction.hh"
#include "Modulator37.hh"
#include "RangeMonitor.hh"
#include "PassiveProtonBeamLine.hh"
#include "NozzleMaterial.hh"
#include "PrimaryGeneratorAction.hh"

#include "NozzleMessenger.hh"
#include "MagneticField.hh"
#include "PassiveProtonBeamLineMessenger.hh"

//*******************************************************************************************
PassiveProtonBeamLine::PassiveProtonBeamLine(): modulator(0), rangeMonitor(0), detectorConstruction(0),
physicalTreatmentRoom(0), physiBeamLineSupport(0), physiRangeMonitor(0), physiWedgeDown(0),
physiWedgeUp(0), phybeamLineSupportRM(0), phybeamLineSupport1(0), phybeamLineSupport2(0),
physicalRangeModulator(0), physiMotherMod(0)
//-------------------------------------------------------------------------------------------

{
   nozzleMessenger  = new NozzleMessenger(this);
   passiveMessenger = new PassiveProtonBeamLineMessenger(this);
   nozzleMaterial   = new NozzleMaterial();
   YmagField        = new MagneticField();     
   XmagField        = new MagneticField();

   DownWedgeVerPos  = -150.0*mm;
   UpWedgeVerPos    = 150.0*mm;
   RangeMonitorZPos = -6978*mm +1589*mm + 45*mm;
}
//*******************************************************************************************
PassiveProtonBeamLine::~PassiveProtonBeamLine()
//-------------------------------------------------------------------------------------------

{
	delete passiveMessenger;
	delete detectorConstruction;
        delete nozzleMaterial;
        delete nozzleMessenger;
        delete YmagField;
        delete XmagField;
}

//*******************************************************************************************
G4VPhysicalVolume* PassiveProtonBeamLine::Construct()
//-------------------------------------------------------------------------------------------
{ 

	SetDefaultDimensions();
        SetDefaultMaterials();
        SetDefaultColors();	
	ConstructPassiveProtonBeamLine();
        	
     // DetectorConstruction builds ONLY the phantom and the detector with its associated ROGeometry
	detectorConstruction = new DetectorConstruction(physicalTreatmentRoom); 
	
	return physicalTreatmentRoom;
}

//*******************************************************************************************
void PassiveProtonBeamLine::SetDefaultDimensions()
//-------------------------------------------------------------------------------------------
{
}

//*******************************************************************************************
void PassiveProtonBeamLine::SetDefaultColors()
//-------------------------------------------------------------------------------------------
{


    white           = new G4VisAttributes( G4Colour() ); 
    blue            = new G4VisAttributes(G4Colour(0. ,0. ,1.));
    yellow          = new G4VisAttributes( G4Colour(1. ,1. ,0.)); 
    gray            = new G4VisAttributes( G4Colour(0.5 ,0.5 ,0.5)); 
    red             = new G4VisAttributes( G4Colour(1., 0., 0.) ); 	
    purple          = new G4VisAttributes( G4Colour(0.5, 0.2, 1.0) ); 
    green           = new G4VisAttributes( G4Colour(25/255., 255/255., 25/255.)); 
    darkGreen       = new G4VisAttributes( G4Colour(0/255., 100/255., 0/255.));
    black           = new G4VisAttributes( G4Colour(0/255., 0/255., 0/255.)); 
    invisible       = new G4VisAttributes( G4Colour(135/255., 206/255., 235/255.)); 
    brass           = new G4VisAttributes( G4Colour(181/255., 166/255., 66/255.));
    stainlessSteel  = new G4VisAttributes( G4Colour(205/255., 102/255., 29/255.));
    graphite        = new G4VisAttributes( G4Colour(224/255., 223/255., 219/255.));
    lead            = new G4VisAttributes( G4Colour(224/255., 223/255., 219/255.));
    iron            = new G4VisAttributes( G4Colour(205/255., 102/255., 0/255.));
    concrete        = new G4VisAttributes( G4Colour(184/255., 184/255., 186/255.));
    copper          = new G4VisAttributes( G4Colour(208/255., 113/255., 49/255.));
    aluminum        = new G4VisAttributes( G4Colour(170/255., 175/255., 181/255.));
    kapton          = new G4VisAttributes( G4Colour(48/255., 48/255., 48/255.));
    water           = new G4VisAttributes( G4Colour(155/255., 216/255., 217/255.));
    mylar           = new G4VisAttributes( G4Colour(0/255., 51/255., 0/255.));
    lexan           = new G4VisAttributes( G4Colour(225/255., 190/255., 48/255.));
    perspex         = new G4VisAttributes( G4Colour(230/255., 231/255., 233/255.));
    thiolyte        = new G4VisAttributes( G4Colour(81/255., 81/255., 81/255.));
    havar           = new G4VisAttributes( G4Colour(187/255., 54/255., 120/255.));
    air             = new G4VisAttributes( G4Colour(0., 0., 1.));
    tungsten        = new G4VisAttributes( G4Colour(239/255., 165/255., 31/255.));
    cerrobend       = new G4VisAttributes( G4Colour(199/255., 97/255., 20/255.));
    vacuum          = new G4VisAttributes( G4Colour(0. ,0. ,1.));
    poleshoe        = new G4VisAttributes( G4Colour(98/255., 97/255., 95/255.));
    diver_yoke      = new G4VisAttributes( G4Colour(98/255., 97/255., 95/255.));
    gold            = new G4VisAttributes( G4Colour(216/255., 177/255., 0/255.));
    pcBoard         = new G4VisAttributes( G4Colour(205/255., 133/255., 0/255.)); 
    ss304           = new G4VisAttributes( G4Colour(224/255., 223/255., 219/255.));
    paraffinWax     = new G4VisAttributes( G4Colour());

    white      -> SetVisibility(true);            white     -> SetForceSolid(false);
    blue       -> SetVisibility(true);            blue      -> SetForceSolid(true);
    invisible  -> SetVisibility(false);           invisible -> SetForceSolid(false);
    graphite   -> SetVisibility(true);            graphite  -> SetForceSolid(true);
    yellow     -> SetVisibility(true);            yellow    -> SetForceSolid(true);
    gray       -> SetVisibility(true);            gray      -> SetForceSolid(true);
    red        -> SetVisibility(true);            red       -> SetForceSolid(true);
    purple     -> SetVisibility(true);            purple    -> SetForceSolid(true);
    green      -> SetVisibility(true);            green     -> SetForceSolid(true);
    darkGreen  -> SetVisibility(true);            darkGreen -> SetForceSolid(true);
    black      -> SetVisibility(true);            black     -> SetForceSolid(true);
    brass      -> SetVisibility(true);            brass     -> SetForceSolid(true);  
    lead       -> SetVisibility(true);            lead      -> SetForceSolid(true);
    iron       -> SetVisibility(true);            iron      -> SetForceSolid(true);
    concrete   -> SetVisibility(true);            concrete  -> SetForceSolid(true);
    copper     -> SetVisibility(true);            copper    -> SetForceSolid(true);
    aluminum   -> SetVisibility(true);            aluminum  -> SetForceSolid(true);
    kapton     -> SetVisibility(true);            kapton    -> SetForceSolid(true);
    water      -> SetVisibility(true);            water     -> SetForceSolid(true);
    mylar      -> SetVisibility(true);            mylar     -> SetForceSolid(true);
    lexan      -> SetVisibility(true);            lexan     -> SetForceSolid(true);
    perspex    -> SetVisibility(true);            perspex   -> SetForceSolid(true);
    thiolyte   -> SetVisibility(true);            thiolyte  -> SetForceSolid(true);
    havar      -> SetVisibility(true);            havar     -> SetForceSolid(true);
    air        -> SetVisibility(true);            air       -> SetForceSolid(false);
    tungsten   -> SetVisibility(true);            tungsten  -> SetForceSolid(true);
    cerrobend  -> SetVisibility(true);            cerrobend -> SetForceSolid(true);
    vacuum     -> SetVisibility(true);            vacuum    -> SetForceSolid(false);
    poleshoe   -> SetVisibility(true);            poleshoe  -> SetForceSolid(false);
    diver_yoke -> SetVisibility(true);            diver_yoke-> SetForceSolid(false);   
    gold       -> SetVisibility(true);            gold      -> SetForceSolid(true);
    pcBoard    -> SetVisibility(true);            pcBoard   -> SetForceSolid(true);
    ss304      -> SetVisibility(true);            ss304     -> SetForceSolid(true);
    stainlessSteel -> SetVisibility(true);        stainlessSteel -> SetForceSolid(true);
    paraffinWax -> SetVisibility(true);           paraffinWax -> SetForceSolid(true);
		
}

//*******************************************************************************************
void PassiveProtonBeamLine::SetDefaultMaterials()
//-------------------------------------------------------------------------------------------
{
     nozzleMaterial -> DefineMaterials();
     Vacuum    = nozzleMaterial -> GetMat("Vacuum");
     Water     = nozzleMaterial -> GetMat("Water");
     Havar     = nozzleMaterial -> GetMat("Havar");
     Brass     = nozzleMaterial -> GetMat("Brass");
     Air       = nozzleMaterial -> GetMat("Air");
     Carbon    = nozzleMaterial -> GetMat("Carbon");
     Aluminum  = nozzleMaterial -> GetMat("Aluminum");
     Copper    = nozzleMaterial -> GetMat("Copper");
     Tungsten  = nozzleMaterial -> GetMat("Tungsten");
     Lead      = nozzleMaterial -> GetMat("Lead");
     Kapton    = nozzleMaterial -> GetMat("Kapton");
     Ceramic   = nozzleMaterial -> GetMat("Ceramic");
     SS304     = nozzleMaterial -> GetMat("SS304");
     Tissue    = nozzleMaterial -> GetMat("Tissue");
     Lucite    = nozzleMaterial -> GetMat("Lucite");
     Graphite  = nozzleMaterial -> GetMat("Graphite");
     Iron      = nozzleMaterial -> GetMat("Iron");
     Cerrobend = nozzleMaterial -> GetMat("Cerrobend");
     Concrete  = nozzleMaterial -> GetMat("Concrete");
     Lexan     = nozzleMaterial -> GetMat("Lexan");
     Mylar     = nozzleMaterial -> GetMat("Mylar");
     Perspex1  = nozzleMaterial -> GetMat("Perspex1");
     Perspex2  = nozzleMaterial -> GetMat("Perspex2");
     Perspex3  = nozzleMaterial -> GetMat("Perspex3");
     Thiolyte  = nozzleMaterial -> GetMat("Thiolyte");
     Gold      = nozzleMaterial -> GetMat("Gold");
     PCBoard   = nozzleMaterial -> GetMat("PCBoard");
     ParaffinWax = nozzleMaterial -> GetMat("ParaffinWax");
}
//*******************************************************************************************
void PassiveProtonBeamLine::ConstructPassiveProtonBeamLine()
//-------------------------------------------------------------------------------------------

{ 
  // Treatment room (World volume)    
     const G4double worldX = 7.0 *m;
     const G4double worldY = 7.0 *m;
     const G4double worldZ = 15.0 *m;

     G4Box* treatmentRoomwall = new G4Box("TreatmentRoomwall",8.0*m,8.0*m,16.0*m);
     G4LogicalVolume* logicTreatmentRoomwall = new G4LogicalVolume(treatmentRoomwall, Concrete, "TreatmentRoomwall");
     new G4PVPlacement(0, G4ThreeVector(), "TreatmentRoomwall", logicTreatmentRoomwall, 0,false,0);
     logicTreatmentRoomwall -> SetVisAttributes (G4VisAttributes::Invisible);

     G4Box* treatmentRoom = new G4Box("TreatmentRoom",worldX,worldY,worldZ);
     logicTreatmentRoom = new G4LogicalVolume(treatmentRoom, Air, "logicTreatmentRoom", 0,0,0);
     physicalTreatmentRoom = new G4PVPlacement(0, G4ThreeVector(), "physicalTreatmentRoom", logicTreatmentRoom, 0,false,0);
     logicTreatmentRoom -> SetVisAttributes (G4VisAttributes::Invisible);
	
     BeamLineSupport();

        if (removeVacuumTube != "Yes")                              VacuumTube();
        if (removeReferenceIonizationChamber != "Yes")              ReferenceIonizationChamber();
        if (removeYSteeringMagnets != "Yes")                        YSteeringMagnets();
        if (removeMultiWireIonizationChamber != "Yes")              MultiWireIonizationChamber();
        if (removeXSteeringMagnets != "Yes")                        XSteeringMagnets();
        if (removeRangeTrimmerPlate != "Yes")                       RangeTrimmerPlate();
        if (removeLeadPlate != "Yes")                               LeadPlate();
        //if (removeWedge != "Yes")                                 Wedge();
        if (removeMultiLayerFaradayCup != "Yes")                    MultiLayerFaradayCup();
        //if (removeRangeMonitor != "Yes")                          BeamRangeMonitor();
        if (removeOccludingRingAndCentralStopper != "Yes")          OccludingRingAndCentralStopper();
        if (removeShieldingCollimators != "Yes")                    ShieldingCollimators();
        if (removeQuadrantAndMonitorIonizationChamber != "Yes")     QuadrantAndMonitorIonizationChamber();
        //if (removeBeamFinalCollimator != "Yes")                   BeamFinalCollimator(); 
        if (removeRangeModulator != "Yes")                          RangeModulator();
        if (removeNewRangeMonitoriThemba != "Yes")                  RangeMonitoriThemba();
   
}

//*******************************************************************************************
void PassiveProtonBeamLine::BeamLineSupport()
//-------------------------------------------------------------------------------------------
{  
    G4Box* beamLineCover = new G4Box("BeamLineCover",30.0*mm,30.*mm,2000.*mm);
    G4LogicalVolume* logicBeamLineCover = new G4LogicalVolume(beamLineCover, Air,"BeamLineCover");
    new G4PVPlacement(0, G4ThreeVector(200.*mm,-250.*mm,-5500.*mm),"BeamLineCover",
					 logicBeamLineCover, physicalTreatmentRoom, false,  0);
    new G4PVPlacement(0, G4ThreeVector(-200.*mm,-250.*mm,-5500.0*mm),"BeamLineCover2", logicBeamLineCover, 
					  physicalTreatmentRoom, false, 0);
    logicBeamLineCover -> SetVisAttributes(blue);

    const G4int NbofbeamSupport = 6;
    G4Box* beamLineVerSupport = new G4Box("BeamLineVerSupport", 30.*mm, 300.0*mm, 30.0*mm);
    G4ThreeVector* beamLineVerSupportPosition = new G4ThreeVector[NbofbeamSupport];
    beamLineVerSupportPosition[0] = G4ThreeVector(200.0*mm, -550.0*mm,  -5500.*mm);
    beamLineVerSupportPosition[1] = G4ThreeVector(200.0*mm, -550.0*mm,  -7400.*mm);
    beamLineVerSupportPosition[2] = G4ThreeVector(200.0*mm, -550.0*mm,  -3600*mm);
    beamLineVerSupportPosition[3] = G4ThreeVector(-200.0*mm, -550.0*mm,  -3600*mm);
    beamLineVerSupportPosition[4] = G4ThreeVector(-200.0*mm, -550.0*mm,  -7400*mm);
    beamLineVerSupportPosition[5] = G4ThreeVector(-200.0*mm, -550.0*mm,  -5500.*mm);

    G4LogicalVolume* logicbeamLineVerSupport = new G4LogicalVolume(beamLineVerSupport, Air, "BeamLineVerSupport");    
    for (G4int i = 0; i < NbofbeamSupport; i++) {
    new G4PVPlacement(0, beamLineVerSupportPosition[i],logicbeamLineVerSupport, "BeamLineVerSupport",  logicTreatmentRoom, false, i);}
    logicbeamLineVerSupport -> SetVisAttributes(blue);

}

// *******************************************************************************************************************
void PassiveProtonBeamLine::VacuumTube()
//--------------------------------------------------------------------------------------------------------------------
{
  // Vacuum Pipe: the first track of the beam line is inside vacuum, 
  // The PIPE contains the 25 micrometer Havar Window
  // -6978.0 mm from isocentre or -50.0 mm from vacuum window
  // Vacuum Pipe (First track of the beam line is inside vacuum tube)

     vacuumTubeZPosition = -7178.0*mm;

     G4Tubs* vacuumTube = new G4Tubs("VacuumTube", 0.0 *mm, 50.0 *mm, 200.0 *mm, 0.0*deg, 360.0*deg);
     G4LogicalVolume* logicVacuumTube = new G4LogicalVolume(vacuumTube, Vacuum, "VacuumTube");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,vacuumTubeZPosition),logicVacuumTube,"VacuumTube",  logicTreatmentRoom, false, 0);
     logicVacuumTube->SetVisAttributes(aluminum);

  // The 25.0 micro meter Havar Window
  // Havar prmits the passage of the beam from vacuum to air
  // Havar window: it prmits the passage of the beam from vacuum to air

     HavarWindowZPosition = 100.0*mm - 0.025/2*mm;

     G4Tubs* vacuumWindow = new G4Tubs("VacuumWindow", 0.0 *mm, 50.0 *mm, 0.025/2*mm, 0.0*deg, 360.0*deg);
     G4LogicalVolume* logicVacuumWindow = new G4LogicalVolume(vacuumWindow, Havar, "VacuumWindow");
     new G4PVPlacement(0, G4ThreeVector(0., 0., HavarWindowZPosition),logicVacuumWindow,"VacuumWindow",  logicVacuumTube, false, 0);
     logicVacuumWindow-> SetVisAttributes(havar);

  // beam support
     const G4int NbofbeamSupportVT1 = 2;
     G4Box* beamLineSupportVT1 = new G4Box("BeamLineSupportVT1", 250.*mm, 25.0*mm, 25.0*mm);
     G4ThreeVector* beamLineSupportVT1Position = new G4ThreeVector[NbofbeamSupportVT1];
     beamLineSupportVT1Position[0] = G4ThreeVector(0.0*mm,-210.0*mm,vacuumTubeZPosition-80.0*mm);
     beamLineSupportVT1Position[1] = G4ThreeVector(0.0*mm,-210.0*mm,vacuumTubeZPosition+80.0*mm);
     G4LogicalVolume* logicBeamLineSupportVT1 = new G4LogicalVolume(beamLineSupportVT1, Air, "BeamLineSupportVT1");
     for (G4int i = 0; i < NbofbeamSupportVT1; i++) {
     new G4PVPlacement(0, beamLineSupportVT1Position[i],"BeamLineSupportVT", logicBeamLineSupportVT1, 
					   physicalTreatmentRoom, false, 0);}
     logicBeamLineSupportVT1 -> SetVisAttributes(yellow);

     const G4int NbofbeamSupport = 2;
     G4Box* beamLineVerSupport = new G4Box("BeamLineVerSupport", 15.*mm, 100.0*mm, 15.0*mm);
     G4ThreeVector* beamLineVerSupportPosition = new G4ThreeVector[NbofbeamSupport];
     beamLineVerSupportPosition[0] = G4ThreeVector(40.0*mm, -120.0*mm,  vacuumTubeZPosition-80.*mm);
     beamLineVerSupportPosition[1] = G4ThreeVector(-40.0*mm, -120.0*mm,  vacuumTubeZPosition+80.*mm);

     G4LogicalVolume* logicbeamLineVerSupport = new G4LogicalVolume(beamLineVerSupport, Air, "BeamLineVerSupport");    
     for (G4int i = 0; i < NbofbeamSupport; i++) {
     new G4PVPlacement(0, beamLineVerSupportPosition[i],logicbeamLineVerSupport, "BeamLineVerSupport",  logicTreatmentRoom, false, i);}
     logicbeamLineVerSupport -> SetVisAttributes(yellow);
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::ReferenceIonizationChamber()
//--------------------------------------------------------------------------------------------------------------------
{
  // centre between two lead electrodes is 47 mm (which is the centre of the ionChamber)from vacuum window
  // -6931.0 mm from isocentre or 47.0 mm from vacuum window
  // Perspex casing of the lead electrodes and the isolating spacer, 
  // which is a circular aperture of 40 mm in diameter and 90 cm outer diameter
     G4Tubs* perspexPlate = new G4Tubs("PerspexPlate", 40.0/2*mm, 90.0/2*mm, 11.468/2*mm, 0.0*deg, 360.0*deg);
     G4LogicalVolume* logicPerspexPlate = new G4LogicalVolume(perspexPlate, Perspex3, "PerspexPlate");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-6932.5*mm),logicPerspexPlate,"PerspexPlate",  logicTreatmentRoom, false, 0);
     logicPerspexPlate->SetVisAttributes(perspex);

  // Lexan isolating disc, whish is 1.0 mm thick and has an outer diameter of 60 mm and a hole with a diamter of 40.0 mm at its center 
     G4Tubs* lexanplate = new G4Tubs("Lexanplate", 40.0/2*mm, 60.0/2*mm, 1.0/2*mm, 0.0*deg, 360.0*deg);
     G4LogicalVolume* logicLexanplate = new G4LogicalVolume(lexanplate, Lexan, "Lexanplate");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,1.5*mm),logicLexanplate, "Lexanplate",  logicPerspexPlate, false, 0);
     logicLexanplate->SetVisAttributes(lexan);

  // Two circular lead electrodes of each 0.234 mm thickness and 60.0 mm diameter
     G4Tubs* leadPlate = new G4Tubs("LeadPlate", 0.0*mm, 60.0/2*mm, 0.234/2*mm, 0.0*deg, 360.0*deg);
     G4ThreeVector* leadPlatePosition = new G4ThreeVector[NbOfLeadPlate];
     leadPlatePosition[0] = G4ThreeVector(0.0*mm, 0.0*mm,  2.117*mm);
     leadPlatePosition[1] = G4ThreeVector(0.0*mm, 0.0*mm,  0.883*mm);

     G4LogicalVolume* logicLeadPlate = new G4LogicalVolume(leadPlate, Lead, "LeadPlate");   
     for (G4int i = 0; i < NbOfLeadPlate; i++) {
     new G4PVPlacement(0, leadPlatePosition[i],logicLeadPlate, "LeadPlate",  logicPerspexPlate, false, i);}
     logicLeadPlate->SetVisAttributes(lead);

  // The aperture of two circular lead electrodes is closed on both ends by a 25 micrometer Kapton 
  // layer across each face of the casing. The outer diameter of the cylindrical casing is 90 mm
     G4Tubs* kaptonCasing = new G4Tubs("KaptonCasing", 0.0*mm, 90.0/2*mm, 0.025/2*mm, 0.0*deg, 360.0*deg);
     G4ThreeVector* kaptonCasingPosition = new G4ThreeVector[NbOfKaptonCasing];
     kaptonCasingPosition[0] = G4ThreeVector(0.0*mm, 0.0*mm,  -6926.7535*mm);
     kaptonCasingPosition[1] = G4ThreeVector(0.0*mm, 0.0*mm,  -6938.2465*mm);

     G4LogicalVolume* logicKaptonCasing = new G4LogicalVolume(kaptonCasing, Kapton, "KaptonCasing");    
     for (G4int i = 0; i < NbOfKaptonCasing; i++) {
     new G4PVPlacement(0, kaptonCasingPosition[i],logicKaptonCasing, "KaptonCasing",  logicTreatmentRoom, false, i);}
     logicKaptonCasing->SetVisAttributes(kapton);


  // The reference chamber is mounted on the downstream face of a Perspex disc of 3.5 mm thickness 
  // and has outer diameter of 118 mm and a hole with a diameter of 45 mm at its centre
     G4Tubs* perspexMount = new G4Tubs("PerspexMount", 45.0/2.0*mm, 118.0/2*mm, 3.5/2*mm, 0.0*deg, 360.0*deg);
     G4LogicalVolume* logicPerspexMount = new G4LogicalVolume(perspexMount, Perspex3, "PerspexMount");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-6940.009*mm),logicPerspexMount,"PerspexMount",  logicTreatmentRoom, false, 0);
     logicPerspexMount->SetVisAttributes(perspex);

}

// *******************************************************************************************************************
void PassiveProtonBeamLine::YSteeringMagnets()
//--------------------------------------------------------------------------------------------------------------------
{
   // out Divider and Yoke plates & Mother volume for Y-Steering Magnet   
   // 338 mm wide (x-axis), 300 mm hight (y-axis) and 200 mm long (z-axis))
   // 80 mm upstream face of poleshoes
      YOuterDividerAndYokeZPosition = -6978.0*mm+80.0*mm+100*mm; 

      G4Box* YouterdividerAndYoke = new G4Box("YOuterDividerAndYoke",338.0/2 *mm,300.0/2*mm,200.0/2*mm);
      G4LogicalVolume* logicYOuterDividerAndYoke = new G4LogicalVolume(YouterdividerAndYoke, Air, "YOuterDividerAndYoke");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,YOuterDividerAndYokeZPosition),logicYOuterDividerAndYoke,
							 "YOuterDividerAndYoke",  logicTreatmentRoom, false, 0);
      logicYOuterDividerAndYoke->SetVisAttributes(invisible);

   // Four yoke 
      G4Box* yokeYdir = new G4Box("YokeYdir", 30.5/2*mm, 300.0/2*mm, 200.0/2*mm);
      G4ThreeVector* YokeYdirPosition = new G4ThreeVector[NbOfYoke];
      YokeYdirPosition[0] = G4ThreeVector(-153.75*mm,0.*mm,  0.*mm);
      YokeYdirPosition[1] = G4ThreeVector(153.75*mm,0.*mm,  0.*mm);
      G4LogicalVolume* logicYokeYdir = new G4LogicalVolume(yokeYdir, Iron, "YokeYdir");
    
      for (G4int i = 0; i < NbOfYoke; i++) {
      new G4PVPlacement(0, YokeYdirPosition[i],logicYokeYdir,"YokeYdir",  logicYOuterDividerAndYoke, false, i);}
      logicYokeYdir->SetVisAttributes(diver_yoke );


      G4Box* yokeXdir = new G4Box("YokeXdir", 277.0/2*mm, 30.5/2*mm, 200.0/2*mm);
      G4ThreeVector* YokeXdirPosition = new G4ThreeVector[NbOfYoke];
      YokeXdirPosition[0] = G4ThreeVector(0.*mm,-134.75*mm,  0.*mm);
      YokeXdirPosition[1] = G4ThreeVector(0.*mm, 134.75*mm,  0.*mm);
      G4LogicalVolume* logicYokeXdir = new G4LogicalVolume(yokeXdir, Iron, "YokeXdir");
    
      for (G4int i = 0; i < NbOfYoke; i++) {
      new G4PVPlacement(0, YokeXdirPosition[i],logicYokeXdir,"YokeXdir",  logicYOuterDividerAndYoke, false, i);}
      logicYokeXdir->SetVisAttributes(diver_yoke );


   // Y-Steering Magnet (338-80) mm x 159 mm x 200 mm

      G4Box* YsteeringMagnet = new G4Box("YSteeringMagnet",277.0/2*mm,159.0*mm/2, 200.0*mm/2 );
      G4LogicalVolume* logicYSteeringMagnet = new G4LogicalVolume(YsteeringMagnet, Iron, "YSteeringMagnet",YmagField->GetTheFieldManager(),0,0);
      new G4PVPlacement(0, G4ThreeVector(0., 0.,0.),logicYSteeringMagnet,"YSteeringMagnet",  logicYOuterDividerAndYoke, false, 0);
      logicYSteeringMagnet->SetVisAttributes(poleshoe);

   // Centre Air gaps 
      G4Box* YmagnetAirGap1 = new G4Box("YMagnetAirGap1",78.0*mm/2,139.0*mm/2, 200.0*mm/2 );  
      G4LogicalVolume* logicYMagnetAirGap1 = new G4LogicalVolume(YmagnetAirGap1, Air, "YMagnetAirGap1");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,0*mm),logicYMagnetAirGap1,"YMagnetAirGap1",  logicYSteeringMagnet, false, 0);
      logicYMagnetAirGap1->SetVisAttributes(air);

      G4Box* YmagnetAirLateralGap = new G4Box("YMagnetAirLateralGap",62.0*mm/2,10.0*mm/2, 200.0*mm/2 );  
      G4ThreeVector* YMagnetAirLateralGapPosition = new G4ThreeVector[NbOfLateralAirGap];
      YMagnetAirLateralGapPosition[0] = G4ThreeVector(0.*mm,-74.5*mm,  0.*mm);
      YMagnetAirLateralGapPosition[1] = G4ThreeVector(0.*mm, 74.5*mm,  0.*mm);
      G4LogicalVolume* logicYMagnetAirLateralGap = new G4LogicalVolume(YmagnetAirLateralGap, Air, "YMagnetAirLateralGap");
    
      for (G4int i = 0; i < NbOfLateralAirGap; i++) {
      new G4PVPlacement(0, YMagnetAirLateralGapPosition[i],logicYMagnetAirLateralGap,"YMagnetAirLateralGap",  logicYSteeringMagnet, false, i);}
      logicYMagnetAirLateralGap->SetVisAttributes(air);

   // Four cupper coils 90mm x 40mm x 200mm

      G4Box* YmagnetCopperCoil = new G4Box("YMagnetCopperCoil", 90.0/2*mm, 40.0/2*mm, 200.0/2*mm);
      G4ThreeVector* YMagnetCopperCoilPosition = new G4ThreeVector[NbOfCoppercoil];
      YMagnetCopperCoilPosition[0] = G4ThreeVector(-93.5*mm,-99.5*mm,  0.*mm);
      YMagnetCopperCoilPosition[1] = G4ThreeVector(-93.5*mm, 99.5*mm,  0.*mm);
      YMagnetCopperCoilPosition[2] = G4ThreeVector( 93.5*mm,-99.5*mm,  0.*mm);
      YMagnetCopperCoilPosition[3] = G4ThreeVector( 93.5*mm, 99.5*mm,  0.*mm);
      G4LogicalVolume* logicYMagnetCopperCoil = new G4LogicalVolume(YmagnetCopperCoil, Copper, "YMagnetCopperCoil");
    
      for (G4int i = 0; i < NbOfCoppercoil; i++) {
      new G4PVPlacement(0, YMagnetCopperCoilPosition[i],logicYMagnetCopperCoil,"YMagnetCopperCoil",  logicYOuterDividerAndYoke, false, i);}
      logicYMagnetCopperCoil->SetVisAttributes(copper);

  // beam support
     const G4int NbofbeamLineSupportYMG = 2;
     G4Box* beamLineSupportYMG = new G4Box("BeamLineSupportYMG", 250.*mm, 40.0*mm, 10.0*mm);
     G4ThreeVector* beamLinebeamLineSupportYMG = new G4ThreeVector[NbofbeamLineSupportYMG];
     beamLinebeamLineSupportYMG[0] = G4ThreeVector(0.0*mm,-205.0*mm,YOuterDividerAndYokeZPosition-90.0*mm);
     beamLinebeamLineSupportYMG[1] = G4ThreeVector(0.0*mm,-205.0*mm,YOuterDividerAndYokeZPosition+90.0*mm);

     G4LogicalVolume* logicbeamLineSupportYMG = new G4LogicalVolume(beamLineSupportYMG, Air, "BeamLineSupportYMG");    
     for (G4int i = 0; i < NbofbeamLineSupportYMG; i++) {
     new G4PVPlacement(0, beamLinebeamLineSupportYMG[i],logicbeamLineSupportYMG, "BeamLineSupportYMG",  logicTreatmentRoom, false, i);}

     logicbeamLineSupportYMG -> SetVisAttributes(yellow);
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::MultiWireIonizationChamber()
//--------------------------------------------------------------------------------------------------------------------
{
   // Mother volume for MultyWireIonizationChamber 
   // 300 mm wide (x-axis), 338 mm hight (y-axis) and 200 mm long (z-axis))
      MultiWireIonizationChamberZPosition =-6978.0*mm+356.0*mm;
 
      G4Box* multiWireIonizationChamber = new G4Box("MultiWireIonizationChamber",120.0/2*mm,120.0/2*mm,60.0/2*mm); 
      G4LogicalVolume* logicMultiWireIonizationChamber = new G4LogicalVolume(multiWireIonizationChamber, Air, "MultiWireIonizationChamber");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,MultiWireIonizationChamberZPosition*mm),logicMultiWireIonizationChamber,
							 "MultiWireIonizationChamber",  logicTreatmentRoom, false, 0);
      logicMultiWireIonizationChamber->SetVisAttributes(invisible);


   // Perspex outer support frame of thickness 10 mm in the beam direction and have 100 mm air gap.
   // the spacing between two plates is 35 mm 
      G4Box* perspexSupportPlate = new G4Box("PerspexSupportPlate", 120.0/2*mm, 120.0/2*mm, 10.0/2*mm);
      G4Box* airGap = new G4Box("AirGap", 100.0/2*mm, 100.0/2*mm, 10.01/2*mm);
      G4SubtractionSolid* perspexSupport= new G4SubtractionSolid("PerspexSupport",perspexSupportPlate,airGap);

      G4ThreeVector* PerspexSupportPosition = new G4ThreeVector[NbOfPerspexSupport];
      PerspexSupportPosition[0] = G4ThreeVector(0.*mm,0.*mm,  22.5*mm);
      PerspexSupportPosition[1] = G4ThreeVector(0.*mm, 0.*mm,  -22.5*mm);

      G4LogicalVolume* logicPerspexSupport = new G4LogicalVolume(perspexSupport, Perspex3, "PerspexSupport");
    
      for (G4int i = 0; i < NbOfPerspexSupport; i++) {
      new G4PVPlacement(0, PerspexSupportPosition[i],logicPerspexSupport,"PerspexSupport",  logicMultiWireIonizationChamber, false, i);}
      logicPerspexSupport->SetVisAttributes(perspex);


   // Kapton protective layer of 25 micrometer is 10.0 mm from the HV plates both sides    
      G4Box* kaptonLayer = new G4Box("KaptonLayer", 120.0/2*mm, 120.0/2*mm, 0.025/2*mm);
      G4ThreeVector* KaptonLayerPosition = new G4ThreeVector[NbOfKaptonLayer];
      KaptonLayerPosition[0] = G4ThreeVector(0.*mm,0.*mm, (35.0/2*mm+10*mm+0.025/2*mm));
      KaptonLayerPosition[1] = G4ThreeVector(0.*mm, 0.*mm,-(35.0/2*mm+10*mm+0.025/2*mm));
      G4LogicalVolume* logicKaptonLayer = new G4LogicalVolume(kaptonLayer, Kapton, "KaptonLayer");
    
      for (G4int i = 0; i < NbOfKaptonLayer; i++) {
      new G4PVPlacement(0, KaptonLayerPosition[i],logicKaptonLayer,"KaptonLayer",  logicMultiWireIonizationChamber, false, i);}
      logicKaptonLayer->SetVisAttributes(kapton);

   // Aluminum HV plate of 125 micrometer at a distance of 10.0 mm from the wire plane
      G4Box* alPlate = new G4Box("AlPlate", 120.0/2*mm, 120.0/2*mm, 0.125/2*mm);
      G4ThreeVector* AlPlatePosition = new G4ThreeVector[NbOfAlPlate];
      AlPlatePosition[0] = G4ThreeVector(0.*mm,0.*mm, (35.0/2*mm-0.125/2*mm));
      AlPlatePosition[1] = G4ThreeVector(0.*mm, 0.*mm,-(35.0/2*mm-0.125/2*mm));
      G4LogicalVolume* logicAlPlate = new G4LogicalVolume(alPlate, Aluminum, "AlPlate");
    
      for (G4int i = 0; i < NbOfAlPlate; i++) {
      new G4PVPlacement(0, AlPlatePosition[i],logicAlPlate,"AlPlate",  logicMultiWireIonizationChamber, false, i);}
      logicAlPlate->SetVisAttributes(gray);

   // centre Perspex support of thickness 15 mm
      G4Box* perspexCentreSheet = new G4Box("PerspexCentreSheet",120.0*mm/2,120.0*mm/2, 15.0*mm/2 );
      G4Box* perspexCentreAirGap = new G4Box("PerspexCentreAirGap",100.0*mm/2,100.0*mm/2, 15.01*mm/2 );  
      G4SubtractionSolid* perspexCentre= new G4SubtractionSolid("PerspexCentre",perspexCentreSheet,perspexCentreAirGap);
  
      G4LogicalVolume* logicPerspexCentre = new G4LogicalVolume(perspexCentre, Perspex3, "PerspexCentre");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,0.*mm),logicPerspexCentre,"PerspexCentre",  logicMultiWireIonizationChamber, false, 0);
      logicPerspexCentre->SetVisAttributes(perspex);

   // Horizontal(Y-Segment) 

     // Position / Dimension Specifications of   
        G4double tungWireRadius    = 0.1/2*mm; 
        G4double tungWireSpacing   = 2.0*mm;
        G4double tungWireLength    = 100.0*mm;
  
     // Setting wire positionsperspex
        G4double y1 = 0.0*mm;
        G4ThreeVector* TungHorizontalWirePosition = new G4ThreeVector[NbOfTungstenWire];
        for (G4int i = 0; i < NbOfTungstenWire; i++) {
        y1 = ((NbOfTungstenWire/2 * tungWireSpacing) - tungWireSpacing/2 - (i*tungWireSpacing));
        TungHorizontalWirePosition[i] = G4ThreeVector( 0.0*mm, y1*mm, 8.0*mm); }

     // Volume Definitions  
        G4RotationMatrix* tungHorizontalWireRot = new G4RotationMatrix;
        tungHorizontalWireRot->rotateY(90.0*deg);
        G4Tubs* solidTungHorizontalWire = new G4Tubs("TungHorizontalWire", 0, tungWireRadius,tungWireLength/2, 0.0*deg, 360.0*deg);
        G4LogicalVolume* logicTungHorizontalWire = new G4LogicalVolume(solidTungHorizontalWire, Tungsten, 
							  "TungHorizontalWire_Logic", 0, 0, 0);
        for (G4int i = 0; i < NbOfTungstenWire; i++) {
	new G4PVPlacement(tungHorizontalWireRot, TungHorizontalWirePosition[i], 
                           logicTungHorizontalWire,"TungHorizontalWire_Physi",logicMultiWireIonizationChamber,false,i);}
        logicTungHorizontalWire->SetVisAttributes(tungsten);

   // Horizontal(Y-Segment) 

     // Setting wire positions
        G4double x1 = 0.0*mm;
        G4ThreeVector* TungVerWirePosition = new G4ThreeVector[NbOfTungstenWire];
        for (G4int i = 0; i < NbOfTungstenWire; i++) {
        x1 = ((NbOfTungstenWire/2 * tungWireSpacing) - tungWireSpacing/2 - (i*tungWireSpacing));
        TungVerWirePosition[i] = G4ThreeVector(x1*mm, 0.0*mm, -8.0*mm); }

     // Volume Definitions  
        G4RotationMatrix* tungVerWireRot = new G4RotationMatrix;
        tungVerWireRot->rotateX(90.0*deg);
        G4Tubs* solidTungVerWire = new G4Tubs("TungVerWire", 0, tungWireRadius, tungWireLength/2, 0.0*deg, 360.0*deg);
        G4LogicalVolume* logicTungVerWire = new G4LogicalVolume(solidTungVerWire, Tungsten,"TungVerWire_Logic", 0, 0, 0);
        for (G4int i = 0; i < NbOfTungstenWire; i++) {
	new G4PVPlacement(tungVerWireRot, TungVerWirePosition[i], logicTungVerWire, "TungVerWire_Physi", logicMultiWireIonizationChamber, false, i);}
        logicTungVerWire->SetVisAttributes(tungsten);
   
}
// *******************************************************************************************************************
void PassiveProtonBeamLine::XSteeringMagnets()
//--------------------------------------------------------------------------------------------------------------------
{
   // out Divider and Yoke plates & Mother volume for Y-Steering Magnet   
   // 300 mm wide (x-axis), 338 mm hight (y-axis) and 200 mm long (z-axis))
   // 446 mm upstream face of poleshoes
      XOuterDividerAndYokeZPosition = -6978.0*mm+446.0*mm+100*mm;

      G4Box* XouterdividerAndYoke = new G4Box("XOuterDividerAndYoke",300.0/2*mm,338.0/2*mm,200.0/2*mm);
      G4LogicalVolume* logicXOuterDividerAndYoke = new G4LogicalVolume(XouterdividerAndYoke, Air, "XOuterDividerAndYoke");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,XOuterDividerAndYokeZPosition*mm),logicXOuterDividerAndYoke,
							 "XOuterDividerAndYoke",  logicTreatmentRoom, false, 0);
      logicXOuterDividerAndYoke->SetVisAttributes(invisible);

   // Four yoke 
      G4Box* yokeYdir = new G4Box("YokeYdir", 30.5/2*mm, 277.0/2*mm, 200.0/2*mm);
      G4ThreeVector* YokeYdirPosition = new G4ThreeVector[NbOfYoke];
      YokeYdirPosition[0] = G4ThreeVector(-134.75*mm,0.*mm,  0.*mm);
      YokeYdirPosition[1] = G4ThreeVector(134.75 *mm,0.*mm,  0.*mm);
      G4LogicalVolume* logicYokeYdir = new G4LogicalVolume(yokeYdir, Iron, "YokeYdir");
    
      for (G4int i = 0; i < NbOfYoke; i++) {
      new G4PVPlacement(0, YokeYdirPosition[i],logicYokeYdir,"YokeYdir",  logicXOuterDividerAndYoke, false, i);}
      logicYokeYdir->SetVisAttributes(diver_yoke );

      G4Box* yokeXdir = new G4Box("YokeXdir", 300.0/2*mm, 30.5/2*mm, 200.0/2*mm);
      G4ThreeVector* YokeXdirPosition = new G4ThreeVector[NbOfYoke];
      YokeXdirPosition[0] = G4ThreeVector(0.*mm,-153.75*mm,  0.*mm);
      YokeXdirPosition[1] = G4ThreeVector(0.*mm, 153.75*mm,  0.*mm);
      G4LogicalVolume* logicYokeXdir = new G4LogicalVolume(yokeXdir, Iron, "YokeXdir");
    
      for (G4int i = 0; i < NbOfYoke; i++) {
      new G4PVPlacement(0, YokeXdirPosition[i],logicYokeXdir,"YokeXdir",  logicXOuterDividerAndYoke, false, i);}
      logicYokeXdir->SetVisAttributes(diver_yoke );

   // X-Steering Magnet 159 mm x  (338-80)mm x 200 mm
      G4Box* XsteeringMagnet = new G4Box("XSteeringMagnet", 159.0/2*mm, 277.0*mm/2, 200.0*mm/2 );
      G4LogicalVolume* logicXSteeringMagnet = new G4LogicalVolume(XsteeringMagnet, Iron, "XSteeringMagnet",XmagField->GetTheFieldManager(),0,0);
      new G4PVPlacement(0, G4ThreeVector(0., 0.,0.),logicXSteeringMagnet,"XSteeringMagnet",  logicXOuterDividerAndYoke, false, 0);
      logicXSteeringMagnet->SetVisAttributes(poleshoe);

   // Centre Air gap
      G4Box* XmagnetAirGap1 = new G4Box("XMagnetAirGap1",139.0*mm/2, 78.0*mm/2, 200.0*mm/2 );  
      G4LogicalVolume* logicXMagnetAirGap1 = new G4LogicalVolume(XmagnetAirGap1, Air, "XMagnetAirGap1");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,0*mm),logicXMagnetAirGap1,"XMagnetAirGap1",  logicXSteeringMagnet, false, 0);
      logicXMagnetAirGap1->SetVisAttributes(air);

      G4Box* XmagnetAirLateralGap = new G4Box("XMagnetAirLateralGap",10.0*mm/2,62.0*mm/2, 200.0*mm/2 );  
      G4ThreeVector* XMagnetAirLateralGapPosition = new G4ThreeVector[NbOfLateralAirGap];
      XMagnetAirLateralGapPosition[0] = G4ThreeVector(-74.5*mm,0.*mm,  0.*mm);
      XMagnetAirLateralGapPosition[1] = G4ThreeVector(74.5*mm, 0.*mm,  0.*mm);
      G4LogicalVolume* logicXMagnetAirLateralGap = new G4LogicalVolume(XmagnetAirLateralGap, Air, "XMagnetAirLateralGap");
    
      for (G4int i = 0; i < NbOfLateralAirGap; i++) {
      new G4PVPlacement(0, XMagnetAirLateralGapPosition[i],logicXMagnetAirLateralGap,"XMagnetAirLateralGap",logicXSteeringMagnet,false,i);}
      logicXMagnetAirLateralGap->SetVisAttributes(air);

   // Four cupper coils 40mm x 90mm x 200mm
      G4Box* XmagnetCopperCoil = new G4Box("XMagnetCopperCoil", 40.0/2*mm, 90.0/2*mm, 200.0/2*mm);
      G4ThreeVector* XMagnetCopperCoilPosition = new G4ThreeVector[NbOfCoppercoil];
      XMagnetCopperCoilPosition[0] = G4ThreeVector(-99.5*mm,-93.5*mm,  0.*mm);
      XMagnetCopperCoilPosition[1] = G4ThreeVector(-99.5*mm, 93.5*mm,  0.*mm);
      XMagnetCopperCoilPosition[2] = G4ThreeVector( 99.5*mm,-93.5*mm,  0.*mm);
      XMagnetCopperCoilPosition[3] = G4ThreeVector( 99.5*mm, 93.5*mm,  0.*mm);
      G4LogicalVolume* logicXMagnetCopperCoil = new G4LogicalVolume(XmagnetCopperCoil, Copper, "XMagnetCopperCoil");
    
      for (G4int i = 0; i < NbOfCoppercoil; i++) {
      new G4PVPlacement(0, XMagnetCopperCoilPosition[i],logicXMagnetCopperCoil,"XMagnetCopperCoil",  logicXOuterDividerAndYoke, false, i);}
      logicXMagnetCopperCoil->SetVisAttributes(copper);

  // beam support
     const G4int NbofbeamLineSupportXMG = 2;
     G4Box* beamLineSupportXMG = new G4Box("BeamLineSupportXMG", 250.*mm, 40.0*mm, 10.0*mm);
     G4ThreeVector* beamLinebeamLineSupportXMG = new G4ThreeVector[NbofbeamLineSupportXMG];
     beamLinebeamLineSupportXMG[0] = G4ThreeVector(0.0*mm,-205.0*mm,XOuterDividerAndYokeZPosition-90.0*mm);
     beamLinebeamLineSupportXMG[1] = G4ThreeVector(0.0*mm,-205.0*mm,XOuterDividerAndYokeZPosition+90.0*mm);

     G4LogicalVolume* logicbeamLineSupportXMG = new G4LogicalVolume(beamLineSupportXMG, Air, "BeamLineSupportXMG");    
     for (G4int i = 0; i < NbofbeamLineSupportXMG; i++) {
     new G4PVPlacement(0, beamLinebeamLineSupportXMG[i],logicbeamLineSupportXMG, "BeamLineSupportXMG",  logicTreatmentRoom, false, i);}

     logicbeamLineSupportXMG -> SetVisAttributes(yellow);

}

// *******************************************************************************************************************
void PassiveProtonBeamLine::RangeTrimmerPlate()
//--------------------------------------------------------------------------------------------------------------------
{
   // out Divider and Yoke plates & Mother volume for Y-Steering Magnet   
   // 300 mm wide (x-axis), 338 mm hight (y-axis) and 200 mm long (z-axis))
   // Range trimmer plates, the most upstream face is at z=683 mm

    //G4double defaultRangeTrimmerPlateZPosition =-6978.0*mm+683.0*mm+(3*0.622*mm)+0.622/2*mm; 
      RangeTrimmerPlateZPosition = -6978.0*mm+683.0*mm+(3*0.622*mm)+0.622/2*mm; 

      G4Box* rangeTrimmerPlate = new G4Box("RangeTrimmerPlate",150.0/2*mm,150.0/2*mm,4.354/2*mm);
      G4LogicalVolume* logicRangeTrimmerPlate = new G4LogicalVolume(rangeTrimmerPlate, Air, "RangeTrimmerPlate");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,RangeTrimmerPlateZPosition),logicRangeTrimmerPlate,"RangeTrimmerPlate",  logicTreatmentRoom, false, 0);
      logicRangeTrimmerPlate->SetVisAttributes(invisible);


   // Setting plate positions
      G4double z = 0.0*mm;
      G4ThreeVector* TrimmerThiolytePlatePosition = new G4ThreeVector[NbOfRangeTrimmer];
      for (G4int i = 0; i < NbOfRangeTrimmer; i++) {
      z = ((NbOfRangeTrimmer/2*0.622) - 0.622/2 - (i*0.622));
      TrimmerThiolytePlatePosition[i] = G4ThreeVector(0.0, 0.0, z*mm); }

   // Volume Definitions  
      G4Box* trimmerThiolytePlate = new G4Box("TrimmerThiolytePlate", 150.0/2*mm,150.0/2*mm, 0.622/2);
      G4LogicalVolume* logicTrimmerPlate = new G4LogicalVolume(trimmerThiolytePlate, Thiolyte,"TrimmerThiolytePlate_Logic", 0, 0, 0);
      for (G4int i = 0; i < NbOfRangeTrimmer; i++) {
      new G4PVPlacement(0,TrimmerThiolytePlatePosition[i], logicTrimmerPlate, "TrimmerThiolytePlate_Physi", logicRangeTrimmerPlate, false, i);}
      logicTrimmerPlate->SetVisAttributes(thiolyte);
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::LeadPlate()
//--------------------------------------------------------------------------------------------------------------------
{
   // out Divider and Yoke plates & Mother volume for Y-Steering Magnet   
   // 300 mm wide (x-axis), 338 mm hight (y-axis) and 200 mm long (z-axis))
   // Lead plates is at z= 774 mm (upstream face)
      LeadShootPlateZPosition =-6978.0*mm+774.0*mm+0.527/2*mm; 

      G4Box* leadShootPlate = new G4Box("LeadShootPlate",150.0/2*mm,100.0/2*mm,0.527/2*mm);
      G4LogicalVolume* logicLeadShootPlate = new G4LogicalVolume(leadShootPlate, Aluminum, "LeadShootPlate");
      new G4PVPlacement(0, G4ThreeVector(0., 0.,LeadShootPlateZPosition),logicLeadShootPlate,"LeadShootPlate",logicTreatmentRoom, false, 0);
      logicLeadShootPlate->SetVisAttributes(aluminum);

      G4Tubs* leadPlate = new G4Tubs("LeadPlate", 0.0*mm, 75.0/2*mm, 0.527/2*mm, 0.0*deg, 360.0*deg);
      G4LogicalVolume* logicLeadPlate = new G4LogicalVolume(leadPlate, Lead, "LeadPlate");
      new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),logicLeadPlate,"LeadPlate",  logicLeadShootPlate, false, 0);
      logicLeadPlate->SetVisAttributes(lead);
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::Wedge(G4double Range)
//--------------------------------------------------------------------------------------------------------------------
{

if (removeWedge != "Yes")
   {

   // Mother Volume for wedges (at z= 895 mm (Mid))
      WedgeMotherZPosition =-6978.0*mm+895.0*mm; 

      G4RotationMatrix* wedgeRot = new G4RotationMatrix;
      wedgeRot->rotateY(-90.0*deg);
      G4Box* wedgeMother = new G4Box("WedgeMother",150.0/2*mm,1000.0/2*mm,200.0/2*mm);
      G4LogicalVolume* logicWedgeMother = new G4LogicalVolume(wedgeMother, Air, "WedgeMother_log");
      new G4PVPlacement(wedgeRot, G4ThreeVector(0., 0.,WedgeMotherZPosition),logicWedgeMother,"WedgeMother",logicTreatmentRoom, false, 0);
      logicWedgeMother->SetVisAttributes(invisible);


   // Each wedge is 400 mm long (y-axis), 150 mm wide (x-axis) and 90 mm thick (z-axis) at the base of the wedge
   // The gap between the 400 mm long vertical faces of the two wedges is 28 mm    
      G4double wedgePos = ((Range - 16.67121*cm)/0.7439);
      DownWedgeVerPos = -wedgePos;
      UpWedgeVerPos = wedgePos;


      G4Trap* wedgeDown = new G4Trap("WedgeDown",150.0/2*mm,400.0/2*mm,90.0/2*mm, 0.00001*mm);
      G4LogicalVolume* logicWedgeDown = new G4LogicalVolume(wedgeDown, Graphite, "WedgeDown");
      physiWedgeDown = new G4PVPlacement(0, G4ThreeVector(14.0*mm, DownWedgeVerPos,0.*mm),logicWedgeDown,"WedgeDown",logicWedgeMother, false, 0);
      logicWedgeDown->SetVisAttributes(graphite);

      G4RotationMatrix* wedgeUpRot = new G4RotationMatrix;
      wedgeUpRot->rotateZ(180.0*deg);
      G4Trap* wedgeUp = new G4Trap("WedgeUp",150.0/2*mm,400.0/2*mm,90.0/2*mm, 0.00001*mm);
      G4LogicalVolume* logicWedgeUp = new G4LogicalVolume(wedgeUp, Graphite, "WedgeUp");
      physiWedgeUp = new G4PVPlacement(wedgeUpRot, G4ThreeVector(-14.0*mm, UpWedgeVerPos,0.0*mm),logicWedgeUp,"WedgeUp",logicWedgeMother, false, 0);
      logicWedgeUp->SetVisAttributes(graphite);

      G4RunManager::GetRunManager() -> GeometryHasBeenModified();
      G4cout << "  __________________________________"<< G4endl;
      G4cout << "                                   "<< G4endl;
      G4cout << "            Wedge set up "<< G4endl;
      G4cout << "  __________________________________"<< G4endl;
      G4cout << " The Wedge is moved to "<< wedgePos <<" mm"<<G4endl;
      G4cout << " up and down along Y axis. " <<G4endl;
      G4cout << " Please make sure that the leadplate must be" <<G4endl;
      G4cout << " removed before introducing the wedge"<<G4endl;
      G4cout << " The Range "<< Range/cm <<" cm was set" <<G4endl;

    }
}
// *******************************************************************************************************************
void PassiveProtonBeamLine::MultiLayerFaradayCup()
//--------------------------------------------------------------------------------------------------------------------
{
  // Uperstream Perspex casing with 90 mm diameter air gap, outer diameter is 128 mm, the upstream face is at the 1026 mm
     G4double uperstreamPerspexPos=-6978.0*mm+1026.0*mm+5.0/2*mm;

     G4Tubs* uperstreamPerspex= new G4Tubs("UperstreamPerspex",90.0/2*mm, 128.0/2*mm,5.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logiUperstreamPerspex= new G4LogicalVolume(uperstreamPerspex, Perspex3, "UperstreamPerspex");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,uperstreamPerspexPos),logiUperstreamPerspex,"UperstreamPerspex",logicTreatmentRoom, false, 0);
     logiUperstreamPerspex->SetVisAttributes(perspex);

  // MLFC, the upstream face is at the 1031 mm (1st Lexan disk)
  // Multi Layer Faraday Cup (MLFC) is a 40 channel device (40 Lexan discs and 40 brass discs)
  // Perspex casing with 98 mm diameter air gap that consists of 40 Lexan and brass plates, outer diameter is 128 mm
     MLFCZPosition =-6978.0*mm+1031.0*mm+66.0/2*mm;

     G4Tubs* multiLayerFaradayCup= new G4Tubs("MultiLayerFaradayCup",98.0/2*mm, 128.0/2*mm,66.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logiMultiLayerFaradayCup= new G4LogicalVolume(multiLayerFaradayCup, Perspex3, "MultiLayerFaradayCup");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,MLFCZPosition),logiMultiLayerFaradayCup,"MultiLayerFaradayCup",  logicTreatmentRoom, false, 0);
     logiMultiLayerFaradayCup->SetVisAttributes(perspex);

  // Setting Lexan 40 plate (1mm thickness & 98 mm outer diameter and 30mm inner diameter) 
  // positions from upstream position of the perspex casing
     G4double z1 = 0.0*mm;
     const G4int NbOfLexanPlate=40;        
     G4ThreeVector* LexanPlatePosition = new G4ThreeVector[NbOfLexanPlate];
     for (G4int i = 0; i < NbOfLexanPlate; i++) {
     z1 = -32.5 + i*1.65;
     LexanPlatePosition[i] = G4ThreeVector(0.0, 0.0, MLFCZPosition+z1*mm); }
 
     G4Tubs* lexanPlate= new G4Tubs("LexanPlate",30.0/2*mm, 98.0/2*mm, 1.0/2*mm, 0,CLHEP::twopi);
     G4LogicalVolume* logicLexanPlate = new G4LogicalVolume(lexanPlate, Lexan,"LexanPlate_Logic");
     for (G4int i = 0; i < NbOfLexanPlate; i++) {
     new G4PVPlacement(0,LexanPlatePosition[i], logicLexanPlate, "LexanPlate_Physi",logicTreatmentRoom, false, i);} 
     logicLexanPlate->SetVisAttributes(lexan);

  // Setting 40 Brass plate (0.65mm thickness & 98 mm outer diameter and 30mm inner diameter)
  // positions from downstream face of the perspex casing
     G4double z2 = 0.0*mm;
     const G4int NbOfBrassPlate=40;         
     G4ThreeVector* BrassPlatePosition = new G4ThreeVector[NbOfBrassPlate];
     for (G4int i = 0; i < NbOfBrassPlate; i++) {
     z2 = 32.675 - i*1.65;
     BrassPlatePosition[i] = G4ThreeVector(0.0, 0.0, MLFCZPosition+z2*mm); }

     G4Tubs* brassPlate= new G4Tubs("BrassPlate",30.0/2*mm, 98.0/2*mm, 0.65/2*mm, 0,CLHEP::twopi);
     G4LogicalVolume* logicBrassPlate = new G4LogicalVolume(brassPlate, Brass,"BrassPlate_Logic");
     for (G4int i = 0; i < NbOfLexanPlate; i++) {
     new G4PVPlacement(0,BrassPlatePosition[i], logicBrassPlate, "BrassPlate_Physi",logicTreatmentRoom, false, i);}
     logicBrassPlate->SetVisAttributes(brass);
 
  // Downstream Perspex casing with circular aperture of 128 mm outer diameter, 90mm inner diameter and has a length 18 mm along z axis  
  // the upstream face is at the 1097 mm
     G4double PerspexStopperCasingPos=-6978.0*mm+1097.0*mm+18.0/2*mm;
     G4Tubs* perspexStopperCasing= new G4Tubs("PerspexStopperCasing",90.0/2*mm, 128.0/2*mm,18.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logiPerspexStopperCasing= new G4LogicalVolume(perspexStopperCasing, Perspex3, "PerspexStopperCasing");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,PerspexStopperCasingPos),logiPerspexStopperCasing,"PerspexStopperCasing", logicTreatmentRoom, false, 0);
     logiPerspexStopperCasing->SetVisAttributes(perspex);

  // Brass beam Stopper with circular aperture of 90 mm outer diameter, 30mm inner diameter and has a length 18 mm along z axis  
  // the upstream face is at the 1097 mm
     G4Tubs* brassBeamStopper1= new G4Tubs("BrassBeamStopper1",30.0/2*mm, 90.0/2*mm,18.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logiBeamStopper1= new G4LogicalVolume(brassBeamStopper1, Brass, "BrassBeamStopper1");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,PerspexStopperCasingPos),logiBeamStopper1,"BrassBeamStopper1", logicTreatmentRoom, false, 0);
     logiBeamStopper1->SetVisAttributes(brass);

  // Brass beam Stopper with circular aperture of 100 mm outer diameter, 30mm inner diameter and has a length 8 mm along z axis 
  // the upstream face is at the 1115 mm
     G4double brassBeamStopper2Pos=-6978.0*mm+1115.0*mm+8.0/2*mm;
     G4Tubs* brassBeamStopper2= new G4Tubs("BrassBeamStopper2",30.0/2*mm, 100.0/2*mm,8.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logiBeamStopper2= new G4LogicalVolume(brassBeamStopper2, Brass, "BrassBeamStopper2");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,brassBeamStopper2Pos),logiBeamStopper2,"BrassBeamStopper2", logicTreatmentRoom, false, 0);
     logiBeamStopper2->SetVisAttributes(brass);

  // beam support
     G4Box* beamLineSupportMFC = new G4Box("BeamLineSupportMFC", 250.*mm, 30.0*mm, 30.0*mm);
     G4LogicalVolume* logicBeamLineSupportMFC = new G4LogicalVolume(beamLineSupportMFC, Air, "BeamLineSupportMFC");
     new G4PVPlacement(0, G4ThreeVector(0.0*mm,-210.0*mm,-5903.*mm),"BeamLineSupportMFC", logicBeamLineSupportMFC, 
					   physicalTreatmentRoom, false, 0);
     logicBeamLineSupportMFC -> SetVisAttributes(yellow);

     const G4int NbofbeamSupport = 2;
     G4Box* beamLineVerSupport = new G4Box("BeamLineVerSupport", 10.*mm, 100.0*mm, 10.0*mm);
     G4ThreeVector* beamLineVerSupportPosition = new G4ThreeVector[NbofbeamSupport];
     beamLineVerSupportPosition[0] = G4ThreeVector(40.0*mm, -150.0*mm,  -5903.*mm);
     beamLineVerSupportPosition[1] = G4ThreeVector(-40.0*mm, -150.0*mm,  -5903.*mm);

     G4LogicalVolume* logicbeamLineVerSupport = new G4LogicalVolume(beamLineVerSupport, Air, "BeamLineVerSupport");    
     for (G4int i = 0; i < NbofbeamSupport; i++) {
     new G4PVPlacement(0, beamLineVerSupportPosition[i],logicbeamLineVerSupport, "BeamLineVerSupport",  logicTreatmentRoom, false, i);}
     logicbeamLineVerSupport -> SetVisAttributes(yellow);
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::RangeModulator()
//--------------------------------------------------------------------------------------------------------------------
{
   // The steel cover of thick ness 5 mm and 115 mm long in the z direction
   // the distance of the upstream face of the entrance window is 1137mm
   // the distance of the downstream face of the entrance window is 1252mm

     G4Box* steelCover1 = new G4Box("SteelCover",500.0/2*mm,400.0/2*mm,115.0/2*mm);
   //  G4Box* steelCover2 = new G4Box("SteelCover",490.0/2*mm,390.0/2*mm,105.0/2*mm);
   //  G4SubtractionSolid* steelCover = new G4SubtractionSolid("SteelCover",steelCover1, steelCover2);
     G4LogicalVolume* logicSteelCover = new G4LogicalVolume(steelCover1, Air, "SteelCover");
     physicalRangeModulator = new G4PVPlacement(0, G4ThreeVector(0., 0.,-5783.5*mm),logicSteelCover,"SteelCover",logicTreatmentRoom, false, 0);
     logicSteelCover->SetVisAttributes(invisible);
      
   // The both upstream and downstream cover have a circular aperture of 85 mm diameter and 5 mm thickness
      const G4int NbOfSteelaperture=2;
      G4Tubs* steelaperture= new G4Tubs("SteelAperture",0.0/2*mm, 85.0/2*mm,5.0/2*mm,0,CLHEP::twopi);
      G4ThreeVector* SteelAperturePosition = new G4ThreeVector[NbOfSteelaperture];
      SteelAperturePosition[0] = G4ThreeVector(0.*mm,0.*mm, 55.0*mm);
      SteelAperturePosition[1] = G4ThreeVector(0.*mm, 0.*mm,-55.0*mm);
      G4LogicalVolume* logicSteelaperture = new G4LogicalVolume(steelaperture, Air, "SteelAperture");
    
      for (G4int i = 0; i < NbOfSteelaperture; i++) {
      new G4PVPlacement(0, SteelAperturePosition[i],logicSteelaperture,"SteelAperture",  logicSteelCover, false, i);}
      logicSteelaperture->SetVisAttributes(invisible);

   // The following lines construc a typical modulator wheel inside the Passive Beam line.
   // Please remember to set the modulator material (default is air, i.e. no modulator!) 
   // in the Modulator37.cc file
      modulator = new Modulator37();
      modulator -> BuildModulator(physicalRangeModulator); 

   // Each of above apertures is covered by a 0.025 mm Kapton protective layer

      const G4int NbOfKaptonCover=2;
      G4Tubs* kaptonCover= new G4Tubs("KaptonCover",0.0/2*mm, 85.0/2*mm,0.025/2*mm,0,CLHEP::twopi);
      G4ThreeVector* KaptonCoverPosition = new G4ThreeVector[NbOfKaptonCover];
      KaptonCoverPosition[0] = G4ThreeVector(0.*mm,0.*mm,  57.4875*mm);
      KaptonCoverPosition[1] = G4ThreeVector(0.*mm, 0.*mm,-57.4875*mm);
      G4LogicalVolume* logicKaptonCover = new G4LogicalVolume(kaptonCover, Kapton, "KaptonCover");
    
      for (G4int i = 0; i < NbOfKaptonCover; i++) {
      new G4PVPlacement(0, KaptonCoverPosition[i],logicKaptonCover,"KaptonCover",  logicSteelCover, false, i);}
      logicKaptonCover->SetVisAttributes(kapton);
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::RangeMonitoriThemba()
//--------------------------------------------------------------------------------------------------------------------
{
 

     // The position of the new range monitor is that where the previous 'occluding' ring appear in the layout. 
     // i.e.the 2nd scatterer (mounting plate for ring & stopper) or 3065mm from the vacuum window. 
     // This is the position of the downstream face of the range monitor.

      G4double z = -(3912.418+50.0)*mm;

     G4ThreeVector positionMotherMod = G4ThreeVector(0. *mm, 0. *mm, z);
     G4Box* solidMotherMod = new G4Box("MotherMod", 220.0/2 *mm, 220.0/2 *mm, 100.0/2 *mm);
     G4LogicalVolume * logicMotherMod = new G4LogicalVolume(solidMotherMod, Vacuum,"NewRangeMonitorLog",0,0,0);
     physiMotherMod = new G4PVPlacement(0,positionMotherMod,  "MotherMod", logicMotherMod, physicalTreatmentRoom, false,0); 
     logicMotherMod -> SetVisAttributes(vacuum); 

   // The following lines construc a typical modulator (iThemba) inside the Passive Beam line.
      rangeMonitor = new RangeMonitor();
      //rangeMonitor -> BuildModulator(physicalTreatmentRoom); 
      rangeMonitor -> BuildModulator(logicMotherMod); 

}

// *******************************************************************************************************************
void PassiveProtonBeamLine::BeamRangeMonitor(G4double value)
//--------------------------------------------------------------------------------------------------------------------
{
   // The Range Monitor consists of a stack of parallel plate ionization chambers spaced with brass degrader plates
   // The ionization chambers are made by PC board, lateral diamension is 200 mm x 200 mm, have a 100mm diameter aperture
   // The overall length of the range monitor (along z direction) is 90 mm
   // The total set of brass is thic enough to stop the beam completely and acts as a  collimator
  if (removeRangeMonitor != "Yes")
  {    
     RangeMonitorZPos = -6978*mm +1589*mm + 45*mm + value; 

     G4Box* rangeMonitor = new G4Box("RangeMonitor",200.0/2*mm,200.0/2*mm,90.0/2*mm);
     G4LogicalVolume* logicRangeMonitor = new G4LogicalVolume(rangeMonitor, Air, "RangeMonitor");
     physiRangeMonitor=new G4PVPlacement(0, G4ThreeVector(0., 0.,RangeMonitorZPos),logicRangeMonitor,"RangeMonitor",logicTreatmentRoom, false, 0);
     logicRangeMonitor->SetVisAttributes(invisible);

  // 30mm Brass
     G4Box* brassPlate30 = new G4Box("BrassPlate30",200.0/2*mm,200.0/2*mm,30.0/2*mm);
     G4Tubs* brassAperture30= new G4Tubs("BrassAperture30",0.0/2*mm, 100.0/2*mm,30.1/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* brassDegrader30 = new G4SubtractionSolid("BrassDegrader30",brassPlate30, brassAperture30);

     G4LogicalVolume* logicBrassDegrader30 = new G4LogicalVolume(brassDegrader30, Brass, "BrassDegrader30");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-24.*mm),logicBrassDegrader30,"BrassDegrader30",logicRangeMonitor, false, 0);
     logicBrassDegrader30->SetVisAttributes(brass);

  // 3mm Brass
     G4Box* brassPlate3 = new G4Box("BrassPlate3",200.0/2*mm,200.0/2*mm,3.0/2*mm);
     G4Tubs* brassAperture3= new G4Tubs("BrassAperture",0.0/2*mm, 100.0/2*mm,3.01/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* brassDegrader3 = new G4SubtractionSolid("BrassDegrader3",brassPlate3, brassAperture3);

     G4LogicalVolume* logicBrassDegrader3 = new G4LogicalVolume(brassDegrader3, Brass, "BrassDegrader3");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-3.5*mm),logicBrassDegrader3,"BrassDegrader3",logicRangeMonitor, false, 0);
     logicBrassDegrader3->SetVisAttributes(brass);

  // 2mm Brass
     G4Box* brassPlate2 = new G4Box("BrassPlate2",200.0/2*mm,200.0/2*mm,2.0/2*mm);
     G4Tubs* brassAperture2= new G4Tubs("BrassAperture2",0.0/2*mm, 100.0/2*mm,2.01/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* brassDegrader2 = new G4SubtractionSolid("BrassDegrader2",brassPlate2, brassAperture2);

     const G4int NbOfBrass2=2;
     G4ThreeVector* brassPlate2Position = new G4ThreeVector[NbOfBrass2];
     brassPlate2Position[0] = G4ThreeVector(0.*mm,0.*mm,  3.0*mm);
     brassPlate2Position[1] = G4ThreeVector(0.*mm, 0.*mm,9.0*mm);
     G4LogicalVolume* logicBrassDegrader2 = new G4LogicalVolume(brassDegrader2, Brass, "BrassDegrader2");

     for (G4int i = 0; i < NbOfBrass2; i++) {
     new G4PVPlacement(0, brassPlate2Position[i],logicBrassDegrader2,"BrassDegrader2",  logicRangeMonitor, false, i);}
     logicBrassDegrader2->SetVisAttributes(brass);

  // 1mm Brass
     G4Box* brassPlate1 = new G4Box("BrassPlate1",200.0/2*mm,200.0/2*mm,1.0/2*mm);
     G4Tubs* brassAperture1= new G4Tubs("BrassAperture1",0.0/2*mm, 100.0/2*mm,1.01/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* brassDegrader1 = new G4SubtractionSolid("BrassDegrader1",brassPlate1, brassAperture1);

     const G4int NbOfBrass1=2;
     G4ThreeVector* brassPlate1Position = new G4ThreeVector[NbOfBrass1];
     brassPlate1Position[0] = G4ThreeVector(0.*mm,0.*mm,  14.5*mm);
     brassPlate1Position[1] = G4ThreeVector(0.*mm, 0.*mm,19.5*mm);
     G4LogicalVolume* logicBrassDegrader1 = new G4LogicalVolume(brassDegrader1, Brass, "BrassDegrader1");

     for (G4int i = 0; i < NbOfBrass1; i++) {
     new G4PVPlacement(0, brassPlate1Position[i],logicBrassDegrader1,"BrassDegrader1",  logicRangeMonitor, false, i);}
     logicBrassDegrader1->SetVisAttributes(brass);

  // 1mm PC Board
     G4Box* pcPlate1 = new G4Box("PcPlate1",200.0/2*mm,200.0/2*mm,1.0/2*mm);
     G4Tubs* pcAperture1= new G4Tubs("PcAperture1",0.0/2*mm, 100.0/2*mm,1.01/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* pcBoard1 = new G4SubtractionSolid("PcBoard1",pcPlate1, pcAperture1);

     const G4int NbOfPcBoard1=14;
     G4ThreeVector* PcBoard1Position = new G4ThreeVector[NbOfPcBoard1];

     PcBoard1Position[0]  = G4ThreeVector(0.*mm, 0.*mm,-44.5*mm);
     PcBoard1Position[1]  = G4ThreeVector(0.*mm, 0.*mm,-41.5*mm);
     PcBoard1Position[2]  = G4ThreeVector(0.*mm, 0.*mm, -8.5*mm);
     PcBoard1Position[3]  = G4ThreeVector(0.*mm, 0.*mm, -5.5*mm);
     PcBoard1Position[4]  = G4ThreeVector(0.*mm, 0.*mm, -1.5*mm);
     PcBoard1Position[5]  = G4ThreeVector(0.*mm, 0.*mm,  1.5*mm);
     PcBoard1Position[6]  = G4ThreeVector(0.*mm, 0.*mm,  4.5*mm);
     PcBoard1Position[7]  = G4ThreeVector(0.*mm, 0.*mm,  7.5*mm);
     PcBoard1Position[8]  = G4ThreeVector(0.*mm, 0.*mm, 10.5*mm);
     PcBoard1Position[9]  = G4ThreeVector(0.*mm, 0.*mm, 13.5*mm);
     PcBoard1Position[10] = G4ThreeVector(0.*mm, 0.*mm, 15.5*mm);
     PcBoard1Position[11] = G4ThreeVector(0.*mm, 0.*mm, 18.5*mm);
     PcBoard1Position[12] = G4ThreeVector(0.*mm, 0.*mm, 20.5*mm);
     PcBoard1Position[13] = G4ThreeVector(0.*mm, 0.*mm, 43.5*mm);

     G4LogicalVolume* logicPcBoard1 = new G4LogicalVolume(pcBoard1, PCBoard, "PcBoard1");

     for (G4int i = 0; i < NbOfPcBoard1; i++) {
     new G4PVPlacement(0, PcBoard1Position[i],logicPcBoard1,"PcBoard1",  logicRangeMonitor, false, i);}
     logicPcBoard1->SetVisAttributes(pcBoard);

  // 2mm PC Board
     G4Box* pcPlate2 = new G4Box("PcPlate2",200.0/2*mm,200.0/2*mm,2.0/2*mm);
     G4Tubs* pcAperture2= new G4Tubs("PcAperture2",0.0/2*mm, 100.0/2*mm,2.01/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* pcBoard2 = new G4SubtractionSolid("PcBoard1",pcPlate2, pcAperture2);

     const G4int NbOfPcBoard2=5;
     G4ThreeVector* PcBoard2Position = new G4ThreeVector[NbOfPcBoard2];

     PcBoard2Position[0] = G4ThreeVector(0.*mm, 0.*mm, 24.*mm);
     PcBoard2Position[1] = G4ThreeVector(0.*mm, 0.*mm, 28.*mm);
     PcBoard2Position[2] = G4ThreeVector(0.*mm, 0.*mm, 32.*mm);
     PcBoard2Position[3] = G4ThreeVector(0.*mm, 0.*mm, 36.*mm);
     PcBoard2Position[4] = G4ThreeVector(0.*mm, 0.*mm, 40.*mm);
     
     G4LogicalVolume* logicPcBoard2 = new G4LogicalVolume(pcBoard2, PCBoard, "PcBoard2");

     for (G4int i = 0; i < NbOfPcBoard2; i++) {
     new G4PVPlacement(0, PcBoard2Position[i],logicPcBoard2,"PcBoard2",  logicRangeMonitor, false, i);}
     logicPcBoard2->SetVisAttributes(pcBoard);

  // beam support
     G4Box* beamLineSupportRM = new G4Box("BeamLineSupportRM", 250.*mm, 30.0*mm, 30.0*mm);
     G4LogicalVolume* logicBeamLineSupportRM = new G4LogicalVolume(beamLineSupportRM, Air, "BeamLineSupportRM");
     phybeamLineSupportRM = new G4PVPlacement(0, G4ThreeVector(0.0*mm,-210.0*mm,RangeMonitorZPos),"BeamLineSupportRM", logicBeamLineSupportRM, 
					   physicalTreatmentRoom, false, 0);
     logicBeamLineSupportRM -> SetVisAttributes(yellow);

     G4Box* beamLineVerSupport1 = new G4Box("BeamLineVerSupport1", 20.*mm, 30.0*mm, 20.0*mm);
     G4LogicalVolume* logicbeamLineVerSupport1 = new G4LogicalVolume(beamLineVerSupport1, Air, "BeamLineVerSupport1");
     phybeamLineSupport1 = new G4PVPlacement(0, G4ThreeVector(60.0*mm,-150.0*mm,RangeMonitorZPos), 
                               "BeamLineVerSupport1",logicbeamLineVerSupport1,  physicalTreatmentRoom, false, 0);  
     logicbeamLineVerSupport1 -> SetVisAttributes(yellow); 

     G4Box* beamLineVerSupport2 = new G4Box("BeamLineVerSupport2", 20.*mm, 30.0*mm, 20.0*mm);
     G4LogicalVolume* logicbeamLineVerSupport2 = new G4LogicalVolume(beamLineVerSupport2, Air, "BeamLineVerSupport2");
     phybeamLineSupport2 = new G4PVPlacement(0, G4ThreeVector(-60.0*mm, -150.0*mm,  RangeMonitorZPos),
                                            "BeamLineVerSupport2",logicbeamLineVerSupport2,   physicalTreatmentRoom, false, 0);  
     logicbeamLineVerSupport2 -> SetVisAttributes(yellow); 

    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
    G4cout << "The Range Monitor is moved to "<< value/cm <<" mm its downstream stop position along the Z axis" <<G4endl;
   } 
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::OccludingRingAndCentralStopper()
//--------------------------------------------------------------------------------------------------------------------
{
  // It is he scond scatterer, centered on the beam axis.
  // Brass Foil, 242 mm wide, 242 mm hight and 1.164 mm thick. Its position is fixed
     G4Box* brassFoil = new G4Box("BrassFoil",242.0/2*mm,242.0/2*mm,1.164/2*mm);
     G4LogicalVolume* logicBrassFoil = new G4LogicalVolume(brassFoil, Brass, "BrassFoil");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-3912.418*mm),logicBrassFoil,"BrassFoil",logicTreatmentRoom, false, 0);
     logicBrassFoil->SetVisAttributes(brass);

  // Inner and outer diameter of Outer Occluding ring are has48.173 mm and 72.358 & 50.0 mm along
     G4Tubs* occludingRing= new G4Tubs("OccludingRing",48.173/2*mm, 72.358/2*mm,50.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicOccludingRing= new G4LogicalVolume(occludingRing, Brass, "OccludingRing");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-3938.0*mm),logicOccludingRing,"OccludingRing",  logicTreatmentRoom, false, 0);
     logicOccludingRing->SetVisAttributes(brass);
  
  // The centre stopper has a diameter of 26.975 mm and 50.0 mm along
     G4Tubs* centreStopper= new G4Tubs("CentreStopper",0.0*mm, 26.975/2*mm,50.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicCentreStopper= new G4LogicalVolume(centreStopper, Brass, "CentreStopper");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-3938.0*mm),logicCentreStopper,"CentreStopper",  logicTreatmentRoom, false, 0);
     logicCentreStopper->SetVisAttributes(brass);

  // beam support
     G4Box* beamLineSupportOccl = new G4Box("BeamLineSupportOccl", 250.*mm, 30.0*mm, 30.0*mm);
     G4LogicalVolume* logicBeamLineSupportOccl = new G4LogicalVolume(beamLineSupportOccl, Air, "BeamLineSupportOccl");
     new G4PVPlacement(0, G4ThreeVector(0.0*mm,-210.0*mm,-3912.418*mm),"BeamLineSupportOccl", logicBeamLineSupportOccl, 
					   physicalTreatmentRoom, false, 0);
     logicBeamLineSupportOccl -> SetVisAttributes(yellow);

     const G4int NbofbeamSupport = 2;
     G4Box* beamLineVerSupport = new G4Box("BeamLineVerSupport", 20.*mm, 30.0*mm, 20.0*mm);
     G4ThreeVector* beamLineVerSupportPosition = new G4ThreeVector[NbofbeamSupport];
     beamLineVerSupportPosition[0] = G4ThreeVector(60.0*mm, -150.0*mm,  -3912.418*mm);
     beamLineVerSupportPosition[1] = G4ThreeVector(-60.0*mm, -150.0*mm,  -3912.418*mm);

     G4LogicalVolume* logicbeamLineVerSupport = new G4LogicalVolume(beamLineVerSupport, Air, "BeamLineVerSupport");    
     for (G4int i = 0; i < NbofbeamSupport; i++) {
     new G4PVPlacement(0, beamLineVerSupportPosition[i],logicbeamLineVerSupport, "BeamLineVerSupport",  logicTreatmentRoom, false, i);}
     logicbeamLineVerSupport -> SetVisAttributes(yellow);
} 

// *******************************************************************************************************************
void PassiveProtonBeamLine::ShieldingCollimators()
//--------------------------------------------------------------------------------------------------------------------
{
  // There are five Shielding collimators in the nozzle to protect the patient and electronic equipments

  // Brick wall (Collimator #1), Concrete bricks of 195 mm thickness
  // An aperture of 195mm x 195 mm is  created using G4SubtractionSolid  
     G4Box* wallBrick = new G4Box("BrickWall",2500.0/2*mm,2500.0/2*mm,195.0/2*mm);
     //G4Box* wallBrick = new G4Box("BrickWall",600.0/2*mm,600.0/2*mm,195.0/2*mm);
     G4Box* gapBrick = new G4Box("GapBrick",195.0/2*mm,195.0/2*mm,195.1/2*mm);
     G4SubtractionSolid* brickWall= new G4SubtractionSolid("BrickWall",wallBrick,gapBrick);
     G4LogicalVolume* logicBrickWall = new G4LogicalVolume(brickWall, Concrete, "BrickWallLog");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-3449.5*mm),logicBrickWall,"BrickWall",logicTreatmentRoom, false, 0);
     logicBrickWall->SetVisAttributes(concrete);
     
  // Square Steel Collimator (Collimator #1), 300mm x 300 mm and 51.4 mm thickness
  // A circular aperture of 170 mm diameter is  created using G4SubtractionSolid 
     G4Box* steelSquare = new G4Box("SteelSquare",300.0/2*mm,300.0/2*mm,51.4/2*mm);
     G4Tubs* gapSteel= new G4Tubs("GapSteel",0.0*mm, 170/2*mm, 51.5/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* squareSteel= new G4SubtractionSolid("SquareSteel",steelSquare,gapSteel);
     G4LogicalVolume* logicSquareSteel = new G4LogicalVolume(squareSteel, SS304, "SquareSteelLog");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-3326.3*mm),logicSquareSteel,"SquareSteel",logicTreatmentRoom, false, 0);
     logicSquareSteel->SetVisAttributes(stainlessSteel);

  // Square Lead Collimator (Collimator #1), 500mm x 497 mm and 48.8 mm thickness 
  // A circular aperture of 120 mm diameter is  created using G4SubtractionSolid
     G4Box* leadSquare = new G4Box("SquareLead",500.0/2*mm,497.0/2*mm,48.8/2*mm);
     G4Tubs* gapAir= new G4Tubs("SquareLeadGap",0.0*mm, 120/2*mm, 48.9/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* squareLead= new G4SubtractionSolid("SquareLead",leadSquare,gapAir);
     G4LogicalVolume* logicSquareLead = new G4LogicalVolume(squareLead, Lead, "SquareLeadLog");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,-2434.6*mm),logicSquareLead,"SquareLead",logicTreatmentRoom, false, 0);
     logicSquareLead->SetVisAttributes(lead);


  // The circular Steel Collimator with outer diameter of 320 mm and aperture of diameter 120mm, 50 mm thickness 
     G4Tubs* circularSteelColli= new G4Tubs("CircularSteelColli",120.0/2*mm, 320/2*mm, 50.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicCircularSteelColli= new G4LogicalVolume(circularSteelColli, Iron, "CircularSteelColliLog");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,-1763.0*mm),logicCircularSteelColli,"CircularSteelColli",  logicTreatmentRoom, false, 0);
     logicCircularSteelColli->SetVisAttributes(iron);

  // The circular Brass Collimator with outer diameter of 380 mm and aperture of diameter 100mm, 50.5 mm thickness 
     G4Tubs* circularBrassColli= new G4Tubs("CircularBrassColli",100.0/2*mm, 380/2*mm, 50.5/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicCircularBrassColli= new G4LogicalVolume(circularBrassColli, Iron, "CircularBrassColliLog");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,-525.75*mm),logicCircularBrassColli,"CircularBrassColli",  logicTreatmentRoom, false, 0);
     logicCircularBrassColli->SetVisAttributes(brass);  

}

// *******************************************************************************************************************
void PassiveProtonBeamLine::QuadrantAndMonitorIonizationChamber()
//--------------------------------------------------------------------------------------------------------------------
{
  // 125.0 micro meter thick Al HV foil is kept at the centre of the dual transmission chamber, has a diameter of 220 mm
     G4Tubs* dualAl= new G4Tubs("DualAl",0.0*mm, 220/2*mm, 0.125/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicDualAl= new G4LogicalVolume(dualAl, Aluminum, "DualAl");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,-405.0*mm),logicDualAl,"DualAl",  logicTreatmentRoom, false, 0);
     logicDualAl->SetVisAttributes(aluminum);

  // Two 5.0 micrometer thick aluminised Mylar foil are kept in both side of the thick HV foil with 5.0mm from each
  // has a diameter of 220 mm
     const G4int NbOfDualMylar=2;
     G4Tubs* dualMylar= new G4Tubs("DualMylar",0.0*mm, 220/2*mm, 0.005/2*mm,0,CLHEP::twopi);
     G4ThreeVector* DualMylarPosition = new G4ThreeVector[NbOfDualMylar];
     DualMylarPosition[0] = G4ThreeVector(0.*mm,0.*mm,(-405.0+2.5025)*mm);
     DualMylarPosition[1] = G4ThreeVector(0.*mm,0.*mm,(-405.0-2.5025)*mm);
     G4LogicalVolume* logicDualMylar= new G4LogicalVolume(dualMylar,Mylar, "DualMylar");
    
     for (G4int i = 0; i < NbOfDualMylar; i++) {
     new G4PVPlacement(0, DualMylarPosition[i],logicDualMylar,"DualMylar",  logicTreatmentRoom, false, i);}
     logicDualMylar->SetVisAttributes(mylar);

  // The dual transmisstion chamber is kept in a cylindrical perspex casing 
  // which consists circular apertures in the both faces have a diameter of 200 mm
     const G4int NbOfPerspexAperture=2;
     G4Tubs* dualChamber= new G4Tubs("DualChamber",240.0/2*mm, 250/2*mm, 5.01/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicDualChamber= new G4LogicalVolume(dualChamber, Perspex3, "DualChamber");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,-405.0*mm),logicDualChamber,"DualChamber",  logicTreatmentRoom, false, 0);
     logicDualChamber->SetVisAttributes(perspex); 

     G4Tubs* perspexAperture= new G4Tubs("PerspexAperture",200.0/2*mm, 250/2*mm, 5.0/2*mm,0,CLHEP::twopi);
     G4ThreeVector* PerspexAperturePosition = new G4ThreeVector[NbOfPerspexAperture];
     PerspexAperturePosition[0] = G4ThreeVector(0.*mm,0.*mm,(-405.0+5.01/2)*mm);
     PerspexAperturePosition[1] = G4ThreeVector(0.*mm,0.*mm,(-405.0-5.01/2)*mm);
     G4LogicalVolume* logicPerspexAperture= new G4LogicalVolume(perspexAperture, Perspex3, "PerspexAperture");
    
     for (G4int i = 0; i < NbOfPerspexAperture; i++) {
     new G4PVPlacement(0, PerspexAperturePosition[i],logicPerspexAperture,"PerspexAperture",  logicTreatmentRoom, false, i);}
     logicPerspexAperture->SetVisAttributes(perspex);

  // Downsstream end-cap is closed with a 0.188 mm thick mylar film that protect the foils of the dual transmission chamber
     G4Tubs* endCapMylar= new G4Tubs("EndCapMylar",0.0*mm, 220/2*mm, 0.188/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicEndCapMylar= new G4LogicalVolume(endCapMylar, Mylar, "EndCapMylar");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,(-405.0+12.5965)*mm),logicEndCapMylar,"EndCapMylar",  logicTreatmentRoom, false, 0);
     logicEndCapMylar->SetVisAttributes(mylar); 

  // Perspex caps at each ends with a circular aperture with a diameter of 220 mm. 
     const G4int NbOfPerspexCap=2;    
     G4Tubs* perspexCap= new G4Tubs("PerspexCap",220.0/2*mm, 260/2*mm, 5.0/2*mm,0,CLHEP::twopi);
     G4ThreeVector* PerspexCapPosition = new G4ThreeVector[NbOfPerspexCap];
     PerspexCapPosition[0] = G4ThreeVector(0.*mm,0.*mm,(-405.0+10.0025)*mm);
     PerspexCapPosition[1] = G4ThreeVector(0.*mm,0.*mm,(-405.0-85.0025)*mm);
     G4LogicalVolume* logicPerspexCap= new G4LogicalVolume(perspexCap, Perspex3, "PerspexSupport");
    
     for (G4int i = 0; i < NbOfPerspexCap; i++) {
     new G4PVPlacement(0, PerspexCapPosition[i],logicPerspexCap,"PerspexSupport",  logicTreatmentRoom, false, i);}
     logicPerspexCap->SetVisAttributes(perspex);

 // Two 25.0 micrometer Kapton protective foils separated by three 6.67 micrometer thick gold-plated Kapton electrodes
 // diameter of the Kapton plate is 240.0 mm
     const G4int NbOfkaptonProtective=2;
     G4Tubs* kaptonProtective= new G4Tubs("KaptonProtective",0.0*mm, 240/2*mm, 0.025/2*mm,0,CLHEP::twopi);
     G4ThreeVector* KaptonProtectivePosition = new G4ThreeVector[NbOfkaptonProtective];
     KaptonProtectivePosition[0] = G4ThreeVector(0.*mm,0.*mm,(-405.0-35.5175)*mm);
     KaptonProtectivePosition[1] = G4ThreeVector(0.*mm,0.*mm,(-405.0-82.4925)*mm);
     G4LogicalVolume* logicKaptonProtective= new G4LogicalVolume(kaptonProtective, Kapton, "KaptonProtective");
    
     for (G4int i = 0; i < NbOfkaptonProtective; i++) {
     new G4PVPlacement(0, KaptonProtectivePosition[i],logicKaptonProtective,"KaptonProtective",  logicTreatmentRoom, false, i);}
     logicKaptonProtective->SetVisAttributes(kapton);

  // three 6.67 micrometer thick gold-plated Kapton electrodes
     const G4int NbOfGoldPlated=3;
     G4Tubs* goldPlated= new G4Tubs("GoldPlated",0.0*mm, 240/2*mm, 0.00667/2*mm,0,CLHEP::twopi);
     G4ThreeVector* GoldPlatedPosition = new G4ThreeVector[NbOfGoldPlated];
     GoldPlatedPosition[0] = G4ThreeVector(0.*mm,0.*mm,(-405.0-47.2658325)*mm);
     GoldPlatedPosition[1] = G4ThreeVector(0.*mm,0.*mm,(-405.0-59.008335)*mm);
     GoldPlatedPosition[2] = G4ThreeVector(0.*mm,0.*mm,(-405.0-70.7508375)*mm);
     G4LogicalVolume* logicGoldPlated= new G4LogicalVolume(goldPlated, Gold, "GoldPlated");
    
     for (G4int i = 0; i < NbOfGoldPlated; i++) {
     new G4PVPlacement(0, GoldPlatedPosition[i],logicGoldPlated,"GoldPlated",  logicTreatmentRoom, false, i);}
     logicGoldPlated->SetVisAttributes(gold);

  // The Quadrant and monitor ionization chambers are kept in a cylindrical Al casing 
  // which consists circular apertures in the both faces have a diameter of 205 mm
     const G4int NbOfAlAperture=2;
     G4Tubs* quadrantChamber= new G4Tubs("QuadrantChamber",240.0/2*mm, 250/2*mm, 47.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicQuadrantChamber= new G4LogicalVolume(quadrantChamber, Aluminum, "QuadrantChamber");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,(-405.0-59.005)*mm),logicQuadrantChamber,"QuadrantChamber",  logicTreatmentRoom, false, 0);
     logicQuadrantChamber->SetVisAttributes(aluminum); 

     G4Tubs* alAperture= new G4Tubs("AlAperture",205.0/2*mm, 240/2*mm, 5.0/2*mm,0,CLHEP::twopi);
     G4ThreeVector* AlAperturePosition = new G4ThreeVector[NbOfAlAperture];
     AlAperturePosition[0] = G4ThreeVector(0.*mm,0.*mm,(-405.0-33.005)*mm);
     AlAperturePosition[1] = G4ThreeVector(0.*mm,0.*mm,(-405.0-85.005)*mm);
     G4LogicalVolume* logicAlAperture= new G4LogicalVolume(alAperture, Aluminum, "AlAperture");
    
     for (G4int i = 0; i < NbOfAlAperture; i++) {
     new G4PVPlacement(0, AlAperturePosition[i],logicAlAperture,"AlAperture",  logicTreatmentRoom, false, i);}
     logicAlAperture->SetVisAttributes(aluminum);

  // The assemblies of the ring and quadrant chambers and the dual transmission chamber are kept togther 
  // in a cylindrical Al housing with Perspex end caps. Each end-cap has a circular aperture with a diameter of 220 mm.
  // length of the cylindrical housing is 110 mm
     G4Tubs* cylindricalAl= new G4Tubs("CylindricalAl",250.0/2*mm, 260/2*mm, 92.505/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicCylindricalAl= new G4LogicalVolume(cylindricalAl, Aluminum, "CylindricalAl");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,-443.75*mm),logicCylindricalAl,"CylindricalAl",  logicTreatmentRoom, false, 0);
     logicCylindricalAl->SetVisAttributes(aluminum);  

}

// *******************************************************************************************************************
void PassiveProtonBeamLine::BeamFinalCollimator(G4double innerDiameter)
//--------------------------------------------------------------------------------------------------------------------
{
if (removeBeamFinalCollimator != "Yes")
   {
     
     G4RunManager::GetRunManager() -> GeometryHasBeenModified();
     G4cout<<"Inner Diameter of the final collimator is (mm): "<< innerDiameter << G4endl;
     colliDiameter=innerDiameter;

  // Beam Collimator MotherVolume of thickness 60 mm
     PationCollimatorZPosition = -6978.0*mm+6678*mm+29.0*mm; 

     G4Box* pationCollimator = new G4Box("PationCollimator",250.0/2*mm,250.0/2*mm,58.0/2*mm);
     G4LogicalVolume* logicPationCollimator = new G4LogicalVolume(pationCollimator, Air, "PationCollimator");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,PationCollimatorZPosition),logicPationCollimator,"PationCollimator",  logicTreatmentRoom, false, 0);
     logicPationCollimator->SetVisAttributes(invisible);


  // The base plate of the Beam Collimator (230 mm x 230 mm x 40 mm)
  // A circular aperture of 140.0 mm diameter is  created using G4SubtractionSolid 
     G4Box* plateBase = new G4Box("PlateBase",230.0/2*mm,230.0/2*mm,40.0/2*mm);
     G4Tubs* gapAir= new G4Tubs("GapAir",0.0*mm, 140.0/2*mm, 40.1/2*mm,0,CLHEP::twopi);
     G4SubtractionSolid* basePlate= new G4SubtractionSolid("BasePlate",plateBase,gapAir);
     G4LogicalVolume* logicBasePlate = new G4LogicalVolume(basePlate, SS304, "BasePlate");
     new G4PVPlacement(0, G4ThreeVector(0., 0.,0.),logicBasePlate,"BasePlate",  logicPationCollimator, false, 0);
     logicBasePlate->SetVisAttributes(ss304);

  // The Protractor plate of the Beam Collimator on the downstream face of the base plate 
  // has an outer diameter of 227.0mm, an inner diameter of 151.0mm and a thickness of 6.0mm
     G4Tubs* protractorPlate= new G4Tubs("ProtractorPlate",151.0/2*mm, 227/2*mm, 6/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicProtractorPlate= new G4LogicalVolume(protractorPlate, SS304, "ProtractorPlate");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,22.0*mm),logicProtractorPlate,"ProtractorPlate",  logicPationCollimator, false, 0);
     logicProtractorPlate->SetVisAttributes(ss304);

  // The Collimator holder on the upstream face of the base plate 
  // has an outer diameter of 140.0mm, an inner diameter of 112.0mm and a thickness of 8.0mm
     G4Tubs* upStreamHolder= new G4Tubs("UpStreamHolder",112.0/2*mm, 140/2*mm, 8/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicUpStreamHolder= new G4LogicalVolume(upStreamHolder, SS304, "UpStreamHolder");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,-25.0*mm),logicUpStreamHolder,"UpStreamHolder",  logicPationCollimator, false, 0);
     logicUpStreamHolder->SetVisAttributes(ss304);

  // The Downstream Collimator holder of the base plate 
  // has an outer diameter of 140.0mm, an inner diameter of 120.1mm and a thickness of 50.0mm
     G4Tubs* downStreamHolder= new G4Tubs("DownStreamHolder",120.1/2*mm, 140.0/2*mm, 50.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicDownStreamHolder= new G4LogicalVolume(downStreamHolder, SS304, "DownStreamHolder");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,4.0*mm),logicDownStreamHolder,"DownStreamHolder",  logicPationCollimator, false, 0);
     logicDownStreamHolder->SetVisAttributes(ss304);

  // A stainless steel ring with an inner diameter of 140.0mm, an outer diameter of 150.0mm and a thickness of 6.0mm 
  // fits over the collimator holder and fills the gap between the collimator holder and protractor plate
     G4Tubs* steelRing= new G4Tubs("SteelRing",140.0/2*mm, 150/2*mm, 6/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicSteelRing= new G4LogicalVolume(steelRing, SS304, "SteelRing");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,22.0*mm),logicSteelRing,"SteelRing",  logicPationCollimator, false, 0);
     logicSteelRing->SetVisAttributes(ss304);

  // The Brass inserts that hold the Cerrobend alloy, have outer radious 120mm and inner radious of 100.0 mm.
  // Available thickness are 50.0mm and 60.0mm
     G4Tubs* brassInsert= new G4Tubs("BrassInsert",100.0/2*mm, 120.0/2*mm, 50.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicBrassInsert= new G4LogicalVolume(brassInsert, Brass, "BrassInsert");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,4.0*mm),logicBrassInsert,"BrassInsert",  logicPationCollimator, false, 0);
     logicBrassInsert->SetVisAttributes(brass);

  // Cerrobend alloy Collimator aperature with outer radious of 100.0mm and inner radious of 50mm (treatment field size)
     collimatorAperature= new G4Tubs("CollimatorAperature",colliDiameter/2*mm, 100.1/2*mm, 50.0/2*mm,0,CLHEP::twopi);
     G4LogicalVolume*  logicCollimatorAperature= new G4LogicalVolume(collimatorAperature, Cerrobend, "CollimatorAperature");
     new G4PVPlacement(0, G4ThreeVector(0.0, 0.0,4.0*mm),logicCollimatorAperature,"CollimatorAperature",  logicPationCollimator, false, 0);
     logicCollimatorAperature->SetVisAttributes(cerrobend);
    }
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::SetXMagField(G4double fieldValue)
//--------------------------------------------------------------------------------------------------------------------
{ 
   xMagFieldValue = fieldValue;
   XmagField->SetFieldValue(G4ThreeVector(0.0, fieldValue, 0.0)); 
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::SetYMagField(G4double fieldValue)
//--------------------------------------------------------------------------------------------------------------------
{ 
   yMagFieldValue = fieldValue;
   YmagField->SetFieldValue(G4ThreeVector(-fieldValue, 0.0, 0.0));
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::SetXSpotPosition(G4double posValue)
//--------------------------------------------------------------------------------------------------------------------
{ 
   xSpotPosition = posValue;
   xMagFieldValue = GetXFieldFromPosition(posValue);
   XmagField->SetFieldValue(G4ThreeVector(0.0, xMagFieldValue, 0.0)); 
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::SetYSpotPosition(G4double posValue)
//--------------------------------------------------------------------------------------------------------------------
{ 
   ySpotPosition = posValue;
   yMagFieldValue = GetYFieldFromPosition(posValue);
   YmagField->SetFieldValue(G4ThreeVector(-yMagFieldValue, 0.0, 0.0));
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::SetZSpotPosition(G4double posValue)
//--------------------------------------------------------------------------------------------------------------------
{ 
   zSpotPosition = posValue;
}

// *******************************************************************************************************************
G4double PassiveProtonBeamLine::GetXFieldFromPosition(G4double xSpot)
//--------------------------------------------------------------------------------------------------------------------
{
  // Elementary Constants
     G4double c    = 299792458*m/s;              // speed of light (m/s)
     G4double Mp   = 1.67262158E-27*kg;          // proton mass (kg)
     G4double e    = 1.602176462E-19*coulomb;    // proton charge (C)
     G4double moc2 = 938.271998*MeV;             // rest mass * speed of light squared (MeV)

  // Nozzle Constants
     G4double yMagLength   = 20.00*cm;           // width of y-magnet (cm)
     G4double xMagPosition = -63.32*cm;          // downside position of x-magnet (cm)
     G4double xMagLength   = 20.00*cm;           // width of x-magnet (cm)
  
  // Get link to PrimaryGeneratorAction for access to beam specifics
     G4RunManager* runManager = G4RunManager::GetRunManager();
     PrimaryGeneratorAction* generator = (PrimaryGeneratorAction*) runManager->GetUserPrimaryGeneratorAction();

     G4ParticleDefinition* particle = generator->GetParticleSource()->GetParticleDefinition();
     G4String Particle = particle->GetParticleName();
     G4double energy = generator->GetParticleSource()->GetParticleEnergy()/MeV;

  // Energy-based values
     G4double VoverC = (sqrt(1 - pow((1 + energy/moc2), -2)));  // (unitless)
     G4double initialVelocity = (c * VoverC);                   // initial beam velocity in z-direction (m/s)
     G4double relMass = (Mp / sqrt(1 - pow(VoverC, 2)));        // relativistic mass (kg)

  // for loop to create lookup values for Bx
     G4double Vzy = initialVelocity;
     G4double thetaY = asin((e * yMagLength * yMagFieldValue)/(relMass * Vzy));
     G4double Vzx = Vzy * cos(thetaY);
     std::vector <G4double> xField;
     std::vector <G4double> xPos;
     G4int index = 1;
     for(G4double ib = -1.00*tesla; ib < 1.01*tesla; ib += 0.01*tesla) {  //actual max/min = 0.39 T

  // Fill x-field vector
     if(fabs(ib) < 1e-10) { xField.push_back(0.0); }
     else { xField.push_back(ib); }

  // Fill x-position vector
     G4double thetaX = asin((e * xMagLength * ib)/(relMass * Vzx));
     G4double posX = ((xMagPosition - zSpotPosition) * tan(thetaX)) + (xMagLength * ((1 - cos(thetaX))/sin(thetaX)));
     if(fabs(thetaX) < 1e-10) { xPos.push_back(0.0); }
     else { xPos.push_back(posX); }

  // increment index
     index = index + 1;
  }
/*
 // Print fields and positions for interpolation
     for(int i = 0; i < (int)xField.size(); i++) {
     G4double xf = xField.at(i);
     G4double xp = xPos.at(i);
     G4cout << " xField = " << std::setprecision(4) << std::setw(5) << xf/tesla << " T, xPos = " << std::setw(7) << xp/cm << " cm" << G4endl;}
*/
  // while loop to flip through data and find closest points
     int i = 0;
     while(xSpot > xPos.at(i)) { i++; }

  // interpolate data
     G4double xBfield = xField.at(i-1) + ((xSpot - xPos.at(i-1)) * ((xField.at(i) - xField.at(i-1))/(xPos.at(i) - xPos.at(i-1))));

  // Print out adjacent points and interpolated field value
     G4cout << G4endl;
     G4cout << " xPos(i-1) = " << std::setprecision(4) << std::setw(7) << xPos.at(i-1)/cm
	    << " cm, xField(i-1) = " << std::setprecision(4) << std::setw(7) << xField.at(i-1)/tesla << " T" << G4endl;
     G4cout << " xSpot     = " << std::setprecision(4) << std::setw(7) << xSpot/cm 
	    << " cm, xBfield     = "  << std::setprecision(4) << std::setw(7) << xBfield/tesla 
	    << " T, zPos = " << zSpotPosition/cm << " cm" << G4endl;
     G4cout << " xPos(i)   = " << std::setprecision(4) << std::setw(7) << xPos.at(i)/cm
	    << " cm, xField(i)   = " << std::setprecision(4) << std::setw(7) << xField.at(i)/tesla << " T" << G4endl;

     return xBfield;
}

// *******************************************************************************************************************
G4double PassiveProtonBeamLine::GetYFieldFromPosition(G4double ySpot)
//--------------------------------------------------------------------------------------------------------------------
{ 

  // Elementary Constants
     G4double c    = 299792458*m/s;             // speed of light (m/s)
     G4double Mp   = 1.67262158E-27*kg;         // proton mass (kg)
     G4double e    = 1.602176462E-19*coulomb;   // proton charge (C)
     G4double moc2 = 938.271998*MeV;            // rest mass * speed of light squared (MeV)

  // Nozzle Constants
    G4double yMagPosition = -66.98*cm;          // downside position of y-magnet (cm)
    G4double yMagLength   = 20.00*cm;           // width of y-magnet (cm)

  // Get link to PrimaryGeneratorAction for access to beam specifics
     /*G4RunManager* runManager = G4RunManager::GetRunManager();
     PrimaryGeneratorAction* generator = (PrimaryGeneratorAction*) runManager->GetUserPrimaryGeneratorAction();

     G4ParticleDefinition* particle = generator->GetParticleSource()->GetParticleDefinition();
     G4double energy = generator->GetParticleSource()->GetParticleEnergy()/MeV;*/
     
     G4double energy = 200.0/MeV;

  // Energy-based values
     G4double VoverC = (sqrt(1 - pow((1 + energy/moc2), -2)));  // (unitless)
     G4double initialVelocity = (c * VoverC);                   // initial beam velocity in z-direction (m/s)
     G4double relMass = (Mp / sqrt(1 - pow(VoverC, 2)));        // relativistic mass (kg)

  // for loop to create lookup values for By
     G4double Vzy = initialVelocity;
     std::vector <G4double> yField;
     std::vector <G4double> yPos;
     G4int index = 1;
     for(G4double ib = -1.00*tesla; ib < 1.01*tesla; ib += 0.01*tesla) {  //actual max/min = 0.72 T

  // Fill y-field vector
     if(fabs(ib) < 1e-10) { yField.push_back(0.0); }
     else { yField.push_back(ib); }

  // Fill y-position vector
     G4double thetaY = asin((e * yMagLength * ib)/(relMass * Vzy));
     G4double posY = ((yMagPosition - zSpotPosition) * tan(thetaY)) + (yMagLength * ((1 - cos(thetaY))/sin(thetaY)));
     if(fabs(thetaY) < 1e-10) { yPos.push_back(0.0); }
     else { yPos.push_back(posY); }

  // increment index
     index = index + 1;
  }
/*
  // Print fields and positions for interpolation
     for(int i = 0; i < (int)yField.size(); i++) {
     G4double yf = yField.at(i);
     G4double yp = yPos.at(i);
     G4cout << " yField = " << std::setprecision(4) << std::setw(5) << yf/tesla << " T, yPos = " << std::setw(7) << yp/cm << " cm" << G4endl;}
*/
  // while loop to flip through data and find closest points
     int i = 0;
     while(ySpot > yPos.at(i)) { i++; }

  // interpolate data
     G4double yBfield = yField.at(i-1) + ((ySpot - yPos.at(i-1)) * ((yField.at(i) - yField.at(i-1))/(yPos.at(i) - yPos.at(i-1))));

  // Print out adjacent points and interpolated field value
     G4cout << G4endl;
     G4cout << " yPos(i-1) = " << std::setprecision(4) << std::setw(7) << yPos.at(i-1)/cm
	    << " cm, yField(i-1) = " << std::setprecision(4) << std::setw(7) << yField.at(i-1)/tesla << " T" << G4endl;
     G4cout << " ySpot     = " << std::setprecision(4) << std::setw(7) << ySpot/cm 
	    << " cm, yBfield     = "  << std::setprecision(4) << std::setw(7) << yBfield/tesla 
	    << " T, zPos = " << zSpotPosition/cm << " cm" << G4endl;
     G4cout << " yPos(i)   = " << std::setprecision(4) << std::setw(7) << yPos.at(i)/cm
	    << " cm, yField(i)   = " << std::setprecision(4) << std::setw(7) << yField.at(i)/tesla << " T" << G4endl;
     G4cout << G4endl;

     return yBfield;
}

// *******************************************************************************************************************
//                                       *********** Messenger ***********
// *******************************************************************************************************************
void PassiveProtonBeamLine::SetModulatorAngle(G4double value)
//--------------------------------------------------------------------------------------------------------------------
{  
  modulator -> SetModulatorAngle(value);
  G4RunManager::GetRunManager() -> GeometryHasBeenModified();
}
/*
// *******************************************************************************************************************
void PassiveProtonBeamLine::SetRangeMonitorZPosition(G4double value)
//--------------------------------------------------------------------------------------------------------------------
{
  physiRangeMonitor -> SetTranslation(G4ThreeVector(0., 0., -6978*mm +1589*mm + 45*mm + value)); 
  phybeamLineSupportRM -> SetTranslation(G4ThreeVector(0.0*mm,-210.0*mm, -6978*mm +1589*mm + 45*mm + value));
  phybeamLineSupport1 ->SetTranslation(G4ThreeVector(60.0*mm, -150.0*mm,  -6978*mm +1589*mm + 45*mm + value)); 
  phybeamLineSupport2 ->SetTranslation(G4ThreeVector(-60.0*mm, -150.0*mm,  -6978*mm +1589*mm + 45*mm + value)); 

  G4RunManager::GetRunManager() -> GeometryHasBeenModified();
  G4cout << "The Range Monitor is moved to "<< value/mm <<" mm its downstream stop position along the Z axis" <<G4endl;
}

// *******************************************************************************************************************
void PassiveProtonBeamLine::SetRangeWedgeYPosition(G4double value)
//--------------------------------------------------------------------------------------------------------------------
{
  physiWedgeDown -> SetTranslation(G4ThreeVector(14.0*mm, -value,0.*mm)); 
  physiWedgeUp   -> SetTranslation(G4ThreeVector(-14.0*mm, value,0.*mm)); 
  G4RunManager::GetRunManager() -> GeometryHasBeenModified();
  G4cout << "The Wedge is moved to "<< value/mm <<" mm up and down Y axis" <<G4endl;
}
// *******************************************************************************************************************

*/


