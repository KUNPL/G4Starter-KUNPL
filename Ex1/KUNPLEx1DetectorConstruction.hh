#pragma once 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class KUNPLEx1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    KUNPLEx1DetectorConstruction();
    virtual ~KUNPLEx1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};
