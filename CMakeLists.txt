cmake_minimum_required(VERSION 3.5)
project(gameBase)

set(CMAKE_BUILD_TYPE Debug)
cmake_policy(SET CMP0015 NEW)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(states abstractAppState.cpp)
set(core inputManager.cpp mapping.h stateManager.cpp soundManager.cpp)
set(util solUtil.cpp util.cpp)

set(LIB_NAME gameBase)
add_library(${LIB_NAME} ${states} ${core} ${util})

set(GLFW_DIR external/glfw)
set(GLFW_LIB_DIR build/external/glfw/src)
target_include_directories(${LIB_NAME} PUBLIC ${GLFW_DIR}/include/GLFW)
target_link_directories(${LIB_NAME} PUBLIC ${GLFW_LIB_DIR})

set(LUA_DIR external/lua-cmake)
add_subdirectory(${LUA_DIR})
target_include_directories(${LIB_NAME} PUBLIC ${LUA_DIR}/external/upstream)

set(SOL_DIR external/sol2)
add_subdirectory(${SOL_DIR})
target_include_directories(${LIB_NAME} PUBLIC ${SOL_DIR}/include)

set(SFML_DIR external/SFML)
add_subdirectory(${SFML_DIR})
set(SFML_LIB_DIR build/${SFML_DIR}/src)
target_include_directories(${LIB_NAME} PUBLIC ${SFML_DIR}/include)
target_link_directories(${LIB_NAME} PUBLIC ${SFML_LIB_DIR})

target_link_libraries(${LIB_NAME} sfml-system sfml-audio glfw lua::lib)
