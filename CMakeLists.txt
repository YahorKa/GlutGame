#MyGame
cmake_minimum_required(VERSION 3.12) # version can be different
project(MyGame)
#add_subdirectory(googletest) # add googletest subdirectory
#include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
message(${OPENGL_INCLUDE_DIR})
add_executable(MyGame  MyGame.cpp) 
#add_executable(MyGame  sship.cpp) 
target_link_libraries(MyGame ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
#target_link_libraries(mytests PRIVATE gtest) 
