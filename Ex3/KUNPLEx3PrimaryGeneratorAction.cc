#include "KUNPLEx3PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

KUNPLEx3PrimaryGeneratorAction::KUNPLEx3PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable -> FindParticle(particleName = "e-");

  fParticleGun -> SetParticleDefinition(particle);
  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.));
  fParticleGun -> SetParticleEnergy(25. * keV);
}

KUNPLEx3PrimaryGeneratorAction::~KUNPLEx3PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void KUNPLEx3PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event

  fParticleGun -> GeneratePrimaryVertex(anEvent);
}
