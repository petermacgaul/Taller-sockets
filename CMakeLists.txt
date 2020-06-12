cmake_minimum_required(VERSION 3.16)
project(untitled1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES
        main.cpp
        Server.cpp Server.h
        Client.cpp Client.h

        CommunicateData.h QueueMultithread.h)


add_executable(untitled1 ${SOURCE_FILES})
# link libraries

target_link_libraries(untitled1 ${SDL2_LIBRARY})
