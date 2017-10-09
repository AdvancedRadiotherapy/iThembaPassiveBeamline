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
// Based On:  Previous developed code: pgc006v494
//            Geant4 example: 
//
// Order:     [Executable] macro filename seed
//
// ********************************************************************

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "EventAction.hh"
#include "PhysicsList.hh"
#include "DetectorSD.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "Randomize.hh"  
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4UImessenger.hh"
#include "globals.hh"
#include <time.h>
#include <sys/time.h>
#include "SteppingAction.hh"
#include "GeometryController.hh"
#include "GeometryMessenger.hh"
#include "DetectorMessenger.hh"
#include "G4ScoringManager.hh"
#include "Matrix.hh"
#include "RootAnalysis.hh"


namespace CLHEP {}
  using namespace CLHEP;

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4ANALYSIS_USE_ROOT
#include "TApplication.h"
#endif

// *********************************************************************************************************
int main(int argc ,char ** argv)
// --------------------------------------------------------------------------------------------------------- 
{
    // Create speed & emittance units (not included by default)
       new G4UnitDefinition ( "meter/second", "m/s", "Speed", m/s );
       new G4UnitDefinition ( "millimeter*milliradian", "mm*mrad", "Emittance", mm*mrad );
       G4UnitDefinition::BuildUnitsTable();

    // Setting seed value
       G4long seed;
       if (argc==4) {
           seed = atol(argv[3]);
           G4cout << G4endl << "+++ Random Seed: " << seed << " / Set via command line" << G4endl;}
       else {   // OR seed = time(0);
           timeval time;
           gettimeofday(&time, NULL);
           seed = time.tv_usec;
           G4cout << G4endl << "+++ Random Seed: " << seed << " / Set via cpu clock using micro-seconds" << G4endl;}

   // Starting random number generator seed & printing to screen
       HepRandom::setTheEngine(new RanecuEngine);
       HepRandom::setTheSeed(seed);  // maximum of 215 seed indices
       HepRandom::showEngineStatus();

    // Setting up output file header
       G4String header;
       if (argc > 2) { header = argv[2]; }
       else if (argc == 2) {
    // Strip .mac from macro file (not very robust method)
       header = argv[1];
       size_t pos = header.find(".mac");
       header.erase(pos, 4);
       } else { header = "vis"; }
	
     G4RunManager* runManager = new G4RunManager;

  // geometries. All geometry specific setup tasks are now in class GeometryController.cc
     GeometryController *geometryController = new GeometryController();

  // Connect the geometry controller to the G4 user interface
     GeometryMessenger *geometryMessenger = new GeometryMessenger(geometryController);
		
  // Initialize the default Hadrontherapy geometry
     geometryController->SetGeometry("default");
	
  // Initialize command based scoring
     G4ScoringManager::GetScoringManager();
	
  // Initialize the physics 
  //runManager -> SetUserInitialization(new HadrontherapyPhysicsList());
	
     G4PhysListFactory factory;
     G4VModularPhysicsList* phys = 0;
     G4String physName = "";
	
  // Physics List name defined via environment variable
     char* path = getenv("PHYSLIST");
     if (path) { physName = G4String(path); }
	
     if(factory.IsReferencePhysList(physName)) 
     {phys = factory.GetReferencePhysList(physName);} 
	
     if(!phys) { phys = new PhysicsList();}
	
     runManager->SetUserInitialization(phys);
	
  // Initialize the primary particles
     PrimaryGeneratorAction *pPrimaryGenerator = new PrimaryGeneratorAction();
     runManager -> SetUserAction(pPrimaryGenerator);
	
  // Optional UserActions: run, event, stepping
     RunAction* runAction = new RunAction(header, seed);
     runManager -> SetUserAction(runAction);	
     EventAction* eventAction = new EventAction();
     runManager -> SetUserAction(eventAction);	
     SteppingAction* steppingAction = new SteppingAction(runAction); 
     runManager -> SetUserAction(steppingAction);  
	
#ifdef G4VIS_USE
  // Visualization, if you choose to have it!
     G4VisManager* visManager = new G4VisExecutive;
     visManager->Initialize();
#endif 
	
  // get the pointer to the User Interface manager 
     G4UImanager* UImanager = G4UImanager::GetUIpointer();
     if (argc!=1){   // batch mode
     
#ifdef G4UI_USE
      G4UIExecutive* UI = new G4UIExecutive(argc, argv);

#ifdef G4VIS_USE
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);   
#endif
      if (UI->IsGUI())
	UI->SessionStart();
      delete UI;
#endif
    }

  else {  

  // interactive mode : define UI session		
#ifdef G4UI_USE
      G4UIExecutive* UI = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
      if(factory.IsReferencePhysList(physName)) 
	{ UImanager->ApplyCommand("/control/execute Proton.mac");}
      else
	{UImanager->ApplyCommand("/control/execute macro/vis.mac");}
		
#endif
      if (UI->IsGUI())
        UImanager->ApplyCommand("/control/execute/Co60.mac"); 
	UI->SessionStart();
      delete UI;
#endif 
    }
	
  // Store dose & fluence data to ASCII & ROOT files 
  if ( Matrix * pMatrix = Matrix::GetInstance() )
    {
      pMatrix -> TotalEnergyDeposit(); 
      pMatrix -> StoreDoseFluenceAscii();
      pMatrix -> EnergyDeposit();
    }

     if (RootAnalysis* analysis = RootAnalysis::getInstance())
     analysis->saveFiles();

#ifdef G4VIS_USE
  delete visManager;
#endif

  delete geometryMessenger;
  delete geometryController;
  delete runManager;
	
  return 0;
}
