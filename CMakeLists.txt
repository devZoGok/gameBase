cmake_minimum_required(VERSION 3.5)
project(gameBase)

set(CMAKE_BUILD_TYPE Debug)
cmake_policy(SET CMP0015 NEW)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CORE_SRC
    source/core/abstractAppState.cpp
    source/core/stateManager.cpp
    source/core/inputManager.cpp
    source/core/soundManager.cpp)

set(UTILS_SRC
	source/utils/solUtil.cpp
    source/utils/util.cpp)

set(LIB_NAME gameBase)
add_library(${LIB_NAME} ${CORE_SRC} ${UTILS_SRC})

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
