# Lager Demo Project for SAME70 XPLD Development Kits
## Project Description
This is a demo project for the ATSAME70 MCU that helps users to learn the many different features of the Lager CLI tool.  
With this demo, users can:  
1. Learn how to build a project inside a docker container
2. Remotely flash and run an application on a DUT (in this case the SAME70-XPLD board)
3. See how unit testing can be incorporated into their work flow via the Unity Testing Framework
4. Set up a continuous integration pipeline

## Pre-requisite
Before experimenting with this project there are a couple of pre-requisites  
1. Install docker client for your operating system (https://www.docker.com/products/docker-desktop)
2. Install Lager's CLI tool:  
`pip3 install lager-cli`
  

## Build Instructions
A Lager environment with build instructions is included in this repository.  
To build the project simply run: `lager exec build`  
This will build all the targets in this project.  
To see the different build options run:  
`lager devenv commands`  
If you would like to create a development environment from scratch do the following:  
`lager devenv delete` This deletes the current development environment  
`lager devenv create` This creates a new development environment.  
This will instruct users to choose a development environment image (e.g. cortex-m, stm32, ti, etc), where to mount their project in the docker container, and what shell type to use. For this project the default settings are OK.  
*Note: Search "lagerdata" on hub.docker.com to view other development environments supported by Lager*  
  
To create a new build command run:  
`lager exec --command "user defined build command" --save-as user-defined-shortcut `  

For example, to build this project using CMake + Ninja a user can define the following:  
`lager exec --command "mkdir -p _build;cd _build; cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-gcc-toolchain.cmake;cmake --build ." --save-as my_build_cmd`  
Moving forward a user could then run `lager exec my_build_cmd`  
Similarly to create a "clean" command a user could do:  
`lager exec --comman "rm -rf _build" --save-as my_clean_cmd`  
and run it as `lager exec my_clean_cmd`  


## Flashing The Board
#### Connect To board
To flash a board first connect the Lager Gateway to the SAME70 development board.  
There are two options to do this:  
1. USB2.0 - This will allow users to use the CMSIS-DAP debug probe built into the SAME70 development board
 
  
Then run:  
`lager connect --device atsame70 --interface cmsis-dap --transport swd --speed 4000`  
or if using built-in debug probe  
`lager connect --device atsame70 --interfact cmsis-dap --transport swd --speed 4000`  
  
#### Flash Image
To flash the board with the project application run the following:  
`lager flash --hexfile _build/app/app.hex`  

## Unit Tests
To run an example unit-test for this project run the following:  
`lager testrun --serial-device /dev/ttyACM0 --hexfile _build/unit-tests/test-suites/test-example/test-example.hex`  
The results of the individual tests will be streamed back to the terminal.  
  
## Drone Setup
To test Drone integration firs make sure the demo repository is forked, then go to drone.app.lagerdata.com and 'Activate' the repository.  
There is already a .drone.yml in the project. You can open it to examine which test images will be flashed to the board and run.  
You can test a deploy by doing an empty commit, and then pushing to the remote repo.  
`git commit --allow-empty`  
`git push`  
You can view progress of the deploy by going to drone.app.lagerdata.com, selecting the demo repository, clicking on the latest commit, and choosing "Activity Feed".  