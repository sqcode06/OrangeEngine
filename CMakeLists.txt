cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME OrangeEngine)
project(${PROJECT_NAME})

add_subdirectory(OrangeEngineCore)
add_subdirectory(OrangeEngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OrangeEngineEditor)