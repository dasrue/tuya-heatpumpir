cmake_minimum_required(VERSION 3.10)
project(TuyaEncode)

# Automatically find all .cpp files in the current directory and store them in the 'SOURCES' variable
file(GLOB HPSOURCES "arduino-heatpumpir/*.cpp")

add_executable(tuyaenc main.cpp Arduino.cpp IRSenderVirt.cpp FastLZ/fastlz.c ${HPSOURCES})
target_include_directories(tuyaenc PUBLIC "arduino-heatpumpir")
target_include_directories(tuyaenc PUBLIC "FastLZ")
target_include_directories(tuyaenc PUBLIC ".")