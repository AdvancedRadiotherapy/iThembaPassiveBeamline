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

#ifndef NozzleMaterial_h
#define NozzleMaterial_h 1

#include "globals.hh"

class G4Material;

// ********************************************************************
class NozzleMaterial
{ 
  public:
    NozzleMaterial();
   ~NozzleMaterial();

  public:
    void  DefineMaterials();
    G4Material* GetMat(G4String); // Returns the material
    G4Element* GetEle(G4String);
  
  private:

    G4Material* ParaffinWax;
    G4Material* Helium;
    G4Material* HeliumLow;
    G4Material* Carbon;
    G4Material* Nitrogen;
    G4Material* Aluminum;
    G4Material* AlCasing;
    G4Material* Phosphorus;
    G4Material* Calcium;
    G4Material* Titanium;
    G4Material* Copper;
    G4Material* Germanium;
    G4Material* Tungsten;
    G4Material* Lead;
    G4Material* Vacuum;
    G4Material* Air;
    G4Material* Air300K;
    G4Material* Water;
    G4Material* ABSresin;
    G4Material* Kapton;
    G4Material* Ceramic;
    G4Material* TungstenAlloys;
    G4Material* AlOxide;
    G4Material* SS304;
    G4Material* Tissue;
    G4Material* Brass;
    G4Material* Lucite;
    G4Material* Polyethylene;
    G4Material* BoneEqPlas;
    G4Material* NaI;
    G4Material* BGO;
    G4Material* Xenon;
    G4Material* LaBr3;
    G4Material* Oxygen;
    G4Material* Graphite;  
    G4Material* Iron;
    G4Material* Cerrobend;
    G4Material* Concrete;
    G4Material* Havar;
    G4Material* Lexan;
    G4Material* Mylar;
    G4Material* Perspex1;
    G4Material* Perspex2;
    G4Material* Perspex3;
    G4Material* Thiolyte;
    G4Material* PMTube;
    G4Material* Gold;
    G4Material* PCBoard;
    G4Material* Lung;
    G4Material* Bone;
    G4Material* Muscle;
    G4Material* Fat;

 
};

// ********************************************************************
#endif
