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
	// PassiveProtonBeamLine.hh; 
	// 

#ifndef PassiveProtonBeamLine_H
#define PassiveProtonBeamLine_H 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "MagneticField.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include <vector>

class G4VPhysicalVolume;
class DetectorConstruction;
class NozzleMaterial;
class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class NozzleMessenger;
class Modulator37;
class RangeMonitor;
class PassiveProtonBeamLineMessenger;


// Declared Constants
const G4int NbOfLeadPlate = 2;         // # of profile monitor windows
const G4int NbOfKaptonCasing=2;        // # of Kapton Casing
const G4int NbOfCoppercoil=4;          // # of copper coils
const G4int NbOfCopperAirGap=2;        // # of air gaps between coperplates
const G4int NbOfLateralAirGap=2;       // # of lateral air gap of Poleshoe
const G4int NbOfPerspexSupport=2;      // # of Perspex Support frames
const G4int NbOfKaptonLayer=2;         // # of Kapton layer
const G4int NbOfAlPlate=2;             // # of Aluminium Plates
const G4int NbOfTungstenWire=48;       // # of tungsten wire
const G4int NbOfRangeTrimmer=7;        // # of Range Trimer Plates
const G4int NbOfYoke=2;                // # of Yoke
const G4int NbOfPerspexCap=2;          // # of Perspex Caps



class PassiveProtonBeamLine : public G4VUserDetectorConstruction
{
public:
	
	PassiveProtonBeamLine();
	~PassiveProtonBeamLine();
	
	G4VPhysicalVolume* Construct();  
	void BeamLineSupport();

       void BuildNozzle(G4VPhysicalVolume* nozzleMother);
       void VacuumTube();
       void ReferenceIonizationChamber();
       void YSteeringMagnets();
       void MultiWireIonizationChamber();
       void XSteeringMagnets();
       void RangeTrimmerPlate();
       void LeadPlate();
       void Wedge(G4double value);
       void MultiLayerFaradayCup();
       void RangeModulator();
       void RangeMonitoriThemba();
       void BeamRangeMonitor(G4double value);
       void OccludingRingAndCentralStopper();
       void ShieldingCollimators();
       void QuadrantAndMonitorIonizationChamber();
       void BeamFinalCollimator(G4double innerDiameter);

  
    // Scanning Magnet Functions
       void          SetXMagField(G4double);
       void          SetYMagField(G4double);
       void          SetXSpotPosition(G4double);
       void          SetYSpotPosition(G4double);
       void          SetZSpotPosition(G4double);
       void          SetSpotXposMin(G4double val)            {spotXposMin = val;};
       void          SetSpotXposMax(G4double val)            {spotXposMax = val;};
       void          SetSpotYposMin(G4double val)            {spotYposMin = val;};
       void          SetSpotYposMax(G4double val)            {spotYposMax = val;};

    // Specific Element Functions
       void          SetRemoveVacuumTube(G4String name)                              {removeVacuumTube = name;};
       void          SetRemoveReferenceIonizationChamber(G4String name)              {removeReferenceIonizationChamber = name;};
       void          SetRemoveYSteeringMagnets(G4String name)                        {removeYSteeringMagnets = name;};
       void          SetRemoveMultiWireIonizationChamber(G4String name)              {removeMultiWireIonizationChamber = name;};
       void          SetRemoveXSteeringMagnets(G4String name)                        {removeXSteeringMagnets = name;};
       void          SetRemoveRangeTrimmerPlate(G4String name)                       {removeRangeTrimmerPlate = name;};
       void          SetRemoveLeadPlate(G4String name)                               {removeLeadPlate = name;};
       void          SetRemoveWedge(G4String name)                                   {removeWedge = name;};
       void          SetRemoveMultiLayerFaradayCup(G4String name)                    {removeMultiLayerFaradayCup = name;};
       void          SetRemoveRangeModulator(G4String name)                          {removeRangeModulator = name;};
       void          RemoveNewRangeMonitoriThemba(G4String name)                     {removeNewRangeMonitoriThemba = name;};
       void          SetRemoveRangeMonitor(G4String name)                            {removeRangeMonitor = name;};
       void          SetRemoveOccludingRingAndCentralStopper(G4String name)          {removeOccludingRingAndCentralStopper = name;};
       void          SetRemoveShieldingCollimators(G4String name)                    {removeShieldingCollimators = name;};
       void          SetRemoveQuadrantAndMonitorIonizationChamber(G4String name)     {removeQuadrantAndMonitorIonizationChamber = name;};
       void          SetRemoveBeamFinalCollimator(G4String name)                     {removeBeamFinalCollimator = name;};
       void          SetWedgepostion(G4double pos)                                   {wedgePostion = pos;};


  // Messanger

        void SetModulatorAngle(G4double angle);
        void SetRangeMonitorZPosition(G4double value);
        void SetRangeWedgeYPosition(G4double value);  

        G4double      GetXSpotPosition()                      {return xSpotPosition;};
        G4double      GetYSpotPosition()                      {return ySpotPosition;};
        G4double      GetZSpotPosition()                      {return zSpotPosition;};
        G4double      GetXFieldFromPosition(G4double);
        G4double      GetYFieldFromPosition(G4double);
        G4double      GetSpotXposMin()                        {return spotXposMin;};
        G4double      GetSpotXposMax()                        {return spotXposMax;};
        G4double      GetSpotYposMin()                        {return spotYposMin;};
        G4double      GetSpotYposMax()                        {return spotYposMax;};
	

private:
     // passive proton line dimensions
	void SetDefaultDimensions(); 
	void ConstructPassiveProtonBeamLine();
        void SetDefaultMaterials();
        void SetDefaultColors();

        G4int DownWedgeVerPos;
        G4int UpWedgeVerPos;
        G4double RangeMonitorZPos; 
        G4double defaultwedge;

     // Pointer to the modulator 
        Modulator37* modulator; 
        RangeMonitor* rangeMonitor; 
	PassiveProtonBeamLineMessenger* passiveMessenger;  

	DetectorConstruction* detectorConstruction;
        NozzleMaterial* nozzleMaterial; 
        G4LogicalVolume* logicTreatmentRoom;
        NozzleMessenger*   nozzleMessenger;
	
	G4VPhysicalVolume* physicalTreatmentRoom;
	G4VPhysicalVolume* physiBeamLineSupport; 
	G4VPhysicalVolume* physiBeamLineCover; 
	G4VPhysicalVolume* physiBeamLineCover2;
        G4VPhysicalVolume* physiRangeMonitor;
        G4VPhysicalVolume* physiWedgeDown;
        G4VPhysicalVolume* physiWedgeUp;
        G4VPhysicalVolume* phybeamLineSupportRM;
        G4VPhysicalVolume* phybeamLineSupport1;
        G4VPhysicalVolume* phybeamLineSupport2;
        G4VPhysicalVolume* physicalRangeModulator;
        G4VPhysicalVolume* physiMotherMod;
 

        G4Tubs* collimatorAperature;
        G4double colliDiameter;

        G4Region* BrickcollRegion;
        G4Region* SqSteelcollRegion;
        G4Region* LeadcollRegion;
        G4Region* CirSteelcollRegion;
        G4Region* CirBrasscollRegion;
        G4Region* PatientcollRegion;
        G4Region* WedgeRegion;
        G4Region* leadShootPlateRegion;
        G4Region* rangeTrimerplateRegion;
        G4Region* MultiWireIonChaRegion;
        G4Region* VacuumTubeRegion;
        G4Region* VacuumTubeHavarWindowRegion;
        G4Region* ReferenceIonizationChambeRegion;
        G4Region* ReferenceIonChamCasingRegion;
        G4Region* ReferenceIonChamperspexMountRegion;
        G4Region* newRangeMonitorRegion;
        G4Region* RangeModulatorRegion;

        G4Region* NaI33CllimatorRegion;
        G4Region* NaI44CllimatorRegion;
        G4Region* NaI66CllimatorRegion;

        G4Region* NaI33WaxRegion;
        G4Region* NaI44WaxRegion;
        G4Region* NaI66WaxRegion;

     // Scanning Magnet Variables
        MagneticField*   YmagField;
        G4FieldManager*  myYFieldMgr;
        MagneticField*   XmagField;
        G4FieldManager*  myXFieldMgr;
        G4double         xMagFieldValue;
        G4double         yMagFieldValue;
        G4double         xSpotPosition;
        G4double         ySpotPosition;
        G4double         zSpotPosition;
        G4double         spotXposMin;
        G4double         spotXposMax;
        G4double         spotYposMin;
        G4double         spotYposMax;

    // Specific Element VNbOfAlPlateariables
       G4String   removeVacuumTube;
       G4String   removeReferenceIonizationChamber;
       G4String   removeYSteeringMagnets;
       G4String   removeMultiWireIonizationChamber;
       G4String   removeXSteeringMagnets;
       G4String   removeRangeTrimmerPlate;
       G4String   removeLeadPlate;
       G4String   removeWedge;
       G4String   removeMultiLayerFaradayCup;
       G4String   removeRangeModulator;
       G4String   removeRangeMonitor;
       G4String   removeOccludingRingAndCentralStopper;
       G4String   removeShieldingCollimators;
       G4String   removeQuadrantAndMonitorIonizationChamber;
       G4String   removeBeamFinalCollimator;
       G4String   removeNewRangeMonitoriThemba;

       G4String  set2x2collimator;
       G4String  set3x3collimator;
       G4String  set4x4collimator;
       G4String  set6x6collimator;
       G4String  setcollimator;

    // Z coordinate
       G4double   vacuumTubeZPosition;
       G4double   HavarWindowZPosition;
       G4double YOuterDividerAndYokeZPosition;
       G4double XOuterDividerAndYokeZPosition;
       G4double MultiWireIonizationChamberZPosition;
       G4double RangeTrimmerPlateZPosition;
       G4double LeadShootPlateZPosition;
       G4double MLFCZPosition;
       G4double PationCollimatorZPosition;
       G4double WedgeMotherZPosition;
       G4double wedgePostion;

    // Specific Color Variables
       G4VisAttributes* blue;
       G4VisAttributes* white;         
       G4VisAttributes* invisible;     
       G4VisAttributes* yellow;        
       G4VisAttributes* gray;         
       G4VisAttributes* red;          
       G4VisAttributes* purple;       
       G4VisAttributes* green;         
       G4VisAttributes* darkGreen;     
       G4VisAttributes* black;         
       G4VisAttributes* brass;        
       G4VisAttributes* lead;          
       G4VisAttributes* iron;          
       G4VisAttributes* concrete;     
       G4VisAttributes* copper;       
       G4VisAttributes* aluminum;      
       G4VisAttributes* kapton;       
       G4VisAttributes* water;        
       G4VisAttributes* mylar;         
       G4VisAttributes* lexan;         
       G4VisAttributes* perspex;       
       G4VisAttributes* thiolyte;      
       G4VisAttributes* havar;         
       G4VisAttributes* air;           
       G4VisAttributes* tungsten;      
       G4VisAttributes* cerrobend;	     
       G4VisAttributes* vacuum;        
       G4VisAttributes* poleshoe;      
       G4VisAttributes* diver_yoke;   
       G4VisAttributes* gold;        
       G4VisAttributes* stainlessSteel; 
       G4VisAttributes* graphite;
       G4VisAttributes* pcBoard;
       G4VisAttributes* ss304;
       G4VisAttributes* paraffinWax;
 

	
    // Specific Material Variables
       G4Material* Vacuum;
       G4Material* Brass;
       G4Material* Water;
       G4Material* Havar;
       G4Material* Air;
       G4Material* Carbon;
       G4Material* Aluminum;
       G4Material* Copper;
       G4Material* Tungsten;
       G4Material* Lead;
       G4Material* ABSresin;
       G4Material* Kapton;
       G4Material* Ceramic;
       G4Material* SS304;
       G4Material* Tissue;
       G4Material* Lucite;
       G4Material* Graphite;
       G4Material* Iron;
       G4Material* Cerrobend;
       G4Material* Concrete;
       G4Material* Lexan;
       G4Material* Mylar;
       G4Material* Perspex1;
       G4Material* Perspex2;
       G4Material* Perspex3;
       G4Material* Thiolyte;
       G4Material* Gold;
       G4Material* PCBoard;
       G4Material* ParaffinWax;

	
};
#endif

