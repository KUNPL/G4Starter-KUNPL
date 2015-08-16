#pragma once

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"

#include "KUNPLEx1ROOTAna.hh"

class KUNPLEx1ROOTSteppingAction : public G4UserSteppingAction
{
  public:
    KUNPLEx1ROOTSteppingAction();
    virtual ~KUNPLEx1ROOTSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    KUNPLEx1ROOTAna* fAna;
};
