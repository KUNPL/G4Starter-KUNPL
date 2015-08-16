#pragma once

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "globals.hh"

class KUNPLEx1TrackingAction : public G4UserTrackingAction
{
  public:
    KUNPLEx1TrackingAction();
    virtual ~KUNPLEx1TrackingAction();

    // method from the base class
    virtual void PreUserTrackingAction(const G4Track* track);
    virtual void PostUserTrackingAction(const G4Track* track);
};
