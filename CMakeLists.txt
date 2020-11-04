cmake_minimum_required(VERSION 3.7.0)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DUNICODE)
set_property(GLOBAL PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies")

project(Simpleton CXX)

add_subdirectory(Source)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Editor")
