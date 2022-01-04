cmake_minimum_required(VERSION 3.2)
project(gameBase)

set(CMAKE_BUILD_TYPE Debug)
cmake_policy(SET CMP0015 NEW)

set(states abstractAppState.cpp)
set(core inputManager.cpp mapping.h stateManager.cpp)
set(util util.cpp)
set(GLFW_DIR vb01/external/glfw)

include_directories(../${GLFW_DIR}/include/GLFW)

add_library(gameBase ${states} ${core} ${util})

set(LIB_NAME gameBase)

link_directories(../../build/external/${GLFW_DIR}/src)
target_link_libraries(${LIB_NAME} PUBLIC glfw)
