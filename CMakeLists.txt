cmake_minimum_required(VERSION 3.15)
project(PitchRecorder)

set(CMAKE_CXX_STANDARD 17)

set(portaudio_DIR "$ENV{HOME}/vcpkg/installed/arm64-osx/share/portaudio")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(fmt CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
find_package(aubio REQUIRED)

add_executable(PitchRecorder module/main.cpp)

target_link_libraries(PitchRecorder PRIVATE fmt::fmt)
target_link_libraries(PitchRecorder PRIVATE portaudio_static)
target_link_libraries(PitchRecorder PRIVATE aubio::aubio)
target_include_directories(PitchRecorder PRIVATE "$ENV{HOME}/vcpkg/installed/arm64-osx/include")