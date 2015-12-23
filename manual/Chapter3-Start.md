# 3 장. 시작하기

이 매뉴얼은 Geant4.10.00.02와 ROOT5.34.21 버전을 사용한다는 점을 다시한번 확인하자.

우리가 지금 부터 만들 프로젝트의 파일 구조는 다음과 같다. 프로젝트명은 임시로 "Koo"라고 하자.

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

src 폴더에는 우리가 앞으로 만들 대부분의 파일들이 들어간다. Koo.cc에서 이 파일들을 연결하고 CMakeList.txt를 이용해서 컴파일 하여 실행파일을 만든다. 미리 말해두지만 CMakeList는 Geant4와 아무 상관이 없으며 작성하는 방법이 매우 어렵다. 본인도 Geant4의 예제 중에 있는 CMakeList.txt 파일을 이 예제에 맞게 고쳤을 뿐이다. 따라서 CMakeList는 이해하려고 하기 보다 그냥 가져다 쓰도록 하자.

이러한 파일 구조는 보통의 Geant4 예제와는 조금 다르다. Geant4 예제들은 폴더가 src와 include로 나뉘어져있다. src에는 소스파일 (.cc로 끝나는 파일)이 들어가고 inlcude에는 헤더파일 (.hh 로 끝나는 파일)이 들어간다. 큰 프로젝트가 아닌 이상 이런 구조는 파일을 열람할 때 불편하기 때문에 위와같이 모두 src 폴더에 몰아넣는 구조를 선택하였다. 만약에 다른 구조를 사용하려면 CMakeList.txt를 수정해야 한다.

CMakeList.txt의 내용은 다음과 같다. 이 파일에 한해서 복사 붙여넣기를 하도록 하자.
_이 매뉴얼에서는 ROOT를 사용하지 않지만 아래 CMakeList.txt는 ROOT 라이브러리도 같이 사용할 수 있도록 쓰여져 있다._

###CMakeList.txt

```cmake
#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PROJECT_Koo)

set(useROOT true)


#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


#----------------------------------------------------------------------------
# Set PROJECT_Koo source directories and executables
#
set(Koo_SOURCE_DIRECTORIES
  src
  )

set(Koo_EXECUTABLES
  Koo
  )


if(useROOT)
  list(APPEND Koo_SOURCE_DIRECTORIES
    )
  list(APPEND Koo_EXECUTABLES
    )
endif(useROOT)


#----------------------------------------------------------------------------
# Set variables
#
set(Koo_SOURCES_DIRECTORIES_FULL)
foreach(_directory ${Koo_SOURCE_DIRECTORIES})
  list(APPEND Koo_SOURCE_DIRECTORIES_FULL ${PROJECT_SOURCE_DIR}/${_directory})
endforeach(_directory)

set(Koo_SOURCES)
foreach(_directory ${Koo_SOURCE_DIRECTORIES_FULL})
  list(APPEND Koo_SOURCES ${_directory}/*.cc)
endforeach(_directory)

set(Koo_HEADERS)
foreach(_directory ${Koo_SOURCE_DIRECTORIES_FULL})
  list(APPEND Koo_HEADERS ${_directory}/*.hh)
endforeach(_directory)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${Koo_SOURCE_DIRECTORIES_FULL})

if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPAC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
endif(useROOT)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${Koo_SOURCES})
file(GLOB headers ${Koo_HEADERS})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
foreach(_executable ${Koo_EXECUTABLES})
  add_executable(${_executable} ${_executable}.cc ${sources} ${headers})
if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
endif(useROOT)
  target_link_libraries(${_executable} ${Geant4_LIBRARIES})
endforeach(_executable)


#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build PROJECT_Koo. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(Koo_SCRIPTS
  vis.mac
  )

foreach(_script ${Koo_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach(_script)


#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(PROJECT_Koo DEPENDS ${Koo_EXECUTABLES})


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
foreach(_executable ${Koo_EXECUTABLES})
  install(TARGETS ${_executable} DESTINATION bin)
endforeach(_executable)
```
