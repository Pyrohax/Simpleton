echo "Initializing submodules (1/6)"
git submodule update --init --recursive
mkdir Dependencies
echo "Generating GLFW (2/6)"
cd Dependencies
mkdir GLFW
cd ..
cmake -DGLFW_INSTALL=ON -S Submodules/glfw -B Dependencies/GLFW
echo "Building GLFW (3/6)"
cmake --build Dependencies/GLFW --target glfw --config Debug
echo "Generating GLAD (4/6)"
cd Dependencies
mkdir GLAD
cd ..
cmake -S Submodules/glad -B Dependencies/GLAD
echo "Building GLAD (5/6)"
cmake --build Dependencies/GLAD --target glad --config Debug
echo "Generating Shaderc (6/6)"
