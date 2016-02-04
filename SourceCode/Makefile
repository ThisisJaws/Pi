# Makefile for Irrlicht Examples
# It's usually sufficient to change just the target name and source file list
# and be sure that CXX is set to a valid compiler
Target = linuxBuild
Sources = main.cpp EventReceiver.cpp Game.cpp Testing.cpp Object.cpp Bullet.cpp Ship.cpp PlayerShip.cpp EnemyShip.cpp StaticObject.cpp BasicEnemy.cpp StrongEnemy.cpp FastEnemy.cpp Collectable.cpp Gem.cpp Ammo.cpp World.cpp LavaWorld.cpp IceWorld.cpp JungleWorld.cpp SoundManager.cpp ScoreScreen.cpp

#for use with g++ 4.7
Sources += -std=c++11

#location of irrlicht lib and include folders
IrrlichtHome = ../Irrlicht_1.9.0_OGL-ES

#use g++-4.7
CXX = g++-4.7

#where to compile the file to
Bin = .

# general compiler settings
CPPFLAGS = -I$(IrrlichtHome)/include -I/usr/X11R6/include
CXXFLAGS = -O3 -ffast-math -Wl,--rpath -Wl,LIBDIR
#CXXFLAGS = -g -Wall

#default target is Linux
all: all_linux

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif

OGLESLIBS := -L$(HOME)/irrlicht/SDKPackage-ogles1/Builds/OGLES/LinuxPC/Lib -L/opt/vc/lib -lGLESv1_CM -lGLESv2 -lEGL -lGL -lbcm_host -laudiere
# target specific settings
all_linux: LDFLAGS = -L/usr/X11R6/lib$(LIBSELECT) -L$(IrrlichtHome)/lib/Linux -lIrrlicht $(OGLESLIBS) -lXxf86vm -lXext -lX11 -lXcursor
all_linux clean_linux: SYSTEM=Linux
all_win32: LDFLAGS = -L../../lib/Win32-gcc -lIrrlicht -lopengl32 -lm
all_win32 clean_win32: SYSTEM=Win32-gcc
all_win32 clean_win32: SUF=.exe
# name of the binary - only valid for targets which set SYSTEM
DESTPATH = $(Bin)/$(Target)$(SUF)

all_linux all_win32:
	$(warning Building...)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(Sources) -o $(DESTPATH) $(LDFLAGS)

clean: clean_linux clean_win32
	$(warning Cleaning...)

clean_linux clean_win32:
	@$(RM) $(DESTPATH)

.PHONY: all all_win32 clean clean_linux clean_win32
