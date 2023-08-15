cmake_minimum_required(VERSION 3.2)
project(gameBase)

cmake_policy(SET CMP0015 NEW)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_TESTS ON)

set(STATES abstractAppState.cpp)
set(CORE inputManager.cpp mapping.h stateManager.cpp luaManager.cpp luaFields.cpp)
set(UTIL util.cpp)
set(LIB_SRC ${STATES} ${CORE} ${UTIL})

set(GLFW_DIR vb01/external/glfw)
set(LUA_DIR external/lua)

include_directories(../${GLFW_DIR}/include/GLFW)

set(LUA_LIB_DIR ${LUA_DIR})
include_directories(${LUA_DIR})
link_directories(${LUA_DIR})

add_library(gameBase STATIC ${LIB_SRC})
set(GLFW_DIR ../vb01/external/glfw)
set(LIB_NAME gameBase)

set(GLFW_LIB_DIR ../vb01/build/external/glfw/src)
target_include_directories(${LIB_NAME} PUBLIC ${GLFW_DIR}/include/GLFW)
target_link_directories(${LIB_NAME} PUBLIC ${GLFW_LIB_DIR})

set(DEPS lua glfw)
target_link_libraries(${LIB_NAME} ${DEPS})

if(BUILD_TESTS)
	if(UNIX)
		include_directories(/usr/include/cppunit)
		link_directories(/usr/lib)
	elseif(WIN32)
		include_directories(C:/Program\ Files\ \(x86\)/cppunit/include)
		link_directories(C:/Program\ Files\ \(x86\)/cppunit/lib)
	endif()
	
	set(TEST_SRC main.cpp ${LIB_SRC} luaFieldsTest.cpp)
	
	add_executable(gameBaseTests ${TEST_SRC})
	target_link_libraries(gameBaseTests ${LIB_NAME} ${DEPS} cppunit)
endif()
