#include "KUNPLEx1DetectorConstruction.hh"
#include "KUNPLEx1PrimaryGeneratorAction.hh"

#include "QBBC.hh"

#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

int main(int argc,char** argv)
{
  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4Random::setTheSeed(time(0));
  
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization and action classes
  runManager -> SetUserInitialization(new QBBC); // Physics list
  runManager -> SetUserInitialization(new KUNPLEx1DetectorConstruction());
  runManager -> SetUserAction(new KUNPLEx1PrimaryGeneratorAction());
    
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
    UImanager -> ApplyCommand("/control/execute macros/init_vis.mac"); 
    UImanager -> ApplyCommand("/control/execute macros/init.mac"); 
    ui -> SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;

  return 0;
}
