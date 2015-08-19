#pragma once

#include "G4VUserPhysicsList.hh"
#include "QGSP_BERT.hh"
#include "globals.hh"

class KUNPLEx3PhysicsList : public QGSP_BERT
{
  public:
    KUNPLEx3PhysicsList();    
    virtual ~KUNPLEx3PhysicsList();

    // method from the base class
    virtual void SetCuts();
};
