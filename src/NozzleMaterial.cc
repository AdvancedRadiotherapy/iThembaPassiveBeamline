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
// Author:    Stephen Peterson          - steve.peterson@uct.ac.za
//            University of Cape Town   - Department of Physics
//            514 RW James              - Rondebosch 7701, SOUTH AFRICA
// Comments:  Model of prompt gamma production from protons hitting target
//
// ********************************************************************

// General libraries
#include "globals.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

// Specific libraries
#include "NozzleMaterial.hh"

// **********************************************************************************
NozzleMaterial::NozzleMaterial():
// **********************************************************************************
    Helium(0),     HeliumLow(0), Carbon(0),    Nitrogen(0),     Aluminum(0),
    Phosphorus(0), Calcium(0),   Titanium(0),  Copper(0),       Germanium(0),
    Tungsten(0),   Lead(0),      Vacuum(0),    Air(0),          Air300K(0),
    Water(0),      ABSresin(0),  Kapton(0),    Ceramic(0),      SS304(0),
    Tissue(0),     Brass(0),     Lucite(0),    Polyethylene(0), BoneEqPlas(0),
    NaI(0),        BGO(0),       Xenon(0),     LaBr3(0), 	Oxygen(0),
    Graphite(0),   Iron(0),      Cerrobend(0), Concrete(0),     Havar(0),
    Lexan(0),      Mylar(0),     Perspex1(0),  Perspex2(0),     Perspex3(0),
    Thiolyte(0),   Gold(0),      PCBoard(0),   AlCasing(0),     AlOxide(0),
    PMTube(0),     TungstenAlloys(0), ParaffinWax(0), Lung(0),   Bone(0),
    Muscle(0),     Fat(0)
{;}

// **********************************************************************************
NozzleMaterial::~NozzleMaterial()
// **********************************************************************************

{
    delete Helium;
    delete HeliumLow;
    delete Carbon;
    delete Nitrogen;
    delete Aluminum;
    delete AlCasing;
    delete Phosphorus;
    delete Calcium;
    delete Titanium;
    delete Copper;
    delete Germanium;
    delete Tungsten;
    delete Lead;
    delete Vacuum;
    delete Air;
    delete Air300K;
    delete Water;
    delete ABSresin;
    delete Kapton;
    delete Ceramic;
    delete TungstenAlloys;
    delete AlOxide;
    delete SS304;
    delete Tissue;
    delete Oxygen;
    delete Brass;
    delete Lucite;
    delete Polyethylene;
    delete BoneEqPlas;
    delete NaI;
    delete BGO;
    delete Xenon;
    delete LaBr3;
    delete Graphite;
    delete Iron;
    delete Cerrobend;
    delete Concrete;
    delete Havar;
    delete Lexan;
    delete Mylar;
    delete Perspex1;
    delete Perspex2;
    delete Perspex3;
    delete Thiolyte;
    delete PMTube;
    delete Gold;
    delete PCBoard;
    delete ParaffinWax;
    delete Lung;
    delete Bone;
    delete Muscle;
    delete Fat;



}

// **********************************************************************************
void NozzleMaterial::DefineMaterials()
// **********************************************************************************
{

//-----------------------------------------------------------------------------------
//                                 Variables
//-----------------------------------------------------------------------------------


    G4double z;          // Atomic number
    G4double a;          // Atomic mass
    G4double density;
    G4int nel;           // Number of elements
    G4int ncomponents;
    G4int natoms;
    G4double abundance;
    G4double massfraction;

//-----------------------------------------------------------------------------------
//                                  Elements
//-----------------------------------------------------------------------------------

 // old version Geant9.5.2

     G4Element* O  = new G4Element("Oxygen"     , "O" , z= 8. , a= 15.9994*g/mole);
     G4Element* H  = new G4Element("Hydrogen"   , "H" , z= 1. , a= 1.0079*g/mole);
     G4Element* Al = new G4Element("Aluminum"   , "Al", z= 13., a= 26.9810*g/mole);
     G4Element* Ar = new G4Element("Argon"      , "Ar", z= 18., a= 39.9481*g/mole);
     G4Element* Bi = new G4Element("Bismuth"    , "Bi", z= 83., a= 208.9804*g/mole);
     G4Element* Br = new G4Element("Bromide"    , "Br", z= 35., a= 79.9000*g/mole);
     G4Element* C  = new G4Element("Carbon"     , "C" , z= 6. , a= 12.0107*g/mole);
     G4Element* Ca = new G4Element("Calcium"    , "Ca", z= 20., a= 40.0784*g/mole);
     G4Element* Cd = new G4Element("Cadmium"    , "Cd", z= 48., a= 112.4110*g/mole);
     G4Element* Cl = new G4Element("Chlorine"   , "Cl", z= 17., a= 35.4530*g/mole);
     G4Element* Co = new G4Element("Cobalt"     , "Co", z= 27., a= 58.933195*g/mole);
     G4Element* Cr = new G4Element("Chromium"   , "Cr", z= 24., a= 51.9961*g/mole);
     G4Element* Cu = new G4Element("Copper"     , "Cu", z= 29., a= 63.5463*g/mole);
     G4Element* Fe = new G4Element("Iron"       , "Fe", z= 26., a= 55.8450*g/mole);
     G4Element* Fl = new G4Element("Fluorine"   , "Fl", z= 9. , a= 18.9984*g/mole);
     G4Element* Ge = new G4Element("Germanium"  , "Ge", z= 32., a= 72.6410*g/mole);
     G4Element* I  = new G4Element("Iodine"     , "I" , z= 53., a= 126.9044*g/mole);
     G4Element* K  = new G4Element("Potassium"  , "K" , z= 19., a= 39.0983*g/mole);
     G4Element* La = new G4Element("Lanthanum"  , "La", z= 57., a= 138.9100*g/mole);
     G4Element* Mg = new G4Element("Magnesium"  , "Mg", z= 12., a=  12.0110*g/mole);
     G4Element* Mn = new G4Element("Manganese"  , "Mn", z= 25., a= 54.9380*g/mole);
     G4Element* Mo = new G4Element("Molybdenum" , "Mo", z= 42., a= 95.9620*g/mole);
     G4Element* N  = new G4Element("Nitrogen"   , "N" , z= 7. , a= 14.0067*g/mole);
     G4Element* Na = new G4Element("Sodium"     , "Na", z= 11., a= 22.9898*g/mole);
     G4Element* Ni = new G4Element("Nickel"     , "Ni", z= 28., a= 58.6934*g/mole);
     G4Element* P  = new G4Element("Phosphorus" , "P" , z= 15., a= 30.9738*g/mole);
     G4Element* Pb = new G4Element("Lead"       , "Pb", z= 82., a= 207.21*g/mole);
     G4Element* S  = new G4Element("Sulfur"     , "S" , z= 16., a= 32.0650*g/mole);
     G4Element* Si = new G4Element("Silicon"    , "Si", z= 14., a= 28.0855*g/mole);
     G4Element* Sn = new G4Element("Tin"        , "Sn", z= 50., a= 118.6900*g/mole);
     G4Element* Tl = new G4Element("Thallium"   , "Tl", z= 81., a= 204.383*g/mole);
     G4Element* Zn = new G4Element("Zinc"       , "Zn", z= 30., a= 65.4094*g/mole);
     G4Element* W  = new G4Element("Tungsten"   , "W", z= 74., a= 183.84*g/mole);

  // New version Geant4.9.6

   /* G4Isotope* iso_O = new G4Isotope("O16",8, 16);
    G4Element* O  = new G4Element("Oxygen", "O16",ncomponents=1);
    O->AddIsotope(iso_O, abundance= 100.*perCent);

    G4Isotope* iso_H = new G4Isotope("H1", 1, 1);
    G4Element* H  = new G4Element("Hydrogen", "H1", ncomponents=1);
    H->AddIsotope(iso_H, abundance= 100.*perCent);

    G4Isotope* iso_Al = new G4Isotope("Al27", 13, 27);
    G4Element* Al  = new G4Element("Aluminum", "Al27", ncomponents=1);
    Al->AddIsotope(iso_Al, abundance= 100.*perCent);

    G4Isotope* iso_Ar = new G4Isotope("Ar40", 18, 40);
    G4Element* Ar  = new G4Element("Argon", "Ar40", ncomponents=1);
    Ar->AddIsotope(iso_Ar, abundance= 100.*perCent);

    G4Isotope* iso_Bi = new G4Isotope("Bi209", 83, 209);
    G4Element* Bi  = new G4Element("Bismuth", "Bi209", ncomponents=1);
    Bi->AddIsotope(iso_Bi, abundance= 100.*perCent);

    G4Isotope* iso_Br = new G4Isotope("Br80", 35, 80);
    G4Element* Br  = new G4Element("Bromide", "Br80", ncomponents=1);
    Br->AddIsotope(iso_Br, abundance= 100.*perCent);

    G4Isotope* iso_C = new G4Isotope("C12", 6, 12);
    G4Element* C  = new G4Element("Carbon", "C12", ncomponents=1);
    C->AddIsotope(iso_C, abundance= 100.*perCent);

    G4Isotope* iso_Ca = new G4Isotope("Ca40", 20, 40);
    G4Element* Ca  = new G4Element("Calcium", "Ca40", ncomponents=1);
    Ca->AddIsotope(iso_Ca, abundance= 100.*perCent);

    G4Isotope* iso_Cd = new G4Isotope("Cd112", 48, 112);
    G4Element* Cd  = new G4Element("Cadmium", "Cd112", ncomponents=1);
    Cd->AddIsotope(iso_Cd, abundance= 100.*perCent);

    G4Isotope* iso_Cl = new G4Isotope("Cl35", 17, 35);
    G4Element* Cl  = new G4Element("Chlorine", "Cl35", ncomponents=1);
    Cl->AddIsotope(iso_Cl, abundance= 100.*perCent);

    G4Isotope* iso_Co = new G4Isotope("Co60", 27, 60);
    G4Element* Co  = new G4Element("Cobalt", "Co60", ncomponents=1);
    Co->AddIsotope(iso_Co, abundance= 100.*perCent);

    G4Isotope* iso_Cr = new G4Isotope("Cr52", 24, 52);
    G4Element* Cr  = new G4Element("Chromium", "Cr52", ncomponents=1);
    Cr->AddIsotope(iso_Cr, abundance= 100.*perCent);

    G4Isotope* iso_Cu = new G4Isotope("Cu64", 29, 64);
    G4Element* Cu  = new G4Element("Copper", "Cu64", ncomponents=1);
    Cu->AddIsotope(iso_Cu, abundance= 100.*perCent);

    G4Isotope* iso_Fe = new G4Isotope("Fe56", 26, 56);
    G4Element* Fe  = new G4Element("Iron", "Fe56", ncomponents=1);
    Fe->AddIsotope(iso_Fe, abundance= 100.*perCent);

    G4Isotope* iso_Fl = new G4Isotope("Fl19", 9, 19);
    G4Element* Fl  = new G4Element("Fluorine", "Fl19", ncomponents=1);
    Fl->AddIsotope(iso_Fl, abundance= 100.*perCent);

    G4Isotope* iso_Ge = new G4Isotope("Ge73", 32, 73);
    G4Element* Ge  = new G4Element("Germanium", "Ge73", ncomponents=1);
    Ge->AddIsotope(iso_Ge, abundance= 100.*perCent);

    G4Isotope* iso_I = new G4Isotope("I127", 53, 127);
    G4Element* I  = new G4Element("Iodine", "I127", ncomponents=1);
    I->AddIsotope(iso_I, abundance= 100.*perCent);

    G4Isotope* iso_K = new G4Isotope("K39", 19, 39);
    G4Element* K  = new G4Element("Potassium", "K39", ncomponents=1);
    K->AddIsotope(iso_K, abundance= 100.*perCent);

    G4Isotope* iso_La = new G4Isotope("La139", 57, 139);
    G4Element* La  = new G4Element("Lanthanum", "La139", ncomponents=1);
    La->AddIsotope(iso_La, abundance= 100.*perCent);

    G4Isotope* iso_Mg = new G4Isotope("Mg12", 12, 24);
    G4Element* Mg  = new G4Element("Magnesium", "Mg12", ncomponents=1);
    Mg->AddIsotope(iso_Mg, abundance= 100.*perCent);

    G4Isotope* iso_Mn = new G4Isotope("Mn80", 25, 55);
    G4Element* Mn  = new G4Element("Manganese", "Mn80", ncomponents=1);
    Mn->AddIsotope(iso_Mn, abundance= 100.*perCent);

    G4Isotope* iso_Mo = new G4Isotope("Mo96", 42, 96);
    G4Element* Mo  = new G4Element("Molybdenum", "Mo96", ncomponents=1);
    Mo->AddIsotope(iso_Mo, abundance= 100.*perCent);

    G4Isotope* iso_N = new G4Isotope("N14", 7, 14);
    G4Element* N  = new G4Element("Nitrogen", "N14", ncomponents=1);
    N->AddIsotope(iso_N, abundance= 100.*perCent);

    G4Isotope* iso_Na = new G4Isotope("Na23", 11, 23);
    G4Element* Na  = new G4Element("Sodium", "Na23", ncomponents=1);
    Na->AddIsotope(iso_Na, abundance= 100.*perCent);

    G4Isotope* iso_Ni = new G4Isotope("Ni57", 28, 57);
    G4Element* Ni  = new G4Element("Nickel", "Ni57", ncomponents=1);
    Ni->AddIsotope(iso_Ni, abundance= 100.*perCent);

    G4Isotope* iso_P = new G4Isotope("P31", 15, 31);
    G4Element* P  = new G4Element("Phosphorus", "P31", ncomponents=1);
    P->AddIsotope(iso_P, abundance= 100.*perCent);

    G4Isotope* iso_Pb = new G4Isotope("Pb207", 82, 207);
    G4Element* Pb  = new G4Element("Lead", "Pb207", ncomponents=1);
    Pb->AddIsotope(iso_Pb, abundance= 100.*perCent);

    G4Isotope* iso_S = new G4Isotope("S32", 16, 32);
    G4Element* S  = new G4Element("Sulfur", "S32", ncomponents=1);
    S->AddIsotope(iso_S, abundance= 100.*perCent);

    G4Isotope* iso_Si = new G4Isotope("Si28", 14, 28);
    G4Element* Si  = new G4Element("Silicon", "Si28", ncomponents=1);
    Si->AddIsotope(iso_Si, abundance= 100.*perCent);

    G4Isotope* iso_Sn = new G4Isotope("Sn119", 50, 119);
    G4Element* Sn  = new G4Element("Tin", "Sn119", ncomponents=1);
    Sn->AddIsotope(iso_Sn, abundance= 100.*perCent);

    G4Isotope* iso_Tl = new G4Isotope("Tl204", 81, 204);
    G4Element* Tl  = new G4Element("Thallium", "Tl204", ncomponents=1);
    Tl->AddIsotope(iso_Tl, abundance= 100.*perCent);

    G4Isotope* iso_Zn = new G4Isotope("Zn65", 30, 65);
    G4Element* Zn  = new G4Element("Zinc", "Zn65", ncomponents=1);
    Zn->AddIsotope(iso_Zn, abundance= 100.*perCent);

    G4Isotope* iso_W = new G4Isotope("W184", 74, 184);
    G4Element* W  = new G4Element("Tungsten", "W184", ncomponents=1);
    W->AddIsotope(iso_W, abundance= 100.*perCent);

*/

//-----------------------------------------------------------------------------------
//                                   Materials
//-----------------------------------------------------------------------------------

    // Helium (using CLHEP STP: 273.15 Kelvin & 101.325 kPa)
       Helium = new G4Material("Helium", z=2.0, a=4.0026*g/mole, density=0.00016632*g/cm3);

    // overwrite computed meanExcitationEnergy with ICRU recommended value 
       Helium->GetIonisation()->SetMeanExcitationEnergy(41.8*eV);

    // Helium (using room temp: 300 Kelvin & 1.97 kPa (from Hitachi data set: MDA-40E-0584R0_Range_Measurement))
       HeliumLow = new G4Material("HeliumLow", z=2.0, a=4.0026*g/mole, density=0.00016632*g/cm3,
			           kStateGas, 300.0*kelvin, 1970*pascal);

    // overwrite computed meanExcitationEnergy with ICRU recommended value 
       HeliumLow->GetIonisation()->SetMeanExcitationEnergy(41.8*eV);


    // old version 

        Carbon      = new G4Material("Carbon", z=6.0, a=12.0107*g/mole, density=2.267*g/cm3); 
        Gold        = new G4Material("Gold", z=79.0, a=196.97*g/mole, density=19.3*g/cm3);
        Graphite    = new G4Material("Graphite", z=6.0, a=12.0107*g/mole, density=1.86*g/cm3); 
        Iron        = new G4Material("Iron", z=26.0,  a= 55.8450*g/mole, density=7.874*g/cm3); 
        Nitrogen    = new G4Material("Nitrogen", z=7.0, a=14.0067*g/mole, density=1.29*mg/cm3);
        Aluminum    = new G4Material("Aluminum", z=13.0, a=26.981*g/mole, density=2.699*g/cm3);
        AlCasing    = new G4Material("AlCasing", z=13.0, a=26.981*g/mole, density=2.94*g/cm3);
        Phosphorus  = new G4Material("Phosphorus", z=15.0, a=30.9737*g/mole, density=1.823*g/cm3);
        Calcium     = new G4Material("Calcium", z=20.0, a=40.0784*g/mole, density=1.550*g/cm3);
        Titanium    = new G4Material("Titanium", z=22.0, a=47.867*g/mole, density=4.507*g/cm3);
        Copper      = new G4Material("Copper", z=29.0, a=63.546*g/mole, density=8.960*g/cm3);
        Germanium   = new G4Material("Germanium", z=32.0, a=72.6410*g/mole, density=5.323*g/cm3);
        Tungsten    = new G4Material("Tungsten", z=74.0, a=183.84*g/mole, density=19.30*g/cm3);
        Lead        = new G4Material("Lead", z=82.0, a=207.21*g/mole, density=11.350*g/cm3);
        Oxygen      = new G4Material("Oxygen", z=8.0, a=15.9994*g/mole, density=1.141*g/cm3);

    // New version 

     /* Oxygen = new G4Material("Oxygen", 1.141*g/cm3, ncomponents=1);
      Oxygen->AddElement(O, massfraction=100.*perCent);

      Carbon = new G4Material("Carbon", 2.267*g/cm3, ncomponents=1);
      Carbon->AddElement(C, massfraction=100.*perCent);

      Graphite = new G4Material("Graphite", 1.86*g/cm3, ncomponents=1);
      Graphite->AddElement(C, massfraction=100.*perCent);

      Iron = new G4Material("Iron", 7.874*g/cm3, ncomponents=1);
      Iron->AddElement(Fe, massfraction=100.*perCent);

      Nitrogen = new G4Material("Nitrogen", 1.29*g/cm3, ncomponents=1);
      Nitrogen->AddElement(N, massfraction=100.*perCent);

      Aluminum = new G4Material("Aluminum", 2.699*g/cm3, ncomponents=1);
      Aluminum->AddElement(Al, massfraction=100.*perCent);

      AlCasing = new G4Material("AlCasing", 2.94*g/cm3, ncomponents=1);
      AlCasing->AddElement(Al, massfraction=100.*perCent);

      Phosphorus = new G4Material("Phosphorus", 1.823*g/cm3, ncomponents=1);
      Phosphorus->AddElement(P, massfraction=100.*perCent);

      Calcium = new G4Material("Calcium", 1.55*g/cm3, ncomponents=1);
      Calcium->AddElement(Ca, massfraction=100.*perCent);

      Copper = new G4Material("Copper", 8.960*g/cm3, ncomponents=1);
      Copper->AddElement(Cu, massfraction=100.*perCent);

      Germanium = new G4Material("Germanium", 5.323*g/cm3, ncomponents=1);
      Germanium->AddElement(Ge, massfraction=100.*perCent);

      Tungsten = new G4Material("Tungsten", 19.30*g/cm3, ncomponents=1);
      Tungsten->AddElement(W, massfraction=100.*perCent);

      Lead = new G4Material("Lead", 11.35*g/cm3, ncomponents=1);
      Lead->AddElement(Pb, massfraction=100.*perCent);
*/
      Vacuum      = new G4Material("Vacuum", z=1.0, a=1.01*g/mole, density=1.e-25*g/cm3,
			             kStateGas, 2.73*kelvin, 3.e-18*pascal);


    // Air (NIST Defn: AIR, DRY (NEAR SEA LEVEL))
       Air = new G4Material("Air", density= 0.001205*g/cm3, nel=4);
       Air->AddElement(C,  0.0124*perCent);
       Air->AddElement(N, 75.5267*perCent);
       Air->AddElement(O, 23.1781*perCent);
       Air->AddElement(Ar, 1.2827*perCent);

    // Air300K (using NIST Defn: AIR, DRY (NEAR SEA LEVEL) & room temp: 300 Kelvin & 101.325 kPa)
       Air300K = new G4Material("Air300K", density= 1.20479*mg/cm3, nel=4, kStateGas, 300.0*kelvin, 1.0*atmosphere);
       Air300K->AddElement(C,  0.0124*perCent);
       Air300K->AddElement(N, 75.5267*perCent);
       Air300K->AddElement(O, 23.1781*perCent);
       Air300K->AddElement(Ar, 1.2827*perCent);

    // Water
       Water = new G4Material("Water", density= 1.0000*g/cm3, nel=2);
       Water->AddElement(H, 11.1894*perCent);
       Water->AddElement(O, 88.8106*perCent);

      // overwrite computed meanExcitationEnergy with ICRU recommended value 
       Water->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);


    // ParaffinWax

       ParaffinWax = new G4Material("ParaffinWax", density= 0.93*g/cm3, nel=2);
       ParaffinWax->AddElement(H, 14.8605*perCent);
       ParaffinWax->AddElement(C, 85.1395*perCent);
       ParaffinWax->GetIonisation()->SetMeanExcitationEnergy(55.9*eV);

    // ABS-Resin
       ABSresin = new G4Material("ABS-Resin", density= 1.041*g/cm3, nel=4);
       ABSresin->AddElement(H,  7.9*perCent);
       ABSresin->AddElement(C, 83.8*perCent); // originally: 83.3 (didn't add up to 100%)
       ABSresin->AddElement(N,  6.5*perCent);
       ABSresin->AddElement(O,  1.8*perCent);

    // Kapton Polyimide Film (ICRU Report 49?)
       Kapton = new G4Material("Kapton", density= 1.4200*g/cm3, nel=4);
       Kapton->AddElement(H,  2.6362*perCent);
       Kapton->AddElement(C, 69.1133*perCent);
       Kapton->AddElement(N,  7.3270*perCent);
       Kapton->AddElement(O, 20.9235*perCent);

    // overwrite computed meanExcitationEnergy with ICRU recommended value 
       Kapton->GetIonisation()->SetMeanExcitationEnergy(79.6*eV);

    // Ceramic (Aluminum Oxide)
       Ceramic = new G4Material("Ceramic", density= 3.97*g/cm3, nel=2);
       Ceramic->AddElement(O , 47.0749*perCent);
       Ceramic->AddElement(Al, 52.9251*perCent);

    // TungstenAlloys (Aluminum Oxide)
       TungstenAlloys = new G4Material("TungstenAlloys", density= 16.96*g/cm3, nel=3);
       TungstenAlloys->AddElement(Ni , 6.0*perCent);
       TungstenAlloys->AddElement(W , 90.0*perCent);
       TungstenAlloys->AddElement(Cu, 4.0*perCent);

    // Aluminum Oxide
       AlOxide = new G4Material("AlOxide", density= 0.55*g/cm3, nel=2);
       AlOxide->AddElement(O , 47.0749*perCent);
       AlOxide->AddElement(Al, 52.9251*perCent);


    // Stainless Steel (Type 304 & 304L)  (0.1% N, 0.4% P, 1.5% Mn, 19.0% Cr, 10.0% Ni, 69.0% Fe)
       SS304 = new G4Material("SS304", density= 8.03*g/cm3, nel=6);
       SS304->AddElement(N,   0.0254*perCent);
       SS304->AddElement(P,   0.2242*perCent);
       SS304->AddElement(Cr, 17.8821*perCent);
       SS304->AddElement(Mn,  1.4916*perCent);
       SS304->AddElement(Fe, 69.7498*perCent);
       SS304->AddElement(Ni, 10.6269*perCent);

    // Tissue (ICRU44 Definition of Adult Average Soft Tissue)
       Tissue = new G4Material("Tissue", density= 1.0300*g/cm3, nel=9);
       Tissue->AddElement(H,  10.5*perCent);
       Tissue->AddElement(C,  25.6*perCent);
       Tissue->AddElement(N,   2.7*perCent);
       Tissue->AddElement(O,  60.2*perCent);
       Tissue->AddElement(Na,  0.1*perCent);
       Tissue->AddElement(P,   0.2*perCent);
       Tissue->AddElement(S,   0.3*perCent);
       Tissue->AddElement(Cl,  0.2*perCent);
       Tissue->AddElement(K,   0.2*perCent);

    // Brass (Type C36000 (free-cutting brass): 61.5% Cu, 35.4% Zn, 3.1% Pb) 
       Brass = new G4Material("Brass", density= 8.496*g/cm3, nel=3);
       Brass->AddElement(Cu, 56.9297*perCent);
       Brass->AddElement(Zn, 33.7131*perCent);
       Brass->AddElement(Pb,  9.3572*perCent);

    // Cerrobend (Ostalloy 158, Wood's metal, Melt-point:70 Celcius: 13.3% Sn, 50% Bi, 26.7% Pb, 10% Cd) 
       Cerrobend = new G4Material("Cerrobend", density= 9.382*g/cm3, nel=4);
       Cerrobend->AddElement(Cd,  6.0160*perCent);
       Cerrobend->AddElement(Sn,  8.4490*perCent);
       Cerrobend->AddElement(Pb, 29.6088*perCent);
       Cerrobend->AddElement(Bi, 55.9262*perCent);

    // Concrete (Portland)
       Concrete = new G4Material("Concrete", density= 2.30*g/cm3, nel=10);
       Concrete->AddElement(H,   1.0000*perCent);
       Concrete->AddElement(C,   0.1000*perCent);
       Concrete->AddElement(O,  52.9107*perCent);
       Concrete->AddElement(Na,  1.6000*perCent);
       Concrete->AddElement(Mg,  0.2000*perCent);
       Concrete->AddElement(Al,  3.3872*perCent);
       Concrete->AddElement(Si, 33.7021*perCent);
       Concrete->AddElement(K,   1.3000*perCent);
       Concrete->AddElement(Ca,  4.4000*perCent);
       Concrete->AddElement(Fe,  1.4000*perCent);

    // Havar (42.0% Co, 19.5% Cr, 12.7% Ni, 2.7% W, 2.2% Mo, 1.6% Mn, 0.2% C, 19.1% Fe)
       Havar = new G4Material("Havar", density= 8.302*g/cm3, nel=8);
       Havar->AddElement(C,    0.0394*perCent);
       Havar->AddElement(Cr,  16.6239*perCent);
       Havar->AddElement(Mn,   1.4412*perCent);
       Havar->AddElement(Fe,  17.4889*perCent);
       Havar->AddElement(Co,  40.5824*perCent);
       Havar->AddElement(Ni,  12.2249*perCent);
       Havar->AddElement(Mo,   3.4606*perCent);
       Havar->AddElement(W,    8.1387*perCent);

    // Lexan 
       Lexan = new G4Material("Lexan", density= 1.200*g/cm3, nel=3);
       Lexan->AddElement(H,  5.5491*perCent);
       Lexan->AddElement(C, 75.5751*perCent);
       Lexan->AddElement(O, 18.8758*perCent);

    // Mylar
       Mylar = new G4Material("Mylar", density= 1.400*g/cm3, nel=3);
       Mylar->AddElement(H,  4.1959*perCent);
       Mylar->AddElement(C, 62.5017*perCent);
       Mylar->AddElement(O, 33.3025*perCent);

    // Thiolyte (for Timmer plates)
       Thiolyte = new G4Material("Thiolyte", density= 1.426*g/cm3, nel=3);
       Thiolyte->AddElement(H,  4.9523*perCent);
       Thiolyte->AddElement(C, 68.8461*perCent);
       Thiolyte->AddElement(O, 26.2016*perCent);

    // PMTube
       PMTube = new G4Material("PMTube", density= 0.94*g/cm3, nel=2);
       PMTube->AddElement(Si, 46.74*perCent);
       PMTube->AddElement(O, 53.26*perCent);

    // Perspex1 (for RM wheels)
       Perspex1 = new G4Material("Perspex1", density= 1.145*g/cm3, nel=3);
       Perspex1->AddElement(H,  8.0538*perCent);
       Perspex1->AddElement(C, 59.9848*perCent);
       Perspex1->AddElement(O, 31.9614*perCent);

    // Perspex2 (for Wellhofer tank wall)
       Perspex2 = new G4Material("Perspex2", density= 1.062*g/cm3, nel=3);
       Perspex2->AddElement(H,  8.0538*perCent);
       Perspex2->AddElement(C, 59.9848*perCent);
       Perspex2->AddElement(O, 31.9614*perCent);

    // Perspex3 (for Blocks for experiments)
       Perspex3 = new G4Material("Perspex3", density= 1.181*g/cm3, nel=3);
       Perspex3->AddElement(H,  8.0538*perCent);
       Perspex3->AddElement(C, 59.9848*perCent);
       Perspex3->AddElement(O, 31.9614*perCent);

    // Lucite (NIST defn for Polymethyl Methacralate)
       Lucite = new G4Material("Lucite", density= 1.19*g/cm3, nel=3);
       Lucite->AddElement(H,  8.0538*perCent);
       Lucite->AddElement(C, 59.9848*perCent);
       Lucite->AddElement(O, 31.9614*perCent);

    // overwrite computed meanExcitationEnergy with ICRU recommended value 
       Lucite->GetIonisation()->SetMeanExcitationEnergy(74.0*eV);

    // Polyethylene (NIST defn for Polyethylene)
       Polyethylene = new G4Material("Polyethylene", density= 0.93*g/cm3, nel=2);
       Polyethylene->AddElement(H, 14.3716*perCent);
       Polyethylene->AddElement(C, 85.6284*perCent);

    // overwrite computed meanExcitationEnergy with ICRU recommended value 
       Polyethylene->GetIonisation()->SetMeanExcitationEnergy(57.4*eV);

    // Bone Eq. Plastic (NIST defn for B-100 bone-equivalent plastic)
       BoneEqPlas = new G4Material("BoneEqPlas", density= 1.82*g/cm3, nel=6);
       BoneEqPlas->AddElement(H,  6.5471*perCent);
       BoneEqPlas->AddElement(C, 53.6945*perCent);
       BoneEqPlas->AddElement(N,  2.1500*perCent);
       BoneEqPlas->AddElement(O,  3.2085*perCent);
       BoneEqPlas->AddElement(Fl,16.7411*perCent);
       BoneEqPlas->AddElement(Ca,17.6589*perCent);

    // Sodium Iodine (Webelements Defn: 15.34% Na, 84.66% I) - density from: Handbook of Chem and Phys (91-92)
       NaI = new G4Material("NaI", density= 3.667*g/cm3, nel=2);
       NaI->AddElement(Na, 15.34*perCent);
       NaI->AddElement(I,  84.66*perCent);
       NaI->GetIonisation()->SetMeanExcitationEnergy(452*eV);
    /*
       G4Material* NaI_Tl = new G4Material("NaI_Tl", density= 3.667*g/cm3, nel=2);
       NaI_Tl->AddElement(Na,1);
       NaI_Tl->AddElement(I,1);

       NaI = new G4Material("NaI", density= 3.667*g/cm3, ncomponents=2);
       NaI->AddMaterial(NaI_Tl,99.6*perCent);
       NaI->AddElement(Tl,0.4*perCent);*/
    /*
       NaI = new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
       NaI->AddElement(Na, natoms=1);
       NaI->AddElement(I , natoms=1);
       NaI->GetIonisation()->SetMeanExcitationEnergy(452*eV);*/

    // Bismuth Germanate: Bi4Ge3O12 / BGO (Webelements Defn: 15.34% Na, 84.66% I) - density from: Handbook of Chem and Phys (91-92)
       BGO = new G4Material("BGO", density= 7.13*g/cm3, nel=3);
       BGO->AddElement(Bi, 67.10*perCent);
       BGO->AddElement(Ge, 17.49*perCent);
       BGO->AddElement(O,  15.41*perCent);

    // Liquid Xenon (density varies with temperature)
       Xenon  = new G4Material("Xenon", z=54.0, a=131.2936*g/mole, density=3.057*g/cm3);

    // LaBr3
       LaBr3 = new G4Material("LaBr3", density= 5.08*g/cm3, nel=2);
       LaBr3->AddElement(Br, 63.3*perCent);
       LaBr3->AddElement(La, 36.7*perCent);

    // PC Board (H15C16O3Si4) 
       PCBoard = new G4Material("PCBoard", density= 1.91*g/cm3, ncomponents=4);
       PCBoard->AddElement(H, natoms=15);
       PCBoard->AddElement(C , natoms=16);
       PCBoard->AddElement(O, natoms=3);
       PCBoard->AddElement(Si , natoms=4);

    // Lung 
       Lung = new G4Material("Lung", density= 0.26*g/cm3, nel=9);
       Lung->AddElement(H, 10.3*perCent);
       Lung->AddElement(C, 10.5*perCent);
       Lung->AddElement(N, 3.1*perCent);
       Lung->AddElement(O, 74.9*perCent);
       Lung->AddElement(Na, 0.2*perCent);
       Lung->AddElement(P, 0.2*perCent);
       Lung->AddElement(S, 0.3*perCent);
       Lung->AddElement(Cl, 0.3*perCent);
       Lung->AddElement(K, 0.2*perCent);

    // Bone
       Bone = new G4Material("Bone", density= 1.85*g/cm3, nel=9);
       Bone->AddElement(H, 3.4*perCent);
       Bone->AddElement(C, 15.5*perCent);
       Bone->AddElement(N, 4.2*perCent);
       Bone->AddElement(O, 43.5*perCent);
       Bone->AddElement(Na, 0.1*perCent);
       Bone->AddElement(Ca, 22.5*perCent);
       Bone->AddElement(P, 10.3*perCent);
       Bone->AddElement(S, 0.3*perCent);
       Bone->AddElement(Mg, 0.2*perCent);

    // Muscle
       Muscle = new G4Material("Muscle", density= 1.05*g/cm3, nel=9);
       Muscle->AddElement(H, 10.2*perCent);
       Muscle->AddElement(C, 14.3*perCent);
       Muscle->AddElement(N, 3.4*perCent);
       Muscle->AddElement(O, 71.0*perCent);
       Muscle->AddElement(Na, 0.1*perCent);
       Muscle->AddElement(P, 0.2*perCent);
       Muscle->AddElement(S, 0.3*perCent);
       Muscle->AddElement(Cl, 0.1*perCent);
       Muscle->AddElement(K, 0.4*perCent);

    // Fat
       Fat = new G4Material("Fat", density= 0.95*g/cm3, nel=7);
       Fat->AddElement(H, 11.4*perCent);
       Fat->AddElement(C, 59.8*perCent);
       Fat->AddElement(N, 0.7*perCent);
       Fat->AddElement(O, 27.8*perCent);
       Fat->AddElement(Na, 0.1*perCent);
       Fat->AddElement(S, 0.1*perCent);
       Fat->AddElement(Cl, 0.1*perCent);


             
}

// **********************************************************************************
G4Material* NozzleMaterial::GetMat(G4String material)
// **********************************************************************************

{
    G4Material* pttoMaterial = G4Material::GetMaterial(material); 
    return pttoMaterial; 
}
/*
// **********************************************************************************
G4Element* NozzleMaterial::GetEle(G4String element)
// **********************************************************************************

{
    G4Element* pttoElement = G4Element::G4Element(element); 
    return pttoElement; 
}

// **********************************************************************************
*/




