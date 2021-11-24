# Simpleton
## Goal
Our goal is to design a platform-agnostic and multi-threaded 3D game engine by focusing on architecture, modularity and tools.
The game engine should be easy to use, including setup and contribution, and support multiple grahpics APIs and file formats.

## Setup
### Windows
It's recommended to start by running `SetupDependencies.bat` to make sure that you have the right Git submodules and libraries. You'll see a `Dependencies` folder once that process is done. With the prerequisites you can use `GenerateVS2019.bat` or `GenerateVS2022.bat` to generate the Visual Studio Solution that will be put in `Generated`. `LaunchVS.bat` can be used to launch the Visual Studio Solution. The binaries and associated build files are put in `Binaries`.
### Prerequisites
Name | Description
------------ | -------------
[CMake](https://cmake.org/) | 3.7.0+
[Python](https://www.python.org/) | Python 2.8+
[Vulkan SDK](https://vulkan.lunarg.com/) | 1.2.162.0

## Dependencies
Name | Description | License
------------ | ------------- | -------------
[GLAD](https://github.com/Dav1dde/glad) | Multi-Language GL Loader-Generator | [MIT](https://github.com/Dav1dde/glad/blob/master/LICENSE)
[GLFW](https://github.com/glfw/glfw) | Multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input | [ZLIB](https://github.com/glfw/glfw/blob/master/LICENSE.md)
[GLM](https://github.com/g-truc/glm) | OpenGL math library | [MIT](https://github.com/g-truc/glm/blob/master/manual.md#section0)
[ImGUI](https://github.com/ocornut/imgui) | Bloat-free Graphical User Interface | [MIT](https://github.com/ocornut/imgui/blob/master/LICENSE.txt)
[RapidJSON](https://github.com/Tencent/rapidjson) | A fast JSON parser/generator for C++ | [MIT](https://github.com/Tencent/rapidjson/blob/master/license.txt)
[STB](https://github.com/nothings/stb) | Collection of single-file libraries | [MIT](https://github.com/nothings/stb/blob/master/LICENSE)
[STDUUID](https://github.com/mariusbancila/stduuid) | A C++17 cross-platform implementation for UUIDs | [MIT](https://github.com/mariusbancila/stduuid/blob/master/LICENSE)
[TinyGLTF](https://github.com/syoyo/tinygltf) | Header only C++11 tiny glTF 2.0 library | [MIT](https://github.com/syoyo/tinygltf/blob/master/LICENSE)
[TinyObjLoader](https://github.com/syoyo/tinyobjloader) | Tiny but powerful single file wavefront obj loader | [MIT](https://github.com/syoyo/tinyobjloader/blob/master/LICENSE)

## Bugs, issues and suggestions
Feel free to open issues in case you encounter bugs, want to make suggestions or need help. 
