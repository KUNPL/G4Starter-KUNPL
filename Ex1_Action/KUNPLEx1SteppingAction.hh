#pragma once

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"

class KUNPLEx1SteppingAction : public G4UserSteppingAction
{
  public:
    KUNPLEx1SteppingAction();
    virtual ~KUNPLEx1SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);
};
