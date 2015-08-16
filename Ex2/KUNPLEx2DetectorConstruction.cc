#include "KUNPLEx2DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

KUNPLEx2DetectorConstruction::KUNPLEx2DetectorConstruction()
: G4VUserDetectorConstruction()
{
}

KUNPLEx2DetectorConstruction::~KUNPLEx2DetectorConstruction()
{
}

G4VPhysicalVolume* KUNPLEx2DetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();


  // -----------------------------------------------------
  // World

  G4Material* vacuum =
    new G4Material("vacuum", 1,
                   1.008 * g/mole, 1.e-25 * g/cm3, kStateGas,
                   2.73 * kelvin, 3.e-18 * pascal);

  G4double world_size = 1000 * mm;

  G4Box* solidWorld =    
    new G4Box("World",                       // its name
              0.5*world_size,                // half x
              0.5*world_size,                // half y
              0.5*world_size);               // half z
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        vacuum,              //its material
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
  // Tracker

  G4double denAr  = 1.782e-3 * g/cm3;
  G4double denCO2 = 1.808e-3 * g/cm3;
  G4double denC10 = 0.9 * denAr + 0.1 * denCO2;
  G4double temperature = (273.15 + 20) * kelvin;

  G4Element* elC = new G4Element("Carbon", "C", 6, 12.0110 * g/mole);
  G4Element* elO = new G4Element("Oxygen", "O", 8, 15.9994 * g/mole);

  G4Material* ArGas = new G4Material("ArGas", 18, 39.948 *g/mole, denAr, kStateGas, temperature);
  G4Material* CO2Gas = new G4Material("CO2Gas", denCO2, 2, kStateGas, temperature);
  CO2Gas -> AddElement(elC, 1);
  CO2Gas -> AddElement(elO, 2);

  G4double mAr    = 0.9 * denAr / denC10;
  G4double mCO2   = 0.1 * denCO2 / denC10;
  G4double mTot   = mAr + mCO2;
  G4double mfAr   = mAr / mTot;
  G4double mfCO2  = mCO2 / mTot;

  G4Material* C10 = new G4Material("C10", denC10, 2, kStateGas, temperature);
  C10 -> AddMaterial(ArGas,  mfAr);
  C10 -> AddMaterial(CO2Gas, mfCO2);

  G4double tRmin   = 250 * mm;
  G4double tRmax   = 500 * mm;
  G4double tSPhi   = 0   * deg;
  G4double tDPhi   = 360 * deg;
  G4double tSTheta = 15  * deg;
  G4double tDTheta = 75  * deg;

  G4VSolid* solidTracker =
    new G4Sphere("Tracker", tRmin, tRmax, tSPhi, tDPhi, tSTheta, tDTheta);

  G4LogicalVolume* logicTracker =                         
    new G4LogicalVolume(solidTracker,
                        C10,
                        "Tracker");
                                   
    new G4PVPlacement(0,
                      G4ThreeVector(0,0,0),
                      logicTracker,
                      "Tracker",
                      logicWorld,
                      false,
                      0,
                      true);


  return physWorld;
}
