#pragma once

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "globals.hh"

#include "KUNPLEx1ROOTAna.hh"

class KUNPLEx1ROOTTrackingAction : public G4UserTrackingAction
{
  public:
    KUNPLEx1ROOTTrackingAction();
    virtual ~KUNPLEx1ROOTTrackingAction();

    // method from the base class
    virtual void PreUserTrackingAction(const G4Track* track);
    virtual void PostUserTrackingAction(const G4Track* track);

  private:
    KUNPLEx1ROOTAna* fAna;
};
