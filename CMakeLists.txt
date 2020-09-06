cmake_minimum_required(VERSION 3.7.0)

# Custom macro function to add project filters
macro(ADD_PROJECT_FILTERS path input_list prepend)
  foreach(_source IN ITEMS ${${input_list}})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${prepend}/${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
  endforeach()
endmacro()

set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Simpleton)

set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS 
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.hpp"
)

add_executable(${PROJECT_NAME} ${SRC})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Generate docs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Generate examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Generate tests" FORCE)
set(GLFW_DIR "${DEP_DIR}/glfw")
add_subdirectory("${GLFW_DIR}" glfw)
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glfw")

# GLM
set(GLM_DIR "${DEP_DIR}/glm")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLM_DIR}")

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)
