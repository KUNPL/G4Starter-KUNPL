#include "KUNPLEx1TrackingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

KUNPLEx1TrackingAction::KUNPLEx1TrackingAction()
: G4UserTrackingAction()
{
}

KUNPLEx1TrackingAction::~KUNPLEx1TrackingAction()
{
}

void KUNPLEx1TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  G4cout << G4endl
         << ">>> PreTracking " 
         << track -> GetTrackID() << " "
         << track -> GetParentID() << G4endl;
}

void KUNPLEx1TrackingAction::PostUserTrackingAction(const G4Track* track)
{
  G4cout << G4endl 
         << "<<< PostTracking " 
         << track -> GetTrackID() << " "
         << track -> GetParentID() << " "
         << track -> GetParentID() << G4endl;
}
