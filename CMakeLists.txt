# Minimum CMake version
cmake_minimum_required(VERSION 3.1)

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

# GLAD
set(GLAD_DIR "${LIB_DIR}/glad")
add_subdirectory("${GLAD_DIR}")
target_link_libraries(${PROJECT_NAME} "glad" "${GLAD_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include")

# Add project filters to VS
add_project_filters(${SRC_DIR} SRC Source)
add_project_filters(${SRC_DIR} INC Include)

# Debugging
message(STATUS "This is the BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is the SOURCE dir " ${PROJECT_SOURCE_DIR})