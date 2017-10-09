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
// Matrix.hh;
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy
//
// **************************************************************************************

#include "Matrix.hh"
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "RootAnalysis.hh"

#include <fstream>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "globals.hh"

// Units definition: CLHEP/Units/SystemOfUnits.h

Matrix* Matrix::instance = NULL;
G4bool Matrix::secondary = false;

// Only return a pointer to matrix
// *******************************************************************************************************************
Matrix* Matrix::GetInstance() 
//--------------------------------------------------------------------------------------------------------------------
{
  return instance;
}

// *******************************************************************************************************************
Matrix* Matrix::GetInstance(G4int voxelX, G4int voxelY, G4int voxelZ, G4double mass)  
//--------------------------------------------------------------------------------------------------------------------
{
  if (instance) delete instance;
  instance = new Matrix(voxelX, voxelY, voxelZ, mass);
  instance -> Initialize();
  return instance;
}

// *******************************************************************************************************************
Matrix::Matrix(G4int voxelX, G4int voxelY, G4int voxelZ, G4double mass): stdFile("Dose.out")
//--------------------------------------------------------------------------------------------------------------------
{  
  // Number of the voxels of the phantom. For X = Y = 1 the phantom is divided in slices (and not in voxels)
  // orthogonal to the beam axis
     numberOfVoxelAlongX = voxelX;
     numberOfVoxelAlongY = voxelY;
     numberOfVoxelAlongZ = voxelZ; 
     massOfVoxel = mass;

  // Create the dose matrix
     matrix = new G4double[numberOfVoxelAlongX*numberOfVoxelAlongY*numberOfVoxelAlongZ];

  // Create the depth dose vector
     depthDose = new G4double[numberOfVoxelAlongZ];
	
     if (matrix && depthDose)
     {
        G4cout << "Memory space to store physical dose into " << numberOfVoxelAlongX*numberOfVoxelAlongY*numberOfVoxelAlongZ 
               << "voxels has been allocated " << G4endl;
     }
     else G4Exception("Matrix::Matrix","ProtonTherapy", FatalException, 
		      "Can't allocate memory to store physical dose!");
	
  // Initialisation to 0 of the 'depthDose' vector
      for(int i=0;i<numberOfVoxelAlongZ;i++) depthDose[i] = 0.; 
	
  // Hit voxel (TrackID) marker
  // This array mark the status of voxel, if a hit occur, with the trackID of the particle Must be initialized
     hitTrack = new G4int[numberOfVoxelAlongX*numberOfVoxelAlongY*numberOfVoxelAlongZ];
     ClearHitTrack();
}

// *******************************************************************************************************************
Matrix::~Matrix()
//--------------------------------------------------------------------------------------------------------------------
{
    delete[] matrix;
    delete[] hitTrack;
    delete[] depthDose; 
    Clear();
}

// clear fluences/dose data
// *******************************************************************************************************************
void Matrix::Clear()                                  
//--------------------------------------------------------------------------------------------------------------------
{
  for (size_t i=0; i<ionStore.size(); i++)
    {
      delete[] ionStore[i].dose; 
      delete[] ionStore[i].fluence; 
    }
      ionStore.clear();
}

// Clear data and initialize the elements of the dose matrix to zero
// *******************************************************************************************************************
void Matrix::Initialize()         
//--------------------------------------------------------------------------------------------------------------------
{ 
    Clear();
    for(int i=0;i<numberOfVoxelAlongX*numberOfVoxelAlongY*numberOfVoxelAlongZ;i++) {matrix[i] = 0;}
}

// Print generated nuclides list
// *******************************************************************************************************************
void Matrix::PrintNuclides()     
//--------------------------------------------------------------------------------------------------------------------
{
  for (size_t i=0; i<ionStore.size(); i++) {G4cout << ionStore[i].name << G4endl;}
}

// Clear Hit voxel (TrackID) markers
// *******************************************************************************************************************
void Matrix::ClearHitTrack()     
//--------------------------------------------------------------------------------------------------------------------
{
  for(G4int i=0; i<numberOfVoxelAlongX*numberOfVoxelAlongY*numberOfVoxelAlongZ; i++) hitTrack[i] = 0;
}

 // Return Hit status
// *******************************************************************************************************************
G4int* Matrix::GetHitTrack(G4int i, G4int j, G4int k) 
//--------------------------------------------------------------------------------------------------------------------
{
  return &(hitTrack[Index(i,j,k)]);
}

// Dose methods...
// Fill DOSE/fluence matrix for particle/ion: 
// If fluence parameter is true (default value is FALSE) then fluence at voxel (i, j, k) is increased. 
// The energyDeposit parameter fill the dose matrix for voxel (i,j,k) 
// *******************************************************************************************************************
G4bool Matrix::Fill(G4int trackID, G4ParticleDefinition* particleDef, G4int i, G4int j,G4int k, G4double energyDeposit, G4bool fluence) 
//--------------------------------------------------------------------------------------------------------------------
{
  // Calculation of dose deposited in Gray units
     if ( (energyDeposit <= 0.0 && !fluence) || !secondary) return false;

  // Get Particle Data Group id
     G4int PDGencoding = particleDef -> GetPDGEncoding();
     PDGencoding -= PDGencoding%10;
	
  // Search for already allocated data...
     for (size_t l=0; l < ionStore.size(); l++) {
       if (ionStore[l].PDGencoding == PDGencoding ) { 
	 // Is it a primary or a secondary particle? 
	    if ( (trackID == 1 && ionStore[l].isPrimary) || (trackID != 1 && !ionStore[l].isPrimary) ) {
	      if (energyDeposit > 0.) ionStore[l].dose[Index(i, j, k)] += energyDeposit;
	   
	   // Fill a matrix per each ion with the fluence
	      if (fluence) ionStore[l].fluence[Index(i, j, k)]++;
	   
	      return true;
	    }
       }
     }

  // Check if new operator fails	
     G4int Z = particleDef-> GetAtomicNumber();
     G4int A = particleDef-> GetAtomicMass();
	
  // FullName is deuterium for H2 ground state, H2[x.y] for higher energy states
     G4String fullName = particleDef -> GetParticleName();
     G4String name = fullName.substr (0, fullName.find("[") ); // cut excitation energy  

  // Let's put a new particle in the store...
     ion newIon = 
     {
       (trackID == 1) ? true:false,
       PDGencoding,
       name,
       name.length(), 
       Z, 
       A, 
       new G4double[numberOfVoxelAlongX * numberOfVoxelAlongY * numberOfVoxelAlongZ],
       new unsigned int[numberOfVoxelAlongX * numberOfVoxelAlongY * numberOfVoxelAlongZ]
      }; 

  // Initialize data
     if (newIon.dose && newIon.fluence)
     {
       for(G4int m=0; m<numberOfVoxelAlongX*numberOfVoxelAlongY*numberOfVoxelAlongZ; m++)
	  {
	    newIon.dose[m] = 0.;
	    newIon.fluence[m] = 0;
	  }
      if (energyDeposit > 0.){newIon.dose[Index(i, j, k)] += energyDeposit; }
      if (fluence) newIon.fluence[Index(i, j, k)]++;
      ionStore.push_back(newIon);
		
      // for verbosity check
      
/*	G4cout << "Memory space to store the DOSE/FLUENCE into " <<  
	numberOfVoxelAlongX*numberOfVoxelAlongY*numberOfVoxelAlongZ << 
	" voxels has been allocated for the nuclide " << newIon.name << 
	" (Z = " << Z << ", A = " << A << ")" << G4endl ;*/
      
      return true;
    }
  else //  Can't allocate memory! 
    {
      return false;
    }
	
}

// Store the energy deposit in the matrix element corresponding to the Detector voxel at the end of event (see EventAction.cc)
// *******************************************************************************************************************
void Matrix::Fill(G4int i, G4int j, G4int k, G4double energyDeposit)
//--------------------------------------------------------------------------------------------------------------------
{	
  if (matrix) {	matrix[Index(i,j,k)] += energyDeposit; }  
}

// Methods to store data to filenames...
// General method to store matrix data to filename
// *******************************************************************************************************************
void Matrix::StoreMatrix(G4String file, void* data, size_t psize)
//--------------------------------------------------------------------------------------------------------------------
{
  if (data)
    {
      ofs.open(file, std::ios::out);
      if (ofs.is_open())
	{
	   for(G4int i = 0; i < numberOfVoxelAlongX; i++) 
	   for(G4int j = 0; j < numberOfVoxelAlongY; j++) 
	   for(G4int k = 0; k < numberOfVoxelAlongZ; k++) 
	   {
		  G4int n = Index(i, j, k);
		  // Check for data type: G4int, G4double, 
		  if (psize == sizeof(unsigned int))
		    {
		      unsigned int* pdata = (unsigned int*)data;
		      if (pdata[n]) ofs << i << '\t' << j << '\t' <<k << '\t' << pdata[n] << G4endl;
		    }
		  else if (psize == sizeof(G4double))
		    {
		      G4double* pdata = (G4double*)data;
		      if (pdata[n]) ofs << i << '\t' << j << '\t' <<k << '\t' << pdata[n] << G4endl;
		    }
           }
	  ofs.close();
	}
    }
}

// Store fluence per single ion in multiple files
// *******************************************************************************************************************
void Matrix::StoreFluenceData()
//--------------------------------------------------------------------------------------------------------------------
{
    for (size_t i=0; i < ionStore.size(); i++)
    {StoreMatrix(ionStore[i].name + "_Fluence.out", ionStore[i].fluence, sizeof(unsigned int));}
}

// Store dose per single ion in multiple files
// *******************************************************************************************************************
void Matrix::StoreDoseData()
//--------------------------------------------------------------------------------------------------------------------
{	
  for (size_t i=0; i < ionStore.size(); i++)
  {StoreMatrix(ionStore[i].name + "_Dose.out", ionStore[i].dose, sizeof(G4double));}
}

// Store dose for all ions into a single file.
// Please note that this function is called via messenger commands defined in the RootMessenger.cc class file
// *******************************************************************************************************************
void Matrix::StoreDoseFluenceAscii(G4String file)
//--------------------------------------------------------------------------------------------------------------------
{
#define width 15L

     stdFile= "Dose.out";
     filename = (file=="") ? stdFile:file;

  // Sort like periodic table
     std::sort(ionStore.begin(), ionStore.end());
     G4cout << "Dose is being written to " << filename << G4endl;
     ofs.open(filename, std::ios::out);

     if (ofs.is_open())
     {
      // Write the voxels index and the list of particles/ions 
        ofs << std::setprecision(6) << std::left <<"i\tj\tk\t"; 
        
      // Total dose 
        ofs << std::setw(width) << "Dose(Gy)"<< '\t';
		
      if (secondary)
	{
	  for (size_t l=0; l < ionStore.size(); l++)
	    {
	      G4String a = (ionStore[l].isPrimary) ? "_P":""; // is it a primary?
	      ofs << '\t' << ionStore[l].name + a <<'\t' << ionStore[l].name  + a;
	    }
	  ofs << G4endl;		       	 
	}

      // Write data
         for(G4int i = 0; i < numberOfVoxelAlongX; i++) 
	 for(G4int j = 0; j < numberOfVoxelAlongY; j++) 
	 for(G4int k = 0; k < numberOfVoxelAlongZ; k++) 
	 {
	      G4int n = Index(i, j, k);

	      // Write only not identically null data lines. Total dose (the elements of matrix[n] are already in Gray) 
	      if (matrix[n])
	      {	 
		  ofs << G4endl;
		  ofs << i << '\t' << j << '\t' << k << '\t';
		  // ofs << std::setw(width) << (matrix[n]/massOfVoxel)/(joule/kg);
		  ofs << matrix[n]<< '\t';

		  if (secondary)
		    {
		      for (size_t l=0; l < ionStore.size(); l++)
			{
			  ofs << '\t' << ionStore[l].dose[n] << '\t' << ionStore[l].fluence[n]; 
			//  ofs << std::setw(width) << (ionStore[l].dose[n]/massOfVoxel)/(joule/kg) <<std::setw(width) << ionStore[l].fluence[n]; 	  
			}
		    }
	      }
	}
      ofs.close();
    }

}

// *******************************************************************************************************************
void Matrix::StoreDoseFluence()
//--------------------------------------------------------------------------------------------------------------------
{
   for(G4int i = 0; i < numberOfVoxelAlongX; i++) 
   for(G4int j = 0; j < numberOfVoxelAlongY; j++) 
   for(G4int k = 0; k < numberOfVoxelAlongZ; k++) 
   {
     //G4int n = Index(i, j, k);
       for (size_t l=0; l < ionStore.size(); l++)				
       {
        //  analysis -> Fill( i, j, k, ionStore[l].A, ionStore[l].Z,  ionStore[l].dose[n],   ionStore[l].fluence[n] );
       }
   }
}

// *******************************************************************************************************************
void Matrix::EnergyDeposit()
//--------------------------------------------------------------------------------------------------------------------
{
     RootAnalysis* analysis = RootAnalysis::getInstance();

  if (matrix)
  {  
        for(G4int k = 0; k < numberOfVoxelAlongZ; k++)
        for(G4int i = 0; i < numberOfVoxelAlongX; i++) 
        for(G4int j = 0; j < numberOfVoxelAlongY; j++) 
        
        {
	    G4int n = Index(i,j,k);
	    depthDose[k] += matrix[n];
    	      
	    if (numberOfVoxelAlongX > 1 ||numberOfVoxelAlongY > 1 ||numberOfVoxelAlongZ > 1)
	    analysis -> DetMatrix(i,j,k, matrix[n]);

	    if (numberOfVoxelAlongZ > 1) analysis -> BraggPeak(k, matrix[n]);
	 }
  }   

}

// *******************************************************************************************************************
void Matrix::TotalEnergyDeposit()
//--------------------------------------------------------------------------------------------------------------------
{
  if (matrix)
  {  
      for(G4int i = 0; i < numberOfVoxelAlongX; i++) 
      for(G4int j = 0; j < numberOfVoxelAlongY; j++) 
      for(G4int k = 0; k < numberOfVoxelAlongZ; k++)
      {
	  G4int n = Index(i,j,k);
	  if (matrix[n] > 0) {

          }
      }		
  }

}

// *******************************************************************************************************************
