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

#ifndef RootAnalysis_h
#define RootAnalysis_h 1

#include "globals.hh"
#include "TCanvas.h"
#include "TGraph.h"
#include "G4ios.hh"
#include <vector>
#include "G4ThreeVector.hh"

class G4Track;
class G4Step;
class TFile;
class TH1D;
class TH2D;
class TH3D;
class TGraph;
class TTree;
class RootMessenger;


using namespace std;

// ********************************************************************
class RootAnalysis 

{
  public:

    RootAnalysis();
   ~RootAnalysis();

    void openFiles(const G4String header, const G4long seed);
    void PhantomGeometricalCharacteristics( G4int phantomSizeX, G4int phantomSizeY, G4int phantomSizeZ);
    void saveFiles();
    static RootAnalysis* getInstance();
    void  SetFileRewriting(G4String name)                              {FileRewriting = name;};
    void  SetHistogramVerbosity(G4int number)                          {Verbosity = number;};

    void TragetDoseDistribution(G4double energyDeposit,G4ThreeVector position);
    void BraggPeak(G4int k, G4double energyDeposit);
    void DetMatrix(G4int i, G4int j, G4int k, G4double energyDeposit);
    
  private:

 // Store instance
    static RootAnalysis* instance;
    RootMessenger* rootMessenger;
    G4String FileRewriting;
    G4int Verbosity;

 // Root file
    TFile *hfile;

 // Modulator
    TH2D  *Modulator2D;


 // Target histograms



    TH1D  *tarDose1D;
    TH2D  *tarDose2DXZ;
    TH2D  *tarDose2DXY;
    TH3D  *tarDose3D;
    TH1D  *BraggPeak1D;
    TH1D  *PDDX1D;
    TH1D  *PDDY1D;

    G4String filename;
    G4int verbosity;


     G4int    nxBins;
     G4double xMin;
     G4double xMax;
     G4int    nzBins;
     G4double zMin;
     G4double zMax;

     G4int verbose;


};

// ********************************************************************
#endif
