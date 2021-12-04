cmake_minimum_required(VERSION 3.2)
project(gameBase)

set(CMAKE_BUILD_TYPE Debug)
cmake_policy(SET CMP0015 NEW)

set(states abstractAppState.cpp)
set(core inputManager.cpp mapping.h stateManager.cpp)
set(util util.cpp)

add_library(gameBase ${states} ${core} ${util})

set(GLFW_DIR external/glfw)
set(LIB_NAME gameBase)

add_subdirectory(${GLFW_DIR})
set(GLFW_LIB_DIR build/${GLFW_DIR}/src)
target_include_directories(${LIB_NAME} PUBLIC ${GLFW_DIR}/include/GLFW)
target_link_directories(${LIB_NAME} PUBLIC ${GLFW_LIB_DIR})

target_link_libraries(gameBase glfw)
