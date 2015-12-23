# 1 장. 들어가며

###3 판 
> 이정우 (phyjics@gmail.com), December 23, 2015  
> https://github.com/KUNPL/G4Starter-KUNPL

Geant4는 버전이 올라감에 따라 호환이 되지 않는 경우가 많다. 따라서 버전이 달라서 잘못되는 경우가 없도록 주의하자.

GEANT4.10.00.02 버전에 맞게 예제와 매뉴얼을 만들었다. 루트의 경우 ROOT5.34.21를 사용하였다. 

버전 외의 큰 차이점은 Physics List를 Geant4 기본 Physics List로 바꾼것, Digitization의 일부분이기도 한 G4PVReplica 제거한것,  그리고 RO(ReadOut)Geometry, SensitiveDetector와 Hit 클래스를 제거하고 직접 SteppingAction에서 정보를 가지고 온다는 점이 있다. ROGeometry와 SensitiveDetector는 복잡한 검출기 시스템을 시뮬레이션 할 때 유용하지만 간단한 시뮬레이션에서는 직접 Action 클래스에서 정보를 가지고 오는것이 더 편리하다. 무엇보다 처음부터 배우기 어렵다. 이에 대해서 알고싶다면 먼저 Geant4의 기본을 알고 자신감이 생긴 후 2 판을 보면서 공부하는 것을 추천한다.

Geant4 [Documetation](http://geant4.cern.ch/support/userdocuments.shtml)은 매우 훌륭하다. 영어를 잘 한다면 Geant4 [Documetation](http://geant4.cern.ch/support/userdocuments.shtml)의 [User's Guide: For Application Developers](http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/index.html)를 읽으면서 공부하는 것을 추천한다. 지금 작성하는 매뉴얼은 Geant4를 한번도 사용해 보지 않았지만 영어가 서툴어서 공식 매뉴얼을 보고 시작하기 어려운 사람들을 위한 설명서이다.

###2 판 
> 장진희 (geniejhang@majimak.com), July 2, 2014, Based on the advice of Kisoo Lee  
> https://github.com/KUNPL/GEANT4_example

아직 아는것이 많지 않기에, 아는것이 생긴다면 시간이 되는대로 업데이트 하겠다. 일단은 지금 까지 시행착오도 많이 거치며 알아낸 것들을 정리하기 위해서 이 문서를 쓴다.나중에 어떻게 될지는 모르겠지만, 가능한 나보다 늦게 시뮬레이션을 시작하는 사람이 나보다 적은 시간을 들여 내가 알아낸 것들을 알 수 있도록 쓸 것이다.

GEANT는 Geometry ANd Tracking의 약자로, 뒤에있는 4는 당연히 4번째 버전임을 나타 낸다. GEANT4는 컴퓨터 안에서 가상의 실험실을 만들고, 그 안에 여러 검출기를 놓아두고 빔(입자 혹은 광자)을 이용해서 실험하는 것을 도와주는 Library Package이다. 우리가 해야할 것은 이 패키지에서 적절한 것을 꺼내와 적절하게 배치하고, 실행시켜주는것이다.

라이브러리 패키지가 뭔지 잘 다가오지 않는 나같은 사람이 있을지도 몰라 간단히 설명해보 도록 하겠다. 아무것도 없는 상태에서 시뮬레이션을 하려고 한다고 해보자. 먼저 기본 단위를 정해야 한다. 길이, 시간, 에너지, 전하량 등등. 계산을 좀 편하게 하기 위해서, 숫자 세개의 묶음 이 벡터라는것도 알려줘야 하고, 이 벡터들 사이에 연산 방법을 알려줘야 한다. 속도를 알려주면, 이 속도라는게 정해준 단위 시간당 얼마만큼의 거리를 프로그램내에서 진행한다는 것을 알려 줘야 한다. 검출기나 기타 물질들과 어떤 상호작용을 하는지 알려줘야 한다. 이처럼 여러가지 해야할 것들을 하나의 패키지로 묶어서 사용할 수 있게 해놓은것이 라이브러리 패키지이다.

참고: 이 문서는 GEANT4.9.4.p01버전과 CLHEP 2.1.0.1버전을 이용해서 만들어졌다. 나중 에 GEANT4가 업데이트 되면서 실행이 안되는 부분이 생길 수도 있다.

### [다음](https://github.com/KUNPL/G4Starter-KUNPL/blob/master/manual/Chapter2-Concept.md)
