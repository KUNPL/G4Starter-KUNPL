#include "KUNPLEx3DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4TwistedBox.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Region.hh"
#include "G4RotationMatrix.hh"
#include "G4UniformElectricField.hh"
#include "G4FieldManager.hh"
#include "G4ClassicalRK4.hh"
#include "G4EqMagElectricField.hh"
#include "G4TransportationManager.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

KUNPLEx3DetectorConstruction::KUNPLEx3DetectorConstruction()
: G4VUserDetectorConstruction()
{
}

KUNPLEx3DetectorConstruction::~KUNPLEx3DetectorConstruction()
{
}

G4VPhysicalVolume* KUNPLEx3DetectorConstruction::Construct()
{  
  // -----------------------------------------------------
  // World

  G4Material* vacuum =
    new G4Material("vacuum", 1,
                   1.008 * g/mole, 1.e-25 * g/cm3, kStateGas,
                   2.73 * kelvin, 3.e-18 * pascal);

  G4double world_size = 5000 * mm;

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

  G4double tRMin = 0   * mm;
  G4double tRMax = 200 * mm;
  G4double tRDz  = 500 * mm;

  G4VSolid* solidTracker =
    new G4Tubs("Tracker", tRMin, tRMax, tRDz, 0, 180);

  G4double tStepMax = 1 * m;

  G4LogicalVolume* logicTracker =                         
    new G4LogicalVolume(solidTracker,
                        C10,
                        "Tracker",
                        0,
                        0,
                        new G4UserLimits(tStepMax));

  G4Region* regionTracker = new G4Region("Tracker");
  logicTracker -> SetRegion(regionTracker);
  regionTracker -> AddRootLogicalVolume(logicTracker);

  /*
  G4UniformElectricField* tField =
    new G4UniformElectricField(G4ThreeVector(0,0,350 * volt));

  G4FieldManager* fieldMan = new G4FieldManager();
  fieldMan -> SetDetectorField(tField);
  fieldMan -> SetChordFinder(tField);
  */

  G4UniformElectricField *EMField = 
    //new G4UniformElectricField(G4ThreeVector(0., 0., 350*volt/cm));
    new G4UniformElectricField(G4ThreeVector(0., 180 * volt / cm, 0.));

  G4EqMagElectricField* equation = 
    new G4EqMagElectricField(EMField);

  G4ClassicalRK4 *stepper = 
    new G4ClassicalRK4(equation, 8);

  G4FieldManager* fieldMgr = 
    G4TransportationManager::GetTransportationManager() -> GetFieldManager();

  fieldMgr -> SetDetectorField(EMField);

  G4double minStep = 1 * m;
  G4MagInt_Driver* driver = 
    new G4MagInt_Driver(minStep, stepper, stepper -> GetNumberOfVariables());

  G4ChordFinder *chordFinder = new G4ChordFinder(driver); 
  fieldMgr -> SetChordFinder(chordFinder);

  G4RotationMatrix* rotTracker = new G4RotationMatrix();
  rotTracker -> rotateX(90 * deg);

  logicTracker -> SetFieldManager(fieldMgr, 0);
                                   
    new G4PVPlacement(rotTracker,
                      G4ThreeVector(0, 0, 0),
                      logicTracker,
                      "Tracker",
                      logicWorld,
                      false,
                      0,
                      true);


  return physWorld;
}
