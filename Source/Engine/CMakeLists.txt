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

set(IMGUI_DIR "${DEP_DIR}/imgui")
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

add_library(Engine STATIC ${SRC} ${IMGUI})

source_group("imgui" FILES ${IMGUI})

find_package(Vulkan REQUIRED)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Generate docs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Generate examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Generate tests" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "Use dedicated GPU" FORCE)
set(GLFW_DIR "${DEP_DIR}/glfw")
add_subdirectory("${GLFW_DIR}" glfw)
target_include_directories(Engine PRIVATE "${GLFW_DIR}/include")
target_link_libraries(Engine "glfw")

# VULKAN
target_link_libraries(Engine Vulkan::Vulkan)

# GLM
set(GLM_DIR "${DEP_DIR}/glm")
target_include_directories(Engine PUBLIC "${GLM_DIR}")

# STB
set(STB_DIR "${DEP_DIR}/stb")
target_include_directories(Engine PRIVATE "${STB_DIR}")

# TINYOBJ
set(TINYOBJ_DIR "${DEP_DIR}/tinyobjloader")
target_include_directories(Engine PRIVATE "${TINYOBJ_DIR}")

# TINYGLTF
set(TINYGLTF_DIR "${DEP_DIR}/tinygltf")
target_include_directories(Engine PRIVATE "${TINYGLTF_DIR}")

# STDUUID
set(STDUUID_DIR "${DEP_DIR}/stduuid")
add_subdirectory("${STDUUID_DIR}" stuuid)
target_include_directories(Engine PUBLIC "${STDUUID_DIR}/include")

# GLAD
set(GLAD_DIR "${DEP_DIR}/glad")
set(GLAD_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/glad")
add_subdirectory("${GLAD_DIR}" glad)
target_include_directories(Engine PRIVATE "${GLAD_BIN_DIR}/include")
target_link_libraries(Engine "glad")

# IMGUI
target_include_directories(Engine PRIVATE "${IMGUI_DIR}")

# RAPIDJSON
set(RAPIDJSON_DIR "${DEP_DIR}/rapidjson/include")
target_include_directories(Engine PRIVATE "${RAPIDJSON_DIR}")

# ENTT
set(ENTT_DIR "${DEP_DIR}/entt")
target_include_directories(Engine PUBLIC "${ENTT_DIR}/src")

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)
