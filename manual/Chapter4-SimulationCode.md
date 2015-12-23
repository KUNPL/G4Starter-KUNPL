# 4 장. 어떤 파일을 만들어야 할까

Geant4는 시뮬레이션에 필요한 클래스의 틀을 미리 만들어 놓았다. 사용자는 이런 클래스를 상속하는 새로운 클래스를 만들어서 필요한 함수에 내용을 채운 후 Geant4에 연결해주기만 하면 된다. 이 둘은 물질과 처음 쏘아주는 입자를 정의하므로 당연히 필수 요소이다. 기본적으로 유저가 다룰 수 있는 클래스는 두가지 종류로 user initialization 클래스와 user action 클래스가 있다.
- User initialization classes
  - [x] **G4VUserDetectorConstruction**
  - [ ] **G4VUserPhysicsList**
  - [ ] **G4VUserActionInitialization**
- User Action classes
  - [x] **G4VUserPrimaryGeneratorAction**
  - [ ] G4UserRunAction  
  - [x] G4UserEvenAction  
  - [x] G4UserSteppingAction
  - [x] G4UserTrackingAction
  - [ ] G4UserStackingAction
  
위 목록에서 진한색으로 되어 있는 클래스는 Geant4 시뮬레이션을 하기 위해서 반드시 정의 해야 하는 시뮬레이션이고 체크 박스에 체크되어있는 클래스들은 우리가 직접 만들어볼 클래스들이다. 

Initialization 클래스는 시뮬레이션을 본격적으로 시작하기 전에 초기화하는 작업을 담당한다. 기본적으로 세 클래스모두 만들어야 하지만 Physics List는 Geant4 기본 클래스가 있고 ActionInitialization은 클래스로 만들지 않아도 동일한 작업을 간단하게 수행할 수 있다.

Action 클래스는 시뮬레이션의 각 단계마다 불려가서 각 함수에 있는 내용을 실행한다. 예를 들어서 SteppingAction의 경우 어떤 이벤트나 입자든 상관없이 한번의 스텝이 끝날때 마다 실행되는 UserSteppingAction(const G4Step* step)이라는 함수가 있다. RunAction, EventAction 그리고 TrackingAction은 각각 런, 이벤트 트랙의 각 시작과 끝에 실행되는 함수가 있다. StackingAction은 지금은 이해하기 어려우므로 넘어가도록 하자. 이러한 Action 기능들은 시뮬레이션에서 우리가 원하는 정보를 꺼내올 때 유용하게 쓰인다.

### [다음](https://github.com/KUNPL/G4Starter-KUNPL/blob/master/manual/Chapter5-DetectorConstruction.md)
