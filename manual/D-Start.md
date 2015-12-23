#시작하기

이 매뉴얼은 Geant4.10.00.02와 ROOT5.34.21 버전을 사용한다는 점을 다시한번 확인하자.

우리가 지금 부터 만들 프로젝트의 파일 구조는 다음과 같다. 프로젝트명은 임시로 Koo 이라고 하자.

- Koo/
  - CMakeList.txt
  - Koo.cc
  - src/
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

CMakeList.txt는 내가 만든 파일들을 하나로 합쳐서 실행파일을 만들어주는 역할을 한다. 미리 말해두지만 CMakeList는 Geant4와 아무 상관이 없고 작성하는 방법은 매우 어렵다. 본인도 Geant4의 예제 중에 있는 CMakeList.txt 파일을 이 예제에 맞게 고쳤을 뿐이다. 따라서 CMakeList는 이해하려고 하기 보다 그냥 가져다 쓰도록 하자.
