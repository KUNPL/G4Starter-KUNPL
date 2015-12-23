# Geant4 Starter for KUNPL

- [Geant4 무작정 따라하기 - 3 판](https://github.com/KUNPL/G4Starter-KUNPL/blob/master/manual/Chapter0-Contents.md)

- For English version click [HERE](https://github.com/KUNPL/G4Starter-KUNPL/blob/master/README_ENG.md).

- G4Starter-KUNPL 프로젝트는 Geant4 를 이제 막 시작하려는 고려대학교 
  핵물리연구실 학생들을 위한 Geant4 예제이자 템플릿입니다.

- 여기에 있는 예제들는 Geant4.10.02 과 ROOT5.34.21에서 테스트 되었으며
  이보다 낮은 버젼을 사용할 경우 컴파일이 및 이벤트 디스플레이가 
  정상적으로 작동하지 않을 수 있습니다.

- CMakeList.txt 에는 ROOT 를 사용할 수 있도록 짜여져있는데 이 때문에 문제가
  일어난다고 생각한다면 변수 'useROOT' 를 'true' 에서 'false' 로 바꾸면 
  ROOT 의존성을 끌 수 있습니다.

- G4Starter-KUNPL 에 있는 예제들을 제외한 나만의 템플릿을 만들고 싶은 경우
  'create_template.py' 메크로를 사용하면 됩니다. 터미널에서
  './create_template.py [프로젝트]' 와 같이 실행하면 [프로젝트] 라는 폴더가
  만들어지며 폴더를 원하는 곳으로 옮겨 G4Starter-KUNPL 과 같은 방법으로 사용
  할 수 있습니다.


---

###1. 컴파일

- G4Starter-KUNPL 경로로 들어간다:
  ```sh
  > cd [Path-to-G4Starter-KUNPL]
  ```

- build 폴더를 만들고 들어간다:
  ```sh
  > mkdir build  
  > cd build  
  ```

- Geant4 와 ROOT 환경을 설정한다. 핵물리연구실 서버의 경우 다음과 같다:
  ```sh
  > geant41000p02
  > root5
  ```

- cmake!
  ```sh
  > cmake ..  
  > make   
  ```


###2. 실행

컴파일을 마친 후 실행파일 들이 build 폴더 안에 생성되었을 것이다.
이제 두가지 방법으로 실행을 할 수 있는데 1) 실행파일을 실행 후 직접
명령어들을 치는 방법과 2) 전에 써놨던 매크로를 이용해서 실행하는
방법이 있다.

#####1) 첫번째 방법
- 직접 명령어를 치는 방법:
  ```sh
  > ./KUNPLEx1
  
  Geant4 kernal 을 실행중...
  
  Idle> /run/beamOn 10  
  Idle> ...  
  Idle> exit  
  ```
  
#####2) 두번째 방법
- 실행을 한 후에 매크로 파일을 불러오는 방법:
  ```sh
  > ./KUNPLEx1
  
  Geant4 kernal 을 실행중...
  
  Idle> /control/execute macros/run1.mac  
  ....  
  Idle> exit  
  ```

- 매크로 파일을 실행파일과 함께 실행하는 방법:
  ```sh
  > ./KUNPLEx1 macros/run1.mac  
  ```

- 아웃픗을 원하는 경우: 
  ```sh
  > ./KUNPLEx1 macros/KUNPLEx1.in > KUNPLEx1.out  
  ```

###3. 클래스를 추가하는 방법

CMakeList.txt 를 열어서 클래스 이름들을 
'set(KUNPLEx_SOURCE_DIRECTORIES' 아래에 추가한다: 

```cmake
set(KUNPLEx_SOURCE_DIRECTORIES  
  Ex1  
  Ex1_Action  
  [directory-1]  
  [directory-2]  
  ...  
  )  
```

###4. 실행파일을 추가하는 방법

CMakeList.txt 를 열어서 확장자를 제외한 실행파일 이름을
'set(KUNPLEx_EXECUTABLE' 아래에 추가한다: 

```cmake
set(KUNPLEx_EXECUTABLES
  KUNPLEx1
  KUNPLEx1_Step
  [executable-1]
  [executable-2]
  ...
  )
```


###5. 매크로 파일을 추가하는 방법

CMakeList.txt 를 열어서 확장자를 제외한 실행파일 이름을
'set(KUNPLEx_SCRIPTS' 아래에 추가한다. 이 예제들의 경우
폴더가 더러워지는 것을 방지하여 macro 폴더를 생성한 후
모든 매크로 파일을 넣어두었다:

```cmake
set(KUNPLEx_SCRIPTS
  macros/init.mac
  macros/init_vis.mac
  macros/vis.mac
  macros/run1.mac
  macros/run2.mac
  macros/[macro-1]
  macros/[macro-2]
  ...
  )
```
