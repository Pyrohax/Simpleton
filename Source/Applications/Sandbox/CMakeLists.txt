cmake_minimum_required(VERSION 3.7.0)

file(GLOB SRC
    "*.cpp"
    "*.hpp")

add_executable(Sandbox WIN32 ${SRC})
target_link_libraries(Sandbox PUBLIC Engine)
target_include_directories(Sandbox PUBLIC "../../Engine/")
