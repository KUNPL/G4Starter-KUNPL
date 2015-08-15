#include "KUNPLEx1SteppingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

KUNPLEx1SteppingAction::KUNPLEx1SteppingAction()
: G4UserSteppingAction()
{
}

KUNPLEx1SteppingAction::~KUNPLEx1SteppingAction()
{
}

void KUNPLEx1SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4int parentID = step -> GetTrack() -> GetParentID();
  G4int pdg      = step -> GetTrack() -> GetDefinition() -> GetPDGEncoding();

  /**
   * GetDeltatEnergy()
   *   : The energy lost by a particle (to the medium and to secondaries) during
   *     a step.
   *
   * GetTotalEnergyDeposit()
   *   : The energy lost to the medium. 
   *     This is sum of
   *       1) the energy deposited by the energy loss process, and
   *       2) the energy lost by secondaries which have NOT been generated
   *          because each of their energies was below the cut threshold.
   *
   * GetNonIonizingEnergyDeposit()
   *   : The energy lost to the medium but not available for ionization.
   *
   * GetTotalEnergyDeposit() - GetNonIonizingEnergyDeposit()
   *   : The energy available for ionization.
   */

  G4double deltaE          = step -> GetDeltaEnergy(); 
  G4double totalEdep       = step -> GetTotalEnergyDeposit(); 
  G4double nonIonizingEdep = step -> GetNonIonizingEnergyDeposit(); 

  G4cout << G4endl << pdg << "(" << parentID << "): "
         << deltaE << ", " << totalEdep << ", " << nonIonizingEdep << G4endl; 



  G4StepStatus stat = step -> GetPostStepPoint() -> GetStepStatus();
  if (stat != fWorldBoundary) 
  {
    G4String preVolName  = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName();
    G4double preTime     = step -> GetPreStepPoint() -> GetGlobalTime();
    G4ThreeVector prePos = step -> GetPreStepPoint() -> GetPosition();
    G4double preX        = prePos.x();
    G4double preY        = prePos.y();
    G4double preZ        = prePos.z();

    G4cout << "  " << preVolName << ": "
           << preX << ", " << preY << ", " << preZ << ", " << preTime << G4endl;



    G4String pstVolName  = step -> GetPostStepPoint() -> GetPhysicalVolume() -> GetName();
    G4ThreeVector pstPos = step -> GetPostStepPoint() -> GetPosition();
    G4double pstTime     = step -> GetPostStepPoint() -> GetGlobalTime();
    G4double pstX        = pstPos.x();
    G4double pstY        = pstPos.y();
    G4double pstZ        = pstPos.z();

    G4cout << "  " << pstVolName << ": "
           << pstX << ", " << pstY << ", " << pstZ << ", " << pstTime << G4endl;
  }
}
