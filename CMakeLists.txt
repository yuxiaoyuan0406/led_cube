# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/dennis/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(led_cube C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add your own include directories
include_directories(./hc595
    ./cube
)

# Add executable. Default name is the project name, version 0.1

add_executable(led_cube 
    led_cube.cpp 
    hc595/hc595.cpp
    cube/cube_data.cpp
    cube/cube.cpp
)

pico_set_program_name(led_cube "led_cube")
pico_set_program_version(led_cube "0.1")

pico_enable_stdio_uart(led_cube 1)
pico_enable_stdio_usb(led_cube 0)

# Add the standard library to the build
target_link_libraries(led_cube pico_stdlib)

# Add any user requested libraries
target_link_libraries(led_cube
        hardware_i2c
        hardware_spi
        pico_multicore
        )

pico_add_extra_outputs(led_cube)

