cmake_minimum_required(VERSION 3.10)
project(mega_fm)

# Add stk submodule
# add_subdirectory(stk)

# Include the STK headers
include_directories(${CMAKE_SOURCE_DIR}/../../stk/include)

# Add your source files
set(SOURCES
    ../main.cpp

    # Your project source files
    # Add more source files here if needed
)

set(CMAKE_AUTOMOC ON)


# Add STK source files to your project
file(GLOB STK_SOURCES ${CMAKE_SOURCE_DIR}/../../stk/src/*.cpp)

# Add executable for your project
add_executable(mega_fm ${SOURCES} ${STK_SOURCES})

# Define the audio API for STK
target_compile_definitions(mega_fm PRIVATE __LINUX_ALSA__)

# Link the ALSA library
# find_package(ASound REQUIRED)
# target_link_libraries(stk_synth PRIVATE asound)
target_link_libraries(mega_fm PRIVATE Qt5::Core Qt5::Widgets asound pthread)  # Link with pthread and ALSA

# Find the Qt libraries
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

# Include Qt headers
include_directories(${Qt5_INCLUDE_DIRS})

# Link Qt libraries
# target_link_libraries(stk_synth Qt5::Core Qt5::Widgets)

# Link any necessary libraries (if STK has them)
# You can specify more libraries here as needed
