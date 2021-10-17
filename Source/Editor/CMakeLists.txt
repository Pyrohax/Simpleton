cmake_minimum_required(VERSION 3.7.0)

file(GLOB SRC
    "*.cpp"
    "*.hpp"
    "*.h")

add_executable(Editor WIN32 ${SRC})

set_target_properties(Editor PROPERTIES FOLDER Pyrohax)

target_link_libraries(Editor PUBLIC Engine)
target_include_directories(Editor PUBLIC "../Engine/")
