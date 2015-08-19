#pragma once 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class KUNPLEx3DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    KUNPLEx3DetectorConstruction();
    virtual ~KUNPLEx3DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};
