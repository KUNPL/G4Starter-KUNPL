# Geant4 Starter for KUNPL


These Geant4 examples are tutorial and template for Korea University 
Nuclear Physics Lab (KUNPL) Geant4 primary users. 

- Examples were tested with Geant4 version 4.10.02.

- CMakeList contains dependency of ROOT. If you think this causes
problem (you may not have ROOT for example), set 
variable 'useROOT' from 'true' to 'false' in CMakeList.txt.

---

###1. How to compile

- Go into the G4Starter-KUNPL directory:
  ```sh
  > cd [Path-to-KUNPLG4]
  ```

- Make build directory, go into it and build with cmake:
  ```sh
  > mkdir build  
  > cd build  
  > cmake ..  
  > make   
  ```


###2. How to run

After compiling, executables are created in build directory.
You have two choices now. Eather 1) type commands by yourself, 
2) or use macros you wrote beforehand.

####1) Former case
- Execute executable and type in the commands:
  ```sh
  > ./KUNPLEx1
  
  Starting Geant4 kernal...
  
  Idle> /run/beamOn 10  
  Idle> ...  
  Idle> exit  
  ```
  
####2) Later case
- Execute executable and load macro file
  ```sh
  > ./KUNPLEx1
  
  Starting Geant4 kernal...
  
  Idle> /control/execute macros/run1.mac  
  ....  
  Idle> exit  
  ```

- Execute executable in the 'batch' mode from macro files:
  ```sh
  > ./KUNPLEx1 macros/run1.mac  
  ```

- Or if you want output, you may do:
  ```sh
  > ./KUNPLEx1 macros/KUNPLEx1.in > KUNPLEx1.out  
  ```

###3. How to add classes

To add your own classes, open CMakeList.txt and add directory name which
contains your classes under 'set(KUNPLEx_SOURCE_DIRECTORIES':  

```cmake
set(KUNPLEx_SOURCE_DIRECTORIES  
  Ex1  
  Ex1_Action  
  [Name of your directory]  
  ...  
  )  
```

###4. How to add executables

To add your own executables, open CMakeList.txt and add executable name
(without filename extension) under 'set(KUNPLEx_EXECUTABLE':

```cmake
set(KUNPLEx_EXECUTABLES
  KUNPLEx1
  KUNPLEx1_Action
  [Name of your executable]
  ...
  )
```


###5. How to add macros

To add your own macros(.in or .mac), 1) add them in macros directory,
2) open CMakeList.txt and add macro names under 'set(KUNPLEx_SCRIPTS':

```cmake
set(KUNPLEx_SCRIPTS
  scripts/init.mac
  scripts/init_vis.mac
  scripts/vis.mac
  scripts/run1.mac
  scripts/run2.mac
  [Name of your script]
  ...
  )
```
