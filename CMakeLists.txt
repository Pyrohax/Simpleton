# Minimum CMake version
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

# Custom macro function to add project filters
macro(add_project_filters path input_list prepend)
  foreach(_source IN ITEMS ${${input_list}})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${prepend}/${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
  endforeach()
endmacro()

# Ensures that we do an out of source build
MACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD MSG)
     STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
     "${CMAKE_BINARY_DIR}" insource)
     GET_FILENAME_COMPONENT(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
     STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
     "${PARENTDIR}" insourcesubdir)
    IF(insource OR insourcesubdir)
        MESSAGE(FATAL_ERROR "${MSG}")
    ENDIF(insource OR insourcesubdir)
ENDMACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)

MACRO_ENSURE_OUT_OF_SOURCE_BUILD(
    "${CMAKE_PROJECT_NAME} requires an out of source build."
)

# Generated project name
project(Simpleton)

# C++ standard (C++17)
set(CMAKE_CXX_STANDARD 17)

# Packages
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
	message(STATUS "Using module to find Vulkan")
	find_package(Vulkan REQUIRED)
endif()

# Add filters/folders for the generated projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

# Executable definition and properties
file(GLOB_RECURSE SRC
    "${SRC_DIR}/*.cpp"
)

file(GLOB_RECURSE INC
    "${SRC_DIR}/*.h"
)

add_executable(${PROJECT_NAME} ${SRC} ${INC})

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# GLM
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm")

#Vulkan
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

# Add project filters to VS
add_project_filters(${SRC_DIR} SRC Source)
add_project_filters(${SRC_DIR} INC Include)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# Debugging
message(STATUS "This is the BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is the SOURCE dir " ${PROJECT_SOURCE_DIR})