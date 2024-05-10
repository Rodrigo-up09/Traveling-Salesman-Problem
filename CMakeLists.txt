cmake_minimum_required(VERSION 3.26)
project(projetDA2)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(projetDA2 src/main.cpp
        src/Graph/graph.cpp
        src/Graph/graph.h
        src/Menu/menu.h
        src/Menu/menu.cpp
        src/DataManager/DataManager.h
        src/DataManager/DataManager.cpp
        src/MainFunctions/BacktrackingAlgorithm.h
        src/MainFunctions/BakctrackingAlgorithm.cpp
        src/MainFunctions/OtherHeuristics.cpp
        src/MainFunctions/TriangularApproximation.cpp
        src/MainFunctions/TSPInTheRealWorld.cpp
)