#include "KUNPLEx1ROOTTrackingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "G4ThreeVector.hh"

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

  G4ThreeVector v = track -> GetMomentum();

  Double_t x = v.x();
  Double_t y = v.y();
  Double_t z = v.z();

  fAna -> Fill(track -> GetParentID(),
               track -> GetDefinition() -> GetPDGEncoding(),
               x, y, z);
}

void KUNPLEx1ROOTTrackingAction::PostUserTrackingAction(const G4Track* track)
{
}
