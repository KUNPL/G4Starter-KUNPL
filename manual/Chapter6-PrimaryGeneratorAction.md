# 6 장. 입자 쏘기

입자를 쏘는 클래스는 KooPrimaryGeneratorAction이다.

###KooPrimaryGeneratorAction.hh
```c++
#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "globals.hh"

class KooPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    KooPrimaryGeneratorAction();    
    virtual ~KooPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
};
```

###KooPrimaryGeneratorAction.cc
```c++
#include "KooPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

KooPrimaryGeneratorAction::KooPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable -> FindParticle(particleName = "proton");

  fParticleGun -> SetParticleDefinition(particle);
  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun -> SetParticleEnergy(200.*MeV);
}

KooPrimaryGeneratorAction::~KooPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void KooPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event

  fParticleGun -> GeneratePrimaryVertex(anEvent);
}
```

이 클래스는 처음 이벤트가 시작할때 어떤 입자를 쏘아줄지 결정한다. 쏘아줄 입자는 G4ParticleGun을 이용해서 만든다. 

```c++
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable -> FindParticle(particleName = "proton");

  fParticleGun -> SetParticleDefinition(particle);
  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun -> SetParticleEnergy(200.*MeV);
```

처음에 생성자에 몇개의 파티클을 쏘아줄 것인지를 정

우리가 채워야 하는 함수는 void GeneratePrimaries(G4Event *) 이다. 이 함수는 각 이벤트가 시작할때 실행된다. 
유저는 미리 만들어둔 G4ParticleGun의 GeneratePrimaryVertex(G4Event*) 함수를 실행시켜주면 된다. 다음 줄과 같다.

```
  fParticleGun -> GeneratePrimaryVertex(anEvent);
```

매 이벤트 마다 쏘아주는 입자들이 달라진다면 이 함수안에서 입자총을
