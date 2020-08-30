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

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Simpleton)

if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
	message(STATUS "Using module to find Vulkan")
	find_package(Vulkan REQUIRED)
endif()

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

# STB
set(STB_DIR "${DEP_DIR}/stb")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_DIR}")

# TINYOBJ
set(TINYOBJ_DIR "${DEP_DIR}/tinyobjloader")
target_include_directories(${PROJECT_NAME} PRIVATE "${TINYOBJ_DIR}")

# ASSIMP
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build tools" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Build samples" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Export objects" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "Import FBX" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER OFF CACHE BOOL "Import OBJ" FORCE)
set(ASSIMP_BUILD_OGRE_IMPORTER OFF CACHE BOOL "Import OGRE" FORCE)
set(ASSIMP_BUILD_IRR_IMPORTER OFF CACHE BOOL "Import IRR" FORCE)
set(ASSIMP_BUILD_M3D_IMPORTER OFF CACHE BOOL "Import M3D" FORCE)
set(ASSIMP_BUILD_AMF_IMPORTER OFF CACHE BOOL "Import AMF" FORCE)
set(ASSIMP_BUILD_3DS_IMPORTER OFF CACHE BOOL "Import 3DS" FORCE)
set(ASSIMP_BUILD_AC_IMPORTER OFF CACHE BOOL "Import AC" FORCE)
set(ASSIMP_BUILD_ASE_IMPORTER OFF CACHE BOOL "Import ASE" FORCE)
set(ASSIMP_BUILD_ASSBIN_IMPORTER OFF CACHE BOOL "Import ASSBIN" FORCE)
set(ASSIMP_BUILD_B3D_IMPORTER OFF CACHE BOOL "Import B3D" FORCE)
set(ASSIMP_BUILD_BVH_IMPORTER OFF CACHE BOOL "Import BVH" FORCE)
set(ASSIMP_BUILD_COLLADA_IMPORTER OFF CACHE BOOL "Import COLLADA" FORCE)
set(ASSIMP_BUILD_DXF_IMPORTER OFF CACHE BOOL "Import DXF" FORCE)
set(ASSIMP_BUILD_IRRMESH_IMPORTER OFF CACHE BOOL "Import IRRMESH" FORCE)
set(ASSIMP_DIR "${DEP_DIR}/assimp")
add_subdirectory("${ASSIMP_DIR}" assimp)
target_include_directories(${PROJECT_NAME} PRIVATE "${ASSIMP_DIR}/include")
target_link_libraries(${PROJECT_NAME} "assimp")

# GLAD
set(GLAD_DIR "${DEP_DIR}/glad")
set(GLAD_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/glad")
add_subdirectory("${GLAD_DIR}" glad)
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_BIN_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad")

#Vulkan
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)