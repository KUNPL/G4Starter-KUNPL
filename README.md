$ README 2015-08-15 $
-------------------------------------------------------------------

                           KUNPL EXAMPLE
                           -------------

 Template for Korea University Nuclear Physics Lab (KUNPL) Geant4 
 primary users. This example was teted with version Geant4.10.02.

 NOTE that CMakeFile.txt contains dependency of ROOT. If you think this 
 causes problem, then set variable 'useROOT' from 'true' to 'false'
 in CMakeList.txt.

 - Author: JungWoo LEE (phyjics@gmail.com), Korea Univ.



 1- HOW TO COMPILE

    - Go in to the KUNPLG4 directory (where this README file is in):
        % cd [Path-to-KUNPLG4]

    - Make build directory, go into it and build with CMake.
        % mkdir build
        % cd build
        % cmake ..
        % make 


 2- HOW TO RUN

    - Go intio build directory and execute KUNPLEx1.
        % ./KUNPLEx1
      and type in the commands:
        Idle> /run/beamOn 10 
        Idle> ...
        Idle> exit
      or
        Idle> /control/execute run1.mac
        ....
        Idle> exit

    - Execute KUNPLEx1  in the 'batch' mode from macro files 
      (without visualization)
        % ./KUNPLEx1 run2.mac
        % ./KUNPLEx1 KUNPLEx1.in > KUNPLEx1.out


 3- HOW TO ADD CLASSES

   To add your own classes, open CMakeList.txt and add directory name which
   contains your classes under 'set(KUNPLEx_SOURCE_DIRECTORIES':

      set(KUNPLEx_SOURCE_DIRECTORIES
        Ex1
        Ex1_Action
        [Name of your directory]
        ...
        )


 4- HOW TO ADD EXECUTABLES

   To add your own executables, open CMakeList.txt and add executable name
   (without filename extension) under 'set(KUNPLEx_EXECUTABLE':

      set(KUNPLEx_EXECUTABLES
        KUNPLEx1
        KUNPLEx1_Action
        [Name of your executable]
        ...
        )


 5- HOW TO ADD SCRIPTS

   To add your own scripts, add them in scripts directory, open CMakeList.txt 
   and add scripts name under 'set(KUNPLEx_SCRIPTS':

      set(KUNPLEx_SCRIPTS
        scripts/init.mac
        scripts/init_vis.mac
        scripts/vis.mac
        scripts/run1.mac
        scripts/run2.mac
        [Name of your script]
        ...
        )


 6- USEFUL COMMANDS

   - /run/printProgress [number]
      : Print progress evenry [number] events

