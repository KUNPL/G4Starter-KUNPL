#검출기 만들기

검출기를 만드는 클래스는 KooDetectorConstruction이다. 먼저 헤더파일을 보자.

### KooDetectorConstruction.hh
```c++
#pragma once 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class KooDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    KooDetectorConstruction();
    virtual ~KooDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};
```

DetectorConstruction은 Geant4 시뮬레이션에

### KooDetectorConstruction.cc
```c++
#include "KooDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

KooDetectorConstruction::KooDetectorConstruction()
: G4VUserDetectorConstruction()
{
}

KooDetectorConstruction::~KooDetectorConstruction()
{
}

G4VPhysicalVolume* KooDetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();


  // -----------------------------------------------------
  // World

  G4Material* world_mat = nist -> FindOrBuildMaterial("G4_AIR");
  G4double world_size = 100*mm;

  G4Box* solidWorld =    
    new G4Box("World",                       // its name
              0.5*world_size,                // half x
              0.5*world_size,                // half y
              0.5*world_size);               // half z
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      true);                 //overlaps checking


  // -----------------------------------------------------
  // Detector

  const G4double labTemp = STP_Temperature + 20.*kelvin;

  G4Element *element_C  = new G4Element("Carbon",   "C",  6,  12.011*g/mole);
  G4Element *element_H  = new G4Element("Hydrogen", "H",  1,  1.00794*g/mole);

  G4Material *detector_mat = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid, l
  detector_mat -> AddElement(element_C, 10);
  detector_mat -> AddElement(element_H, 11);

  G4double detector_size = 20*mm;
  G4double detector_offset_z = 30*mm;

  G4Box* solidDetector =    
    new G4Box("Detector",
              0.5*detector_size,
              0.5*detector_size,
              0.5*detector_size);
      
  G4LogicalVolume* logicDetector =                         
    new G4LogicalVolume(solidDetector,
                        detector_mat,
                        "Detector");
                                   
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,detector_offset_z),
                      logicDetector,
                      "Detector",
                      logicWorld,
                      false,
                      0,
                      true);

  return physWorld;
}

```
