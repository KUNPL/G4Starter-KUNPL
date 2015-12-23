#어떤 파일들을 만들어야 할까

Geant4는 시뮬레이션에 필요한 클래스의 틀을 미리 만들어 놓았다. 예를 들어서 아래와 같다.
- G4VUserDetectorConstruction
- G4VUserPrimaryGeneratorAction
- G4UserSteppingAction
- G4UserTrackingAction
- ...

사용자는 이런 클래스를 상속하는 새로운 클래스를 만들어서 연결해주기만 하면 된다.
이 중에서 첫번째와 두번째 클래스는



src 폴더안에 들어갈 파일들을 다시 살펴보자.

- KooDetectorConstruction.cc
- KooDetectorConstruction.hh
- KooEventAction.cc
- KooEventAction.hh
- KooPrimaryGeneratorAction.cc
- KooPrimaryGeneratorAction.hh
- KooSteppingAction.cc
- KooSteppingAction.hh
- KooTrackingAction.cc
- KooTrackingAction.hh

우리가 만들 클래스는 총 5개다.
