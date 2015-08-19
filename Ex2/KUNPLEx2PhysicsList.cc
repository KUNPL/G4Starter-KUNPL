#include "KUNPLEx2PhysicsList.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

KUNPLEx2PhysicsList::KUNPLEx2PhysicsList()
{
}

KUNPLEx2PhysicsList::~KUNPLEx2PhysicsList()
{
}

void KUNPLEx2PhysicsList::SetCuts()
{
  G4Region* trackerRegion = G4RegionStore::GetInstance() -> GetRegion("Tracker");
  G4ProductionCuts* trackerCuts = new G4ProductionCuts;

  trackerCuts -> SetProductionCut(1 * km, "e-");
  trackerRegion -> SetProductionCuts(trackerCuts);
}
