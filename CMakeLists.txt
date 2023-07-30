cmake_minimum_required(VERSION 3.2)
project(gameBase)

set(CMAKE_BUILD_TYPE Debug)
cmake_policy(SET CMP0015 NEW)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(states abstractAppState.cpp)
set(core inputManager.cpp mapping.h stateManager.cpp luaManager.cpp)
set(util util.cpp)

set(GLFW_DIR vb01/external/glfw)
set(LUA_DIR external/lua-cmake)

include_directories(../${GLFW_DIR}/include/GLFW)

set(LUA_LIB_DIR ${LUA_DIR})
add_subdirectory(${LUA_DIR})

set(LIB_NAME gameBase)
add_library(${LIB_NAME} STATIC ${states} ${core} ${util})
set(GLFW_DIR ../vb01/external/glfw)

set(GLFW_LIB_DIR ../vb01/build/external/glfw/src)
target_include_directories(${LIB_NAME} PUBLIC ${GLFW_DIR}/include/GLFW)
target_link_directories(${LIB_NAME} PUBLIC ${GLFW_LIB_DIR})

target_link_libraries(${LIB_NAME} glfw lua::lib)
