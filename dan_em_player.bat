cmake -BBuild/WebGL -H. -DURHO3D_HOME="C:/Dev/Urho3D/Build/WebGL" ^
-DURHO3D_PACKAGING=0 -DEMSCRIPTEN=1 -DWEB=1 -DEMSCRIPTEN_ALLOW_MEMORY_GROWTH=1 ^
-G "MinGW Makefiles" -DPLAYER_ONLY=1 -DCMAKE_BUILD_TYPE=RELEASE ^
-DCMAKE_TOOLCHAIN_FILE="CMake/Toolchains/emscripten.toolchain.cmake" ^
-DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX="./"