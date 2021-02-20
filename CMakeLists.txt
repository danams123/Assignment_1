cmake_minimum_required(VERSION 3.17)
project(Assignment_1)

SET(CMAKE_CXX_STANDARD 11)


add_executable(Assignment_1 src/main.cpp include/Session.h src/Session.cpp include/Agent.h src/Agent.cpp include/Graph.h
        src/Graph.cpp include/Tree.h src/Tree.cpp)