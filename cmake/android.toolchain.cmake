set(ANDROID_ABI arm64-v8a)
set(ANDROID_PLATFORM android-30)
set(ANDROID_STL c++_shared)


# Include the NDK cmake toolchain file
if(NOT DEFINED ENV{NDK_HOME})
  message(FATAL_ERROR "NDK_HOME environment variable not set")
endif()
include($ENV{NDK_HOME}/build/cmake/android.toolchain.cmake)

message(STATUS "AMENT_PREFIX_PATH : $ENV{AMENT_PREFIX_PATH}")
message(STATUS "PYTHONPATH : $ENV{PYTHONPATH}")
message(STATUS "CMAKE_FIND_ROOT_PATH : ${CMAKE_FIND_ROOT_PATH}")

############################################

# Set compile flags which are overwritter by android.toolchain.cmake
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Set the -s flag for linker to strip unneeded info (like debug info) for Release builds since the
# NDK toolchain file enables -g compiler flag even for Release builds.
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s" CACHE STRING "")
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} -s" CACHE STRING "")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -s" CACHE STRING "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)