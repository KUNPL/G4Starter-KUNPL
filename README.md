# Geant4 Starter for KUNPL


These Geant4 examples are tutorial and template for Korea University 
Nuclear Physics Lab (KUNPL) Geant4 primary users. 

Examples were tested with version Geant4.10.02.

NOTE that CMakeFile.txt contains dependency of ROOT. If you think this 
causes problem, set variable 'useROOT' from 'true' to 'false' in 
CMakeList.txt.

- Author: JungWoo LEE, Korea Univ. (phyjics@gmail.com)

---

###1. How to compile

- Go into the KUNPLG4 directory (where this README.md is):  
  $ cd [Path-to-KUNPLG4]

- Make build directory, go into it and build with cmake:
  $ mkdir build  
  $ cd build  
  $ cmake ..  
  $ make   


###2. How to run

- Go into build directory and execute KUNPLEx1.  
  $ ./KUNPLEx1

- and type in the commands:  
  Idle> /run/beamOn 10  
  Idle> ...  
  Idle> exit  

- or  
  Idle> /control/execute run1.mac  
  ....  
  Idle> exit  

- Execute KUNPLEx1  in the 'batch' mode from macro files (without visualization)  
  $ ./KUNPLEx1 run2.mac  
  $ ./KUNPLEx1 KUNPLEx1.in > KUNPLEx1.out  


###3. How to add classes

To add your own classes, open CMakeList.txt and add directory name which
contains your classes under 'set(KUNPLEx_SOURCE_DIRECTORIES':  

    set(KUNPLEx_SOURCE_DIRECTORIES  
    Ex1  
    Ex1_Action  
    [Name of your directory]  
    ...  
    )  


###4. How to add executables

To add your own executables, open CMakeList.txt and add executable name
(without filename extension) under 'set(KUNPLEx_EXECUTABLE':

      set(KUNPLEx_EXECUTABLES
        KUNPLEx1
        KUNPLEx1_Action
        [Name of your executable]
        ...
        )


###5. How to add macros

To add your own macros(.in or .mac), 1)add them in macros directory,
2) open CMakeList.txt and add macro names under 'set(KUNPLEx_SCRIPTS':

      set(KUNPLEx_SCRIPTS
        scripts/init.mac
        scripts/init_vis.mac
        scripts/vis.mac
        scripts/run1.mac
        scripts/run2.mac
        [Name of your script]
        ...
        )
