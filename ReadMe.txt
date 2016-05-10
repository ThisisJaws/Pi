To run and play Space Trip on a Pi machine do the following:
1. Install the following libraries to compile Space Trip
	--Normal irrlicht libs
		sudo apt-get install build-essential
		sudo apt-get install freeglut3 freeglut3-dev freeglut3-dbg
		sudo apt-get install build-essential xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxext-dev libxcursor-dev
	--Irrlicht ogl-es libs
		sudo apt-get install libgl1-mesa-swx11
		sudo apt-get install libgl1-mesa-glx
		sudo apt-get install libgles1-mesa-dev
		sudo apt-get install libgles2-mesa-dev
	--Used to compile the game
		sudo apt-get install g++-4.7
	--SFML for the audio module
		sudo apt-get install libsfml-dev
2. Navigate to the irrlicht source directory (Irrlicht_1.9.0_OGL-ES/source/Irrlicht) and type 'make NDEBUG=1' to compile the engine
3. Navigate to the SourceCode folder and type 'make' to compile the game
4. Inside the SourceCode folder type ./linuxBuild to run the game

If you would like to use an xbox 360 gamepad for input then do the following:
1. Install the xbox pad driver
	sudo apt-get install xboxdrv
There are now two ways to set up your pad
2a. Before the game is launched type in the following with the pad connected:
	sudo xboxdrv --trigger-as-button --id 0 --led 2 --deadzone 4000 --silent & sleep 1
2b. To detect and activate the pad on start up do the following:
		sudo nano /etc/rc.local
	then place your cursor between the "fi" and "exit 0" lines and type:
		xboxdrv --trigger-as-button --id 0 --led 2 --deadzone 4000 --silent & sleep 1
	Then reboot the pi
		sudo reboot
	Your pad will have to be connected each time you restart the pi, otherwise refer to step 2a.
3. You may get the error LIBUSB_ERROR_ACCESS if this is the case then add the following after xboxdrv and before --trigger-as-button
	--detach-kernel-driver
