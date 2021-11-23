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

set_target_properties(Engine PROPERTIES FOLDER Pyrohax)

source_group("imgui" FILES ${IMGUI})

find_package(Vulkan REQUIRED)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Generate docs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Generate examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Generate tests" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "Use dedicated GPU" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "GLFW_INSTALL" FORCE)
set(GLFW_DIR "${DEP_DIR}/glfw")
add_subdirectory("${GLFW_DIR}" glfw)
target_include_directories(Engine PRIVATE "${GLFW_DIR}/include")
target_link_libraries(Engine "glfw")
set_target_properties(glfw PROPERTIES FOLDER Dependencies)

# VULKAN
target_link_libraries(Engine Vulkan::Vulkan)
set_target_properties(Vulkan::Vulkan PROPERTIES FOLDER Dependencies)

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
set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF CACHE BOOL "TINYGLTF_BUILD_LOADER_EXAMPLE" FORCE)
set(TINYGLTF_INSTALL OFF CACHE BOOL "TINYGLTF_INSTALL" FORCE)
set(TINYGLTF_DIR "${DEP_DIR}/tinygltf")
target_include_directories(Engine PRIVATE "${TINYGLTF_DIR}")

# STDUUID
set(UUID_BUILD_TESTS OFF CACHE BOOL "UUID_BUILD_TESTS" FORCE)
set(STDUUID_DIR "${DEP_DIR}/stduuid")
target_include_directories(Engine PUBLIC "${STDUUID_DIR}/include")

# GLAD
set(GLAD_DIR "${DEP_DIR}/glad")
set(GLAD_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/glad")
add_subdirectory("${GLAD_DIR}" glad)
target_include_directories(Engine PRIVATE "${GLAD_BIN_DIR}/include")
target_link_libraries(Engine "glad")
set_target_properties(glad PROPERTIES FOLDER Dependencies)

# IMGUI
target_include_directories(Engine PRIVATE "${IMGUI_DIR}")

# RAPIDJSON
set(RAPIDJSON_DIR "${DEP_DIR}/rapidjson/include")
target_include_directories(Engine PRIVATE "${RAPIDJSON_DIR}")

# ENTT
set(ENTT_BUILD_TESTING OFF CACHE BOOL "ENTT_BUILD_TESTING" FORCE)
set(ENTT_BUILD_DOCS OFF CACHE BOOL "ENTT_BUILD_DOCS" FORCE)
set(ENTT_DIR "${DEP_DIR}/entt")
target_include_directories(Engine PUBLIC "${ENTT_DIR}/src")

# SHADERC
set(SHADERC_SKIP_TESTS ON CACHE BOOL "SHADERC_SKIP_TESTS" FORCE)
set(SHADERC_SKIP_EXAMPLES ON CACHE BOOL "SHADERC_SKIP_EXAMPLES" FORCE)
set(SHADERC_SKIP_INSTALL ON CACHE BOOL "SHADERC_SKIP_INSTALL" FORCE)
set(SHADERC_SKIP_COPYRIGHT_CHECK ON CACHE BOOL "SHADERC_SKIP_COPYRIGHT_CHECK" FORCE)
set(SHADERC_ENABLE_WGSL_OUTPUT OFF CACHE BOOL "SHADERC_ENABLE_WGSL_OUTPUT" FORCE)
set(ENABLE_HLSL ON CACHE BOOL "ENABLE_HLSL" FORCE)
set(ENABLE_CTEST OFF CACHE BOOL "ENABLE_CTEST" FORCE)
set(ENABLE_GLSLANG_WEBMIN OFF CACHE BOOL "ENABLE_GLSLANG_WEBMIN" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "BUILD_TESTING" FORCE)
set(SPIRV_HEADERS_SKIP_EXAMPLES ON CACHE BOOL "SPIRV_HEADERS_SKIP_EXAMPLES" FORCE)
set(SPIRV_HEADERS_SKIP_INSTALL ON CACHE BOOL "SPIRV_HEADERS_SKIP_INSTALL" FORCE)
set(SKIP_SPIRV_TOOLS_INSTALL OFF CACHE BOOL "SKIP_SPIRV_TOOLS_INSTALL" FORCE)
set(SPIRV_BUILD_COMPRESSION OFF CACHE BOOL "SPIRV_BUILD_COMPRESSION" FORCE)
set(SPIRV_BUILD_FUZZER OFF CACHE BOOL "SPIRV_BUILD_FUZZER" FORCE)
set(SPIRV_BUILD_LIBFUZZER_TARGETS OFF CACHE BOOL "SPIRV_BUILD_LIBFUZZER_TARGETS" FORCE)
set(SPIRV_COLOR_TERMINAL OFF CACHE BOOL "SPIRV_COLOR_TERMINAL" FORCE)
set(SPIRV_SKIP_EXECUTABLES ON CACHE BOOL "SPIRV_SKIP_EXECUTABLES" FORCE)
set(SPIRV_SKIP_TESTS ON CACHE BOOL "SPIRV_SKIP_TESTS" FORCE)
set(ENABLE_SPIRV_TOOLS_INSTALL OFF CACHE BOOL "ENABLE_SPIRV_TOOLS_INSTALL" FORCE)
set(SHADERC_SPIRV_TOOLS_DIR "${DEP_DIR}/SPIRV-Tools" CACHE STRING "SHADERC_SPIRV_TOOLS_DIR" FORCE)
set(SHADERC_SPIRV_HEADERS_DIR "${DEP_DIR}/SPIRV-Headers" CACHE STRING "SHADERC_SPIRV_HEADERS_DIR" FORCE)
set(SHADERC_GLSLANG_DIR "${DEP_DIR}/glslang" CACHE STRING "SHADERC_GLSLANG_DIR" FORCE)
set(SHADERC_DIR "${DEP_DIR}/shaderc")
add_subdirectory("${SHADERC_DIR}" shaderc)
target_include_directories(Engine PUBLIC "${SHADERC_DIR}")
target_link_libraries(Engine "shaderc")
set_target_properties(shaderc PROPERTIES FOLDER Dependencies)

set_target_properties(add-copyright update_mappings build-version core_tables 
    enum_string_mapping extinst_tables glad-generate-files glslc glslc_exe
    install-headers shaderc_combined_genfile shaderc_combined-pkg-config
    shaderc_shared shaderc_static-pkg-config shaderc_util shaderc-pkg-config
    spirv-tools-pkg-config spirv-tools-shared-pkg-config testdata
    glslangValidator spirv-remap HLSL glslang GenericCodeGen glslang-default-resource-limits
    MachineIndependent OGLCompiler OSDependent SPIRV SPVRemapper spirv-tools-vimsyntax
    SPIRV-Tools-link SPIRV-Tools-lint SPIRV-Tools-opt SPIRV-Tools-reduce SPIRV-Tools-shared
    SPIRV-Tools-static spirv-tools-build-version spirv-tools-header-DebugInfo spirv-tools-header-NonSemanticShaderDebugInfo100
    spirv-tools-header-OpenCLDebugInfo100 spv-tools-cldi100 spv-tools-clspvreflection spv-tools-debuginfo
    spv-tools-shdi100 spv-tools-spv-amd-gs spv-tools-spv-amd-sb spv-tools-spv-amd-sevp spv-tools-spv-amd-stm
    PROPERTIES FOLDER Dependencies)

set_target_properties(add-copyright update_mappings build-version core_tables 
    enum_string_mapping extinst_tables glad-generate-files glslc glslc_exe
    install-headers shaderc_combined_genfile shaderc_combined-pkg-config
    shaderc_shared shaderc_static-pkg-config shaderc_util shaderc-pkg-config
    spirv-tools-pkg-config spirv-tools-shared-pkg-config testdata
    glslangValidator spirv-remap HLSL glslang GenericCodeGen glslang-default-resource-limits
    MachineIndependent OGLCompiler OSDependent SPIRV SPVRemapper spirv-tools-vimsyntax
    SPIRV-Tools-link SPIRV-Tools-lint SPIRV-Tools-opt SPIRV-Tools-reduce SPIRV-Tools-shared
    SPIRV-Tools-static spirv-tools-build-version spirv-tools-header-DebugInfo spirv-tools-header-NonSemanticShaderDebugInfo100
    spirv-tools-header-OpenCLDebugInfo100 spv-tools-cldi100 spv-tools-clspvreflection spv-tools-debuginfo
    spv-tools-shdi100 spv-tools-spv-amd-gs spv-tools-spv-amd-sb spv-tools-spv-amd-sevp spv-tools-spv-amd-stm
    PROPERTIES EXCLUDE_FROM_ALL True)

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)
