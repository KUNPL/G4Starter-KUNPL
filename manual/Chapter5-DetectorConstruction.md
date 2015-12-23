#검출기 만들기

검출기를 만드는 클래스는 KooDetectorConstruction이다. 앞장에서 말했듯이 user class 에는 반드시 정의 해야 하는 함수들이 있는데 DetectorConstruction의 경우는 G4VPhysicalVolume* Construct()이다. 이 예제에서는 공기로 되어 있는 World와 C10H11로 되어 있는 Detector를 만들 것이다. 코드를 보자.

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

  G4Material *detector_mat = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid, labTemp);
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

먼저 물질의 재료가 될 G4Material을 먼저 정의해야 한다. 다행히도 Geant4에는 기본 물질들의 정의를 해주는 Nist 데이터베이스가 있는데 공기의 경우도 이를 통해서 공정의 할 수 있다. 각 물질에대한 이름은 Geant4 메뉴얼에서 찾을 수 있다.

```c++
  G4NistManager* nist = G4NistManager::Instance();
```
```c++
  G4Material* world_mat = nist -> FindOrBuildMaterial("G4_AIR");
```

하지만 검출기의 재료가 될 C10H11은 Nist 데이터 베이스에 존재하지 않는다. 이런 경우에는 다음과 같이 일일이 재료를 정의해야 한다. 먼저 탄소와 수소 원소를 G4Element로 정의 한다. 각 변수는 이름, 기호, Z-number, molecular mass다.

```c++
  G4Element *element_C  = new G4Element("Carbon",   "C",  6,  12.011*g/mole);
  G4Element *element_H  = new G4Element("Hydrogen", "H",  1,  1.00794*g/mole);
```

그 다음은 재료, G4Material을 정의 한다. 각 변수는 이름, 단위부피당 질량, 원소의 개수, 상태, 온도다. 추가로 위에서 정의한 원소들을 AddElement로 추가한다. 이때 옆에 들어가는 숫자는 원소의 개수가 된다.

```c++
  G4Material *detector_mat = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid, labTemp);
  detector_mat -> AddElement(element_C, 10);
  detector_mat -> AddElement(element_H, 11);
```

이제 재료를 준비했으니 물질을 정의할 차례다. 물질을 정의할때는 다음 세가지 요소가 필요하다.
- 물질의 모양과 크기를 결정하는 **Solid Volume**
- 물질의 특성을 결정하는 **Logical Volume**
- 물질을 위치시키는 **Physical Volume**

하나씩 살펴보자.

```c++
 G4Box* solidDetector =    
    new G4Box("Detector",          // its name
              0.5*detector_size,   // half x
              0.5*detector_size,   // half y
              0.5*detector_size);  // half z
```

먼저 Solid volume은 말 그대로 모양과 크기를 결정한다. Geant4에서 제공하는 기본 모양들은 아주 많고, 또 이들끼리 조합하여 더하거나 빼는것도 가능하다. Geant4 매뉴얼에 아주 잘 설명되어 있다. 가장 기본인 박스모양은 G4Box를 이용한다. 

```c++
  G4LogicalVolume* logicDetector =                         
    new G4LogicalVolume(solidDetector,  //its solid
                        detector_mat,   //its material
                        "Detector");    //its name
```

Logical volume은 그 특성을 결정하는데 위 코드는 solid volume과 재료만 추가하여 정의 하였지만 나중에 필요하면 Field 또는 SDManager 또한 추가할 수 있다.

```c++
    new G4PVPlacement(0,                                     //no rotation
                      G4ThreeVector(0,0,detector_offset_z),  //at (0,0,0)
                      logicDetector,                         //its logical volume
                      "Detector",                            //its name
                      logicWorld,                            //its mother  volume
                      false,                                 //no boolean operation
                      0,                                     //copy number
                      true);                                 //overlaps checking
```

마지막으로 Physical volume은 logical volume을 위치시키는 일을 한다. 하나의 logical volume을 가지고 여러개를 만드는 것도 가능하다(이 경우 copy number를 다르게 해준다). 또 상위 물질(Mother volume)을 입력하여 물질의 상하관계를 알려주어야 한다. World의 경우는 상위 물질이 없지만 Detector의 경우 상위 물질은 World가 된다.

Construct가 반환해야 할 volume은 가장 상위 물질인 World의 Physical volume이다. World의 Physical volume은 모든 정보를 가지고 있기 때문에 다른 검출기의 Physical volume은 new로 만들기만 하고 변수로 받지않아도 메모리에 남게 된다.
