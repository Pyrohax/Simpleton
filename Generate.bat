mkdir Build
cd Build
cmake -DGLFW_USE_HYBRID_HPG=ON -Wno-dev -DLIBRARY_SUFFIX="" -G "Visual Studio 16 2019" -Ax64 ..
pause