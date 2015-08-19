#pragma once

#include "G4VUserPhysicsList.hh"
#include "QGSP_BERT.hh"
#include "globals.hh"

class KUNPLEx2PhysicsList : public QGSP_BERT
{
  public:
    KUNPLEx2PhysicsList();    
    virtual ~KUNPLEx2PhysicsList();

    // method from the base class
    virtual void SetCuts();
};
