--UNFINISHED INSTRUCTIONS--

To run and play Space Trip on a Pi machine do the following
1. install the following libraries to get irrlicht working
--normal irrlicht libs
--irrlicht ogl-es libs
2. navigate to the irrlicht source directory and type 'make' to compile the engine
3. navigate to the audiere directory and type './configure && make && sudo make install' to compile the audiere engine
4. after audiere has finished make sure to type 'sudo ldconfig' to make sure all libraries are linked
5. make sure to type 'sudo modprobe snd_pcm_oss' so audiere has the right drivers
6. navigate to the SourCode folder and type 'make' to compile the game
7. play and enjoy