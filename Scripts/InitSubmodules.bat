@echo on
set currentDirectory=%cd%
echo "Initializing submodules (1/7)"
git submodule update --init --recursive
mkdir Dependencies
echo "Generating GLFW (2/7)"
cd Dependencies
mkdir GLFW
cd ..
cmake -DGLFW_INSTALL=ON -S Submodules/glfw -B Dependencies/GLFW
echo "Building GLFW (3/7)"
cmake --build Dependencies/GLFW --target glfw --config Debug
echo "Generating GLAD (4/7)"
cd Dependencies
mkdir GLAD
cd ..
cmake -S Submodules/glad -B Dependencies/GLAD
echo "Building GLAD (5/7)"
cmake --build Dependencies/GLAD --target glad --config Debug
echo "Generating Shaderc (6/7)"
cd Dependencies
mkdir Shaderc
cd ..
cmake -DSHADERC_SKIP_TESTS:BOOL=ON -DSHADERC_SKIP_EXAMPLES:BOOL=ON -DSHADERC_SKIP_COPYRIGHT_CHECK:BOOL=ON -DSHADERC_ENABLE_WGSL_OUTPUT:BOOL=OFF -DENABLE_HLSL:BOOL=ON -DENABLE_CTEST:BOOL=OFF -DENABLE_GLSLANG_WEBMIN:BOOL=OFF -DSPIRV_HEADERS_SKIP_EXAMPLES:BOOL=ON -DSPIRV_BUILD_FUZZER:BOOL=OFF -DSPIRV_BUILD_LIBFUZZER_TARGETS:BOOL=OFF -DSPIRV_SKIP_TESTS:BOOL=ON -DSPIRV_BUILD_COMPRESSION:BOOL=OFF -DSPIRV_COLOR_TERMINAL:BOOL=OFF -DSPIRV_SKIP_EXECUTABLES:BOOL=ON -DBUILD_TESTING:BOOL=OFF -DSHADERC_SPIRV_TOOLS_DIR="%currentDirectory%/Submodules/SPIRVTools" -DSHADERC_SPIRV_HEADERS_DIR="%currentDirectory%/Submodules/SPIRVHeaders" -DSHADERC_GLSLANG_DIR="%currentDirectory%/Submodules/GLSLLang" -DSHADERC_DIR="%currentDirectory%/Submodules/Shaderc" -S Submodules/shaderc -B Dependencies/Shaderc
echo "Building Shaderc (7/7)"
cmake --build Dependencies/Shaderc --target shaderc --config Debug
