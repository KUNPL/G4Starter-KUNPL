#include "KUNPLEx3PhysicsList.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

KUNPLEx3PhysicsList::KUNPLEx3PhysicsList()
{
}

KUNPLEx3PhysicsList::~KUNPLEx3PhysicsList()
{
}

void KUNPLEx3PhysicsList::SetCuts()
{
  G4Region* trackerRegion = G4RegionStore::GetInstance() -> GetRegion("Tracker");
  G4ProductionCuts* trackerCuts = new G4ProductionCuts;

  trackerCuts -> SetProductionCut(1 * km, "e-");
  trackerRegion -> SetProductionCuts(trackerCuts);
}
