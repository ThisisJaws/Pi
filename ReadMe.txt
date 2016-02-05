To run and play Space Trip on a Pi machine do the following
1. Install the following libraries to get irrlicht working
	--Normal irrlicht libs
		sudo apt-get install build-essential
		sudo apt-get install freeglut3 freeglut3-dev freeglut3-dbg
		sudo apt-get install build-essential xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxext-dev libxcursor-dev
	--Irrlicht ogl-es libs
		sudo apt-get install libgl1-mesa-swx11
		sudo apt-get install libgl1-mesa-glx
		sudo apt-get install libgles1-mesa-dev
		sudo apt-get install libgles2-mesa-dev
2. Navigate to the irrlicht source directory (Irrlicht_1.9.0_OGL-ES/source/Irrlicht) and type 'make' to compile the engine
3. Navigate to the audiere directory (audiere-1.9.4) and type './configure && make && sudo make install' to compile the audiere engine
4. After audiere has finished make sure to type 'sudo ldconfig' to make sure all libraries are linked
5. Make sure to type 'sudo modprobe snd_pcm_oss' so audiere has the right drivers, this will have to be done everytime the Pi restarts
6. Navigate to the SourceCode folder and type 'make' to compile the game
7. Inside the SourceCode folder type ./linuxBuild to run the game