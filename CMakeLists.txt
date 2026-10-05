cmake_minimum_required(VERSION 3.16)
project(SignalCodec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

# Core logic (no graphics dependency)
add_library(codec_core
    src/DataGenerator.cpp
    src/analog/Analog.cpp
    src/encoders/Encoder.cpp
)
target_include_directories(codec_core PUBLIC src)

# Plotting & Image Decoding (SFML 3)
add_library(codec_gfx
    src/graphics/Plotter.cpp
    src/graphics/ImageDecoder.cpp
)
target_link_libraries(codec_gfx PUBLIC codec_core SFML::Graphics)

add_executable(signal_codec src/main.cpp)
target_link_libraries(signal_codec PRIVATE codec_core codec_gfx)
