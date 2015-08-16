#pragma once 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class KUNPLEx2DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    KUNPLEx2DetectorConstruction();
    virtual ~KUNPLEx2DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};
