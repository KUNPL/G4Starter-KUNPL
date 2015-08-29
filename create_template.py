#!/usr/bin/env python
import os
import sys



if len(sys.argv) == 1 :
  project = raw_input('project name: ')
else :
  project = sys.argv[1]

command = 'mkdir ' + project
os.system(command)
command = 'mkdir ' + project + '/src'
os.system(command)
command = 'mkdir ' + project + '/build'
os.system(command)



#-------------------------------------------------------
template_name = 'CMakeLists.txt'
copy_name = project + '/' + template_name
copy_file = open(copy_name, 'w')

content = '''#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PROJECT_DUMMY)

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
# Set PROJECT_DUMMY source directories and executables
#
set(DUMMY_SOURCE_DIRECTORIES
  src
  )

set(DUMMY_EXECUTABLES
  DUMMY
  )


if(useROOT)
  list(APPEND DUMMY_SOURCE_DIRECTORIES
    )
  list(APPEND DUMMY_EXECUTABLES
    )
endif(useROOT)


#----------------------------------------------------------------------------
# Set variables
#
set(DUMMY_SOURCES_DIRECTORIES_FULL)
foreach(_directory ${DUMMY_SOURCE_DIRECTORIES})
  list(APPEND DUMMY_SOURCE_DIRECTORIES_FULL ${PROJECT_SOURCE_DIR}/${_directory})
endforeach(_directory)

set(DUMMY_SOURCES)
foreach(_directory ${DUMMY_SOURCE_DIRECTORIES_FULL})
  list(APPEND DUMMY_SOURCES ${_directory}/*.cc)
endforeach(_directory)

set(DUMMY_HEADERS)
foreach(_directory ${DUMMY_SOURCE_DIRECTORIES_FULL})
  list(APPEND DUMMY_HEADERS ${_directory}/*.hh)
endforeach(_directory)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${DUMMY_SOURCE_DIRECTORIES_FULL})

if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
endif(useROOT)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${DUMMY_SOURCES})
file(GLOB headers ${DUMMY_HEADERS})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
foreach(_executable ${DUMMY_EXECUTABLES})
  add_executable(${_executable} ${_executable}.cc ${sources} ${headers})
if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
endif(useROOT)
  target_link_libraries(${_executable} ${Geant4_LIBRARIES})
endforeach(_executable)


#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build PROJECT_DUMMY. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(DUMMY_SCRIPTS
  vis.mac
  )

foreach(_script ${DUMMY_SCRIPTS})
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
add_custom_target(PROJECT_DUMMY DEPENDS ${DUMMY_EXECUTABLES})


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
foreach(_executable ${DUMMY_EXECUTABLES})
  install(TARGETS ${_executable} DESTINATION bin)
endforeach(_executable)
'''
content = content.replace('DUMMY',project)
copy_file.write(content)
copy_file.close()



#-------------------------------------------------------
copy_name = project + '/' + project + '.cc'
copy_file = open(copy_name, 'w')

content = '''#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

#include "QGSP_BERT.hh"
// Add user defined classes here
#include "DUMMYDetectorConstruction.hh"
#include "DUMMYPrimaryGeneratorAction.hh"

int main(int argc,char** argv)
{
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4Random::setTheSeed(time(0));
  
  G4RunManager* runManager = new G4RunManager;

  // Add user initialization and action here
  G4VModularPhysicsList* physicsList = new QGSP_BERT;
  runManager -> SetUserInitialization(physicsList); // Physics list
  runManager -> SetUserInitialization(new DUMMYDetectorConstruction());
  runManager -> SetUserAction(new DUMMYPrimaryGeneratorAction());
    
  runManager -> Initialize();
  
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc != 1) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager -> ApplyCommand(command+fileName);
  }
  else {
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    // Add user macros here to load automatically - ex) vis.mac
    UImanager -> ApplyCommand("/control/execute vis.mac"); 
    ui -> SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;

  return 0;
}
'''
content = content.replace('DUMMY',project)
copy_file.write(content)
copy_file.close()





#-------------------------------------------------------
copy_name = project + '/vis.mac'
copy_file = open(copy_name, 'w')
content = '''/control/verbose 2
/control/saveHistory
/tracking/verbose 2
/run/verbose 2

/vis/open OGL 600x600-0+0
/vis/viewer/set/autoRefresh false
/vis/verbose errors
/vis/drawVolume

/vis/viewer/set/viewpointVector -1 0 0
/vis/viewer/set/lightsVector -1 0 0
/vis/viewer/set/style wireframe
/vis/viewer/set/auxiliaryEdge true
/vis/viewer/set/lineSegmentsPerCircle 100

/vis/scene/add/trajectories smooth
/vis/modeling/trajectories/create/drawByCharge
/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true
/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 2

/vis/scene/endOfEventAction accumulate

/vis/scene/add/scale   100 mm
/vis/scene/add/axes    0 0 0 100 mm 
/vis/scene/add/eventID
/vis/scene/add/frame
/vis/set/colour
/vis/set/lineWidth

/vis/geometry/set/visibility World 0 false
/vis/geometry/set/colour Detector 1 0.8 0.8 1 0.3

/vis/viewer/set/style surface
/vis/viewer/set/hiddenMarker true
/vis/viewer/set/viewpointThetaPhi 100 160
/vis/viewer/set/autoRefresh true

/vis/verbose warnings
'''

copy_file.write(content)
copy_file.close()



#-------------------------------------------------------
template_name = 'Ex1/KUNPLEx1DetectorConstruction.cc'
template_file = open(template_name, 'r')
copy_name = project + '/src/' + project + 'DetectorConstruction.cc'
copy_file = open(copy_name, 'w')
while 1 :
  line = template_file.readline()
  if not line : 
    break # break if oef
  if line.find('KUNPLEx1') is not -1 :
    line = line.replace('KUNPLEx1', project)
  copy_file.write(line)
copy_file.close()



#-------------------------------------------------------
template_name = 'Ex1/KUNPLEx1DetectorConstruction.hh'
template_file = open(template_name, 'r')
copy_name = project + '/src/' + project + 'DetectorConstruction.hh'
copy_file = open(copy_name, 'w')
while 1 :
  line = template_file.readline()
  if not line : 
    break # break if oef
  if line.find('KUNPLEx1') is not -1 :
    line = line.replace('KUNPLEx1', project)
  copy_file.write(line)
copy_file.close()



#-------------------------------------------------------
template_name = 'Ex1/KUNPLEx1PrimaryGeneratorAction.cc'
template_file = open(template_name, 'r')
copy_name = project + '/src/' + project + 'PrimaryGeneratorAction.cc'
copy_file = open(copy_name, 'w')
while 1 :
  line = template_file.readline()
  if not line : 
    break # break if oef
  if line.find('KUNPLEx1') is not -1 :
    line = line.replace('KUNPLEx1', project)
  copy_file.write(line)
copy_file.close()



#-------------------------------------------------------
template_name = 'Ex1/KUNPLEx1PrimaryGeneratorAction.hh'
template_file = open(template_name, 'r')
copy_name = project + '/src/' + project + 'PrimaryGeneratorAction.hh'
copy_file = open(copy_name, 'w')
while 1 :
  line = template_file.readline()
  if not line : 
    break # break if oef
  if line.find('KUNPLEx1') is not -1 :
    line = line.replace('KUNPLEx1', project)
  copy_file.write(line)
copy_file.close()
