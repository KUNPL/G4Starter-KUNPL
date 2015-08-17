#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(G4KUNPL)

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
# Set G4KUNPL source directories and executables
#
set(KUNPLEx_SOURCE_DIRECTORIES
  Ex1
  Ex2
  )

set(KUNPLEx_EXECUTABLES
  KUNPLEx1
  KUNPLEx1_Action
  KUNPLEx2
  )


if(useROOT)
  list(APPEND KUNPLEx_SOURCE_DIRECTORIES
    Ex1/ROOT
    )
  list(APPEND KUNPLEx_EXECUTABLES
    KUNPLEx1_ROOT
    )
endif(useROOT)


#----------------------------------------------------------------------------
# Set variables
#
set(KUNPLEx_SOURCES_DIRECTORIES_FULL)
foreach(_directory ${KUNPLEx_SOURCE_DIRECTORIES})
  list(APPEND KUNPLEx_SOURCE_DIRECTORIES_FULL ${PROJECT_SOURCE_DIR}/${_directory})
endforeach(_directory)

set(KUNPLEx_SOURCES)
foreach(_directory ${KUNPLEx_SOURCE_DIRECTORIES_FULL})
  list(APPEND KUNPLEx_SOURCES ${_directory}/*.cc)
endforeach(_directory)

set(KUNPLEx_HEADERS)
foreach(_directory ${KUNPLEx_SOURCE_DIRECTORIES_FULL})
  list(APPEND KUNPLEx_HEADERS ${_directory}/*.hh)
endforeach(_directory)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${KUNPLEx_SOURCE_DIRECTORIES_FULL})

if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
endif(useROOT)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${KUNPLEx_SOURCES})
file(GLOB headers ${KUNPLEx_HEADERS})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
foreach(_executable ${KUNPLEx_EXECUTABLES})
  add_executable(${_executable} ${_executable}.cc ${sources} ${headers})
if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
endif(useROOT)
  target_link_libraries(${_executable} ${Geant4_LIBRARIES})
endforeach(_executable)


#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build G4KUNPL. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(KUNPLEx_SCRIPTS
  macros/init.mac
  macros/init_vis.mac
  macros/vis.mac
  macros/run1.mac
  #macros/run2.mac

  macros/init2.mac
  macros/init_vis2.mac
  macros/vis2.mac
  )

foreach(_script ${KUNPLEx_SCRIPTS})
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
add_custom_target(G4KUNPL DEPENDS ${KUNPLEx_EXECUTABLES})


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
foreach(_executable ${KUNPLEx_EXECUTABLES})
  install(TARGETS ${_executable} DESTINATION bin)
endforeach(_executable)
