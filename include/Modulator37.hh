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

#ifndef Modulator37_H
#define Modulator37_H 1

class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class NozzleMaterial;


class Modulator37
{
public:

  Modulator37();
  ~Modulator37();

  void BuildModulator(G4VPhysicalVolume*);  
  void SetModulatorAngle(G4double);

private:

  NozzleMaterial* nozzleMaterial; 
  G4RotationMatrix* rm;
  G4VPhysicalVolume* physiMotherMod;
  G4Material* Air;

  G4LogicalVolume* logicColler;

  G4Tubs*            solidMod0;    
  G4LogicalVolume*   logicMod0;   
  G4VPhysicalVolume* physiMod0;
  
  
  G4Tubs*            solidMod1;   
  G4LogicalVolume*   logicMod1;   
  G4VPhysicalVolume* physiMod1;
  
  G4Tubs*            solidMod2;   
  G4LogicalVolume*   logicMod2;   
  G4VPhysicalVolume* physiMod2;
  
  G4Tubs*            solidMod3;   
  G4LogicalVolume*   logicMod3;   
  G4VPhysicalVolume* physiMod3;
  
  G4Tubs*            solidMod4;  
  G4LogicalVolume*   logicMod4;  
  G4VPhysicalVolume* physiMod4;

  G4Tubs*            solidMod5;  
  G4LogicalVolume*   logicMod5;   
  G4VPhysicalVolume* physiMod5;
  
  G4Tubs*            solidMod6;  
  G4LogicalVolume*   logicMod6;  
  G4VPhysicalVolume* physiMod6;
  
  G4Tubs*            solidMod7;   
  G4LogicalVolume*   logicMod7;   
  G4VPhysicalVolume* physiMod7;
  
  G4Tubs*            solidMod20;  
  G4LogicalVolume*   logicMod20;  
  G4VPhysicalVolume* physiMod20;

  G4Tubs*            solidMod21;  
  G4LogicalVolume*   logicMod21;   
  G4VPhysicalVolume* physiMod21;

  G4Tubs*            solidMod22;    
  G4LogicalVolume*   logicMod22;  
  G4VPhysicalVolume* physiMod22;
  
  G4Tubs*            solidMod23;   
  G4LogicalVolume*   logicMod23; 
  G4VPhysicalVolume* physiMod23;
  
  G4Tubs*            solidMod24;  
  G4LogicalVolume*   logicMod24;  
  G4VPhysicalVolume* physiMod24;

  G4Tubs*            solidMod25;   
  G4LogicalVolume*   logicMod25;  
  G4VPhysicalVolume* physiMod25;

  G4Tubs*            solidMod26;    
  G4LogicalVolume*   logicMod26;  
  G4VPhysicalVolume* physiMod26;
  
  G4Tubs*            solidMod27;  
  G4LogicalVolume*   logicMod27;  
  G4VPhysicalVolume* physiMod27;
    
  G4Tubs*            solidMod30;  
  G4LogicalVolume*   logicMod30;  
  G4VPhysicalVolume* physiMod30;
  
  G4Tubs*            solidMod31;   
  G4LogicalVolume*   logicMod31;  
  G4VPhysicalVolume* physiMod31;
  
  G4Tubs*            solidMod32;  
  G4LogicalVolume*   logicMod32;   
  G4VPhysicalVolume* physiMod32;
  
  G4Tubs*            solidMod33;  
  G4LogicalVolume*   logicMod33;   
  G4VPhysicalVolume* physiMod33;
  
  G4Tubs*            solidMod34;   
  G4LogicalVolume*   logicMod34;  
  G4VPhysicalVolume* physiMod34;
  
  G4Tubs*            solidMod35;  
  G4LogicalVolume*   logicMod35;  
  G4VPhysicalVolume* physiMod35;

  G4Tubs*            solidMod36;  
  G4LogicalVolume*   logicMod36;  
  G4VPhysicalVolume* physiMod36;
  
  G4Tubs*            solidMod37;   
  G4LogicalVolume*   logicMod37;   
  G4VPhysicalVolume* physiMod37;
  
  G4Tubs*            solidMod40;   
  G4LogicalVolume*   logicMod40;  
  G4VPhysicalVolume* physiMod40;
  
  G4Tubs*            solidMod41;    
  G4LogicalVolume*   logicMod41;  
  G4VPhysicalVolume* physiMod41;
  
  G4Tubs*            solidMod42;  
  G4LogicalVolume*   logicMod42;  
  G4VPhysicalVolume* physiMod42;
  
  G4Tubs*            solidMod43;   
  G4LogicalVolume*   logicMod43;  
  G4VPhysicalVolume* physiMod43;
  
  G4Tubs*            solidMod44;  
  G4LogicalVolume*   logicMod44;   
  G4VPhysicalVolume* physiMod44;
  
  G4Tubs*            solidMod45;    
  G4LogicalVolume*   logicMod45;   
  G4VPhysicalVolume* physiMod45;

  G4Tubs*            solidMod46;   
  G4LogicalVolume*   logicMod46;   
  G4VPhysicalVolume* physiMod46;
  
  G4Tubs*            solidMod47;  
  G4LogicalVolume*   logicMod47; 
  G4VPhysicalVolume* physiMod47;
  
   
};
#endif
