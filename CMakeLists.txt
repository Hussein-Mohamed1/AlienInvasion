cmake_minimum_required(VERSION 3.27)
project(AlienInvasion)

set(CMAKE_CXX_STANDARD 14)

include_directories("Alien Invasion/src")
include_directories("Alien Invasion/src/ds")
include_directories("Alien Invasion/src/units")

add_executable(AlienInvasion
        "Alien Invasion/src/ds/ArrayStack.h"
        "Alien Invasion/src/ds/DoublyLinkedQueue.h"
        "Alien Invasion/src/ds/dsTest.cpp"
        "Alien Invasion/src/ds/LinkedQueue.h"
        "Alien Invasion/src/ds/Node.h"
        "Alien Invasion/src/ds/priNode.h"
        "Alien Invasion/src/ds/priQueue.h"
        "Alien Invasion/src/ds/QueueADT.h"
        "Alien Invasion/src/ds/Source.cpp"
        "Alien Invasion/src/ds/StackADT.h"
        "Alien Invasion/src/units/alienArmy.cpp"
        "Alien Invasion/src/units/alienArmy.h"
        "Alien Invasion/src/units/Army.cpp"
        "Alien Invasion/src/units/Army.h"
        "Alien Invasion/src/units/ASolider.cpp"
        "Alien Invasion/src/units/ASolider.h"
        "Alien Invasion/src/units/Drone.cpp"
        "Alien Invasion/src/units/Drone.h"
        "Alien Invasion/src/units/earthArmy.cpp"
        "Alien Invasion/src/units/earthArmy.h"
        "Alien Invasion/src/units/Egunnery.cpp"
        "Alien Invasion/src/units/Egunnery.h"
        "Alien Invasion/src/units/Esoldier.cpp"
        "Alien Invasion/src/units/Esoldier.h"
        "Alien Invasion/src/units/HealUnit.cpp"
        "Alien Invasion/src/units/HealUnit.h"
        "Alien Invasion/src/units/Monster.cpp"
        "Alien Invasion/src/units/Monster.h"
        "Alien Invasion/src/units/Tank.cpp"
        "Alien Invasion/src/units/Tank.h"
        "Alien Invasion/src/units/unit.cpp"
        "Alien Invasion/src/units/unit.h"
        "Alien Invasion/src/randGen.cpp"
        "Alien Invasion/src/randGen.h"
        "Alien Invasion/src/simulationManager.cpp"
        "Alien Invasion/src/simulationManager.h"
        "Alien Invasion/main.cpp")
