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
// Author:    Stephen Peterson          - swpeters@mdanderson.org
//            MD Anderson Cancer Center - Department of Radiation Physics
//            1515 Holcombe Blvd #94    - Houston, TX  77030
// Comments:  Model of scanning proton beam at MD Anderson PTC-H
//
// ********************************************************************

#ifndef MagneticField_H
#define MagneticField_H

#include "G4UniformMagField.hh"

class G4FieldManager;

// ********************************************************************
class MagneticField: public G4UniformMagField
{
  public:
  
    MagneticField(G4ThreeVector);  //  The value of the field
    MagneticField();               //  A zero field
   ~MagneticField();  
      
    // Set the Magnetic Field
    void SetFieldValue(G4ThreeVector fieldVector);

    G4FieldManager* theFieldManager;

    // Returns the Field Manager
    G4FieldManager* GetTheFieldManager();
};

// ********************************************************************
#endif
