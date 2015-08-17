#include "KUNPLEx1ROOTSteppingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

KUNPLEx1ROOTSteppingAction::KUNPLEx1ROOTSteppingAction()
: G4UserSteppingAction()
{
  fAna = KUNPLEx1ROOTAna::GetInstance();
}

KUNPLEx1ROOTSteppingAction::~KUNPLEx1ROOTSteppingAction()
{
}

void KUNPLEx1ROOTSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4StepStatus stat = step -> GetPostStepPoint() -> GetStepStatus();
  if (stat != fWorldBoundary) 
  {
    G4int parentID = step -> GetTrack() -> GetParentID();
    G4int pdg      = step -> GetTrack() -> GetDefinition() -> GetPDGEncoding();

    G4double totalEdep       = step -> GetTotalEnergyDeposit(); 
    G4double nonIonizingEdep = step -> GetNonIonizingEnergyDeposit(); 

    G4String preVolName  = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName();
    G4double preTime     = step -> GetPreStepPoint() -> GetGlobalTime();
    G4ThreeVector prePos = step -> GetPreStepPoint() -> GetPosition();
    G4double preX        = prePos.x();
    G4double preY        = prePos.y();
    G4double preZ        = prePos.z();

    G4String pstVolName  = step -> GetPostStepPoint() -> GetPhysicalVolume() -> GetName();
    G4ThreeVector pstPos = step -> GetPostStepPoint() -> GetPosition();
    G4double pstTime     = step -> GetPostStepPoint() -> GetGlobalTime();
    G4double pstX        = pstPos.x();
    G4double pstY        = pstPos.y();
    G4double pstZ        = pstPos.z();

    G4int preVolumeIdx = 0;
    if      (preVolName == "World")    preVolumeIdx = 0;
    else if (preVolName == "Detector") preVolumeIdx = 1;
    else                               preVolumeIdx = -1;

    G4int pstVolumeIdx = 0;
    if      (pstVolName == "World")    pstVolumeIdx = 0;
    else if (pstVolName == "Detector") pstVolumeIdx = 1;
    else                               pstVolumeIdx = -1;
    
    fAna -> Fill(
      parentID,
      pdg,
      totalEdep,
      nonIonizingEdep, 
      preVolumeIdx,
      preX,
      preY,
      preZ,
      preTime, 
      pstVolumeIdx,
      pstX,
      pstY,
      pstZ,
      pstTime);
  }
}
