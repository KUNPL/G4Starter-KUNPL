#include "KUNPLEx1ROOTTrackingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

KUNPLEx1ROOTTrackingAction::KUNPLEx1ROOTTrackingAction()
: G4UserTrackingAction()
{
  fAna = KUNPLEx1ROOTAna::GetInstance();
}

KUNPLEx1ROOTTrackingAction::~KUNPLEx1ROOTTrackingAction()
{
}

void KUNPLEx1ROOTTrackingAction::PreUserTrackingAction(const G4Track* track)
{
  fAna -> SetTrackID(track -> GetTrackID());
}

void KUNPLEx1ROOTTrackingAction::PostUserTrackingAction(const G4Track* track)
{
}
