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
#include "G4RunManager.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

// Specific libraries
#include "RootAnalysis.hh"
#include "RootMessenger.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

// ROOT libraries
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TTree.h"
#include "TObject.h"
#include "TString.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TCanvas.h"

#include <stdio.h>
#include <math.h>

namespace CLHEP {}
using namespace CLHEP;

  RootAnalysis* RootAnalysis::instance = 0;

  RootAnalysis::RootAnalysis() : verbosity(0)
  {
   G4cout << "RootAnalysis constructing..." << G4endl;
   rootMessenger = new RootMessenger(this);
  
  }

  RootAnalysis::~RootAnalysis() 
  {
    G4cout << "RootAnalysis deleting..." << G4endl;
    delete rootMessenger;
  }

// ***************************************************************************************************
void RootAnalysis::openFiles(const G4String header, const G4long seed)
//----------------------------------------------------------------------------------------------------

{

  // Setting up output file
     filename = header;
     char name[30];
     std::sprintf(name, "_%03i.%06li%s", int(HepRandom::getTheSeed()), seed, ".root");
     filename.append(name);

  // Set new seed and increment values
     G4long newSeed = seed;
     int increment = 11;

  // Convert filename to TString
     TString rootName(filename);

  // weird, but return true if file does not exist

     while (!gSystem->AccessPathName(rootName.Data(), kFileExists) && FileRewriting != "Yes") {
           G4cout << "RootAnalysis - File: " << filename << " already exists!" << G4endl;
    
           // Set new seed value (use original seed)
              newSeed += increment;
    
           // Set the new seed and print to screen
              HepRandom::setTheSeed(newSeed);
              HepRandom::showEngineStatus();
    
           // Create new filename
              filename = header;
              std::sprintf(name, "_%03i.%06li%s", int(HepRandom::getTheSeed()), newSeed, ".root");
              filename.append(name);
    
           // Set TString rootName to new filename
              rootName = filename;
              G4cout << "RootAnalysis - New filename is: " << filename << G4endl << G4endl;
     }
  
  // Create ROOT histgrams
     hfile = new TFile(filename, "RECREATE");

  // Store initial beam energy
  // initialBeamEnergy = generator->GetMeanEnergy();

  // Detector Histograms


     BraggPeak1D = new TH1D("BraggPeak1D", "Lateral depth dose profile (Bragg Peak)",400, 0, 400);
     PDDX1D = new TH1D("PDDX1D", "Depth dose profile along X axis",400, 0, 400);
     PDDY1D = new TH1D("PDDY1D", "Depth dose profile along Y axis",400, 0, 400);

     tarDose1D   = new TH1D("tarDose1D","1D depth dose profile in target;z-pos (cm)",nzBins, zMin/cm, zMax/cm);
     tarDose2DXZ = new TH2D("tarDose2DXZ", "2D depth dose profile in target (XZ projection);z-pos (cm);x-pos (cm)", 
                             nzBins, zMin/cm, zMax/cm, nxBins, xMin/cm, xMax/cm);
     tarDose2DXY = new TH2D("tarDose2DXY", "2D depth dose profile in target (XY projection);y-pos (cm);x-pos (cm)", 
                             nxBins, xMin/cm, xMax/cm, nxBins, xMin/cm, xMax/cm);
     tarDose3D   = new TH3D("tarDose3D", "3D depth dose profile in target;z-pos (cm);y-pos (cm);x-pos (cm)", 
                           nzBins, zMin/cm, zMax/cm, nxBins, xMin/cm, xMax/cm, nxBins, xMin/cm,  xMax/cm); 

  // store sum of squares of weights

     tarDose1D->Sumw2();
     tarDose2DXY->Sumw2();
     tarDose2DXZ->Sumw2();
     tarDose3D->Sumw2();

}


// ***************************************************************************************************
void RootAnalysis::PhantomGeometricalCharacteristics( G4int phantomSizeX, G4int phantomSizeY, G4int phantomSizeZ)
{  
  // Set depth dose limits to fill target (centered at isocenter) with bin size set by targetStepMax
     G4double TargetStepMax = 3.0*mm;
     nxBins = int(phantomSizeX/TargetStepMax)+1;
     xMin = -phantomSizeX/2 - TargetStepMax/2;
     xMax =  phantomSizeX/2 + TargetStepMax/2;
     nzBins = int(phantomSizeZ/TargetStepMax)+1;
     zMin = -phantomSizeZ/2 - TargetStepMax/2;
     zMax =  phantomSizeZ/2 + TargetStepMax/2;
}


// ***************************************************************************************************
void RootAnalysis::TragetDoseDistribution(G4double energyDeposit, G4ThreeVector position)
//----------------------------------------------------------------------------------------------------
{
  
  if(fabs(position.x())<1*cm && fabs(position.y())<1*cm) {
tarDose1D->Fill(position.z()/cm, energyDeposit/MeV);
	}
  tarDose2DXY->Fill(position.y()/cm, position.x()/cm, energyDeposit/MeV);
  tarDose2DXZ->Fill(position.z()/cm, position.x()/cm, energyDeposit/MeV);
  tarDose3D->Fill(position.z()/cm, position.y()/cm, position.x()/cm, energyDeposit/MeV);
}


// ***************************************************************************************************
void RootAnalysis::DetMatrix(G4int i, G4int j, G4int k, G4double energyDeposit)
//----------------------------------------------------------------------------------------------------
{ 
  PDDX1D->Fill(i, energyDeposit);
  PDDY1D->Fill(j, energyDeposit);
}

// ***************************************************************************************************
void RootAnalysis::BraggPeak(G4int k, G4double energyDeposit)
//----------------------------------------------------------------------------------------------------
{ 
  BraggPeak1D->Fill(k, energyDeposit);
}



// ***************************************************************************************************
void RootAnalysis::saveFiles()         // Write histograms                // Saving ROOT Files
//----------------------------------------------------------------------------------------------------

{

     tarDose1D->Write();
     tarDose2DXY->Write();
     tarDose2DXZ->Write();
     tarDose3D->Write();

     BraggPeak1D->Write();
     PDDX1D->Write();
     PDDY1D->Write();

     G4cout << "                                                                                 "<< G4endl;
     G4cout << "      DATA SAVED TO DISK AS " << filename << G4endl << G4endl;
     G4cout << "                                                                                 "<< G4endl;
     G4cout << "                                                                                 "<< G4endl;

     hfile->Close();

    

}

// ***************************************************************************************************
RootAnalysis* RootAnalysis::getInstance()
//----------------------------------------------------------------------------------------------------
{
  if (instance == 0) instance = new RootAnalysis;
  return instance;
}

// ***************************************************************************************************

