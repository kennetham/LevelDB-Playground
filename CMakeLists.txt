cmake_minimum_required(VERSION 3.3)
project(LevelDB_Playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lleveldb -lpthread -lsnappy")

set(SOURCE_FILES main.cpp main.h)

add_executable(LevelDB_Playground ${SOURCE_FILES})