cmake_minimum_required(VERSION 3.7.0)

file(GLOB SRC
    "*.cpp"
    "*.hpp"
    "*.h")

add_executable(Editor WIN32 ${SRC})
target_link_libraries(Editor PUBLIC Engine)
target_include_directories(Editor PUBLIC "../Engine/")

# GLM
set(GLM_DIR "${DEP_DIR}/glm")
target_include_directories(Editor PRIVATE "${GLM_DIR}")
