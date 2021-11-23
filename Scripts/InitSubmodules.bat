@echo on
echo "Initializing submodules (1/5)"
:: git submodule update --init --recursive
mkdir Build
echo "Generating GLFW (2/5)"
cd Build
mkdir GLFW
cd ..
cmake -S Dependencies/glfw -B Build/GLFW
echo "Building GLFW (3/5)"
cmake --build Build/GLFW --target glfw --config Debug
echo "Generating GLAD (4/5)"
cd Build
mkdir GLAD
cd ..
cmake -S Dependencies/glad -B Build/GLAD
echo "Building GLAD (5/5)"
cmake --build Build/GLAD --target glad --config Debug