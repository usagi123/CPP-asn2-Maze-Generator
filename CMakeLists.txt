cmake_minimum_required(VERSION 3.13)
project(asn2_att1)

set(CMAKE_CXX_STANDARD 14)

add_executable(asn2_att1 main.cpp Edge.h Edge.cpp Coordinator.h Coordinator.cpp Maze.h Maze.cpp HuntAndKillAlgorithm.h HuntAndKillAlgorithm.cpp)