#include "KUNPLEx2DetectorConstruction.hh"
#include "KUNPLEx2PrimaryGeneratorAction.hh"
#include "KUNPLEx2PhysicsList.hh"
#include "QGSP_BERT.hh"

#include "G4StepLimiterPhysics.hh"

#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

int main(int argc, char** argv)
{
  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4Random::setTheSeed(time(0));
  
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Set physics list with step limiter
  //G4VModularPhysicsList* physicsList = new KUNPLEx2PhysicsList();
  G4VModularPhysicsList* physicsList = new QGSP_BERT;
  physicsList -> RegisterPhysics(new G4StepLimiterPhysics());

  // Set mandatory initialization and action classes
  runManager -> SetUserInitialization(new KUNPLEx2DetectorConstruction());
  runManager -> SetUserInitialization(physicsList); // Physics list
  runManager -> SetUserAction(new KUNPLEx2PrimaryGeneratorAction());
    
  // Initialize G4 kernel
  runManager -> Initialize();
  
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc != 1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager -> ApplyCommand(command+fileName);
  }
  else {
    // interactive mode : define UI session
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager -> ApplyCommand("/control/execute macros/init_vis2.mac"); 
    UImanager -> ApplyCommand("/control/execute macros/init2.mac"); 
    ui -> SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;

  return 0;
}
