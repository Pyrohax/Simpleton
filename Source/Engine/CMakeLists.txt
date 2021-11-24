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

set(IMGUI_DIR "${SUBMODULES_DIR}/imgui")
set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/")

file(GLOB IMGUI
  "${IMGUI_DIR}/imconfig.h"
  "${IMGUI_DIR}/imgui.h"
  "${IMGUI_DIR}/imgui_internal.h"
  "${IMGUI_DIR}/imstb_rectpack.h"
  "${IMGUI_DIR}/imstb_textedit.h"
  "${IMGUI_DIR}/imstb_truetype.h"
  "${IMGUI_DIR}/backends/imgui_impl_vulkan.h"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.h"
  "${IMGUI_DIR}/backends/imgui_impl_glfw.h"
  "${IMGUI_DIR}/imgui.cpp"
  "${IMGUI_DIR}/imgui_draw.cpp"
  "${IMGUI_DIR}/imgui_tables.cpp"
  "${IMGUI_DIR}/imgui_widgets.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
)

file(GLOB_RECURSE SRC SRC_DIR
    "*.cpp"
    "*.h"
    "*.hpp")

# Vulkan
find_package(Vulkan REQUIRED)

# GLFW
add_library(GLFW STATIC IMPORTED)
set_target_properties(GLFW PROPERTIES
  IMPORTED_LOCATION "${DEPENDENCIES_DIR}/GLFW/src/Debug/glfw3.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${SUBMODULES_DIR}/GLFW/include"
)

# GLAD
add_library(GLAD STATIC IMPORTED)
set_target_properties(GLAD PROPERTIES
  IMPORTED_LOCATION "${DEPENDENCIES_DIR}/GLAD/Debug/glad.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/GLAD/include"
)

add_library(Engine STATIC ${SRC} ${IMGUI})

set_target_properties(Engine PROPERTIES FOLDER Pyrohax)

source_group("imgui" FILES ${IMGUI})

# Vulkan
target_link_libraries(Engine ${Vulkan_LIBRARIES})
target_include_directories(Engine PRIVATE ${Vulkan_INCLUDE_DIRS})

# GLFW
target_link_libraries(Engine GLFW)

# GLAD
target_link_libraries(Engine GLAD)

# GLM
target_include_directories(Engine PUBLIC "${SUBMODULES_DIR}/GLM")

# STB
target_include_directories(Engine PRIVATE "${SUBMODULES_DIR}/STB")

# TinyOBJLoader
target_include_directories(Engine PRIVATE "${SUBMODULES_DIR}/TinyOBJLoader")

# TinyGLTF
target_include_directories(Engine PRIVATE "${SUBMODULES_DIR}/TinyGLTF")

# STDUUID
target_include_directories(Engine PUBLIC "${SUBMODULES_DIR}/STDUUID/include")

# IMGUI
target_include_directories(Engine PRIVATE "${IMGUI_DIR}")

# RapidJSON
target_include_directories(Engine PRIVATE "${SUBMODULES_DIR}/RapidJSON/include")

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)
