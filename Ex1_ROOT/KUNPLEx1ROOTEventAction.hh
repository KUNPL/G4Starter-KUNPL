#pragma once

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"

#include "KUNPLEx1ROOTAna.hh"

class KUNPLEx1ROOTEventAction : public G4UserEventAction
{
  public:
    KUNPLEx1ROOTEventAction();
    virtual ~KUNPLEx1ROOTEventAction();

    // method from the base class
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

  private:
    KUNPLEx1ROOTAna* ana;
};
