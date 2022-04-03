cmake_minimum_required(VERSION 3.2)
project(gameBase)

set(CMAKE_BUILD_TYPE Debug)
cmake_policy(SET CMP0015 NEW)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(states abstractAppState.cpp)
set(core inputManager.cpp mapping.h stateManager.cpp luaManager.cpp)
set(util util.cpp)

set(GLFW_DIR vb01/external/glfw)
set(LUA_DIR external/lua)

include_directories(../${GLFW_DIR}/include/GLFW)

set(LUA_LIB_DIR ${LUA_DIR})
include_directories(${LUA_DIR})
link_directories(${LUA_DIR})

add_library(gameBase STATIC ${states} ${core} ${util})
set(GLFW_DIR ../vb01/external/glfw)
set(LIB_NAME gameBase)

set(GLFW_LIB_DIR ../vb01/build/external/glfw/src)
target_include_directories(${LIB_NAME} PUBLIC ${GLFW_DIR}/include/GLFW)
target_link_directories(${LIB_NAME} PUBLIC ${GLFW_LIB_DIR})

target_link_libraries(${LIB_NAME} lua)
target_link_libraries(gameBase glfw)

