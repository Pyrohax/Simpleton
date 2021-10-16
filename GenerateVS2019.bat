mkdir Generated
cd Generated
cmake -DGLFW_USE_HYBRID_HPG:BOOL=ON -Wno-dev -G "Visual Studio 16 2019" -Ax64 ..
pause
