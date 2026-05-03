cmake_minimum_required(VERSION 3.5)
project(Engine)

set(LIB_NAME Engine)

set(CORE_SRC
    Source/Core/Private/util.cpp)

set(SYSTEMS_SRC
    Source/Systems/Private/abstractAppState.cpp
    Source/Systems/Private/stateManager.cpp
    Source/Systems/Private/soundManager.cpp)

set(PLATFORM_SRC
    Source/Platform/Private/inputManager.cpp)

set(SCRIPTING_SRC
    Source/Scripting/Private/solUtil.cpp)

set(ENGINE_SRC ${CORE_SRC} ${SYSTEMS_SRC} ${PLATFORM_SRC} ${SCRIPTING_SRC})

add_library(${LIB_NAME} ${ENGINE_SRC})

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Systems/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Scripting/Public)

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/ThirdParty)

target_include_directories(${LIB_NAME} PUBLIC ${THIRDPARTY_DIR}/GLFW/include)
target_link_libraries(${LIB_NAME} PUBLIC glfw)

target_include_directories(${LIB_NAME} PUBLIC
    ${THIRDPARTY_DIR}/Lua/upstream)
target_link_libraries(${LIB_NAME} PUBLIC lua::lib)

target_include_directories(${LIB_NAME} PUBLIC
    ${THIRDPARTY_DIR}/sol2/include)

target_include_directories(${LIB_NAME} PUBLIC
    ${THIRDPARTY_DIR}/SFML/include)
target_link_libraries(${LIB_NAME} PUBLIC sfml-system sfml-audio)
