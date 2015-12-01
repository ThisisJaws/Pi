#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++-4.6
CXX=g++-4.6
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Ammo.o \
	${OBJECTDIR}/BasicEnemy.o \
	${OBJECTDIR}/Bullet.o \
	${OBJECTDIR}/Collectable.o \
	${OBJECTDIR}/EnemyShip.o \
	${OBJECTDIR}/EventReceiver.o \
	${OBJECTDIR}/FastEnemy.o \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/Gem.o \
	${OBJECTDIR}/Object.o \
	${OBJECTDIR}/PlayerShip.o \
	${OBJECTDIR}/Ship.o \
	${OBJECTDIR}/StaticObject.o \
	${OBJECTDIR}/StrongEnemy.o \
	${OBJECTDIR}/Testing.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsourcecode.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsourcecode.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsourcecode.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsourcecode.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsourcecode.a

${OBJECTDIR}/Ammo.o: Ammo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ammo.o Ammo.cpp

${OBJECTDIR}/BasicEnemy.o: BasicEnemy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BasicEnemy.o BasicEnemy.cpp

${OBJECTDIR}/Bullet.o: Bullet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Bullet.o Bullet.cpp

${OBJECTDIR}/Collectable.o: Collectable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Collectable.o Collectable.cpp

${OBJECTDIR}/EnemyShip.o: EnemyShip.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EnemyShip.o EnemyShip.cpp

${OBJECTDIR}/EventReceiver.o: EventReceiver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EventReceiver.o EventReceiver.cpp

${OBJECTDIR}/FastEnemy.o: FastEnemy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FastEnemy.o FastEnemy.cpp

${OBJECTDIR}/Game.o: Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/Gem.o: Gem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gem.o Gem.cpp

${OBJECTDIR}/Object.o: Object.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Object.o Object.cpp

${OBJECTDIR}/PlayerShip.o: PlayerShip.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PlayerShip.o PlayerShip.cpp

${OBJECTDIR}/Ship.o: Ship.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ship.o Ship.cpp

${OBJECTDIR}/StaticObject.o: StaticObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StaticObject.o StaticObject.cpp

${OBJECTDIR}/StrongEnemy.o: StrongEnemy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StrongEnemy.o StrongEnemy.cpp

${OBJECTDIR}/Testing.o: Testing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Testing.o Testing.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../irrlicht-1.8.3/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsourcecode.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
