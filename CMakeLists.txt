cmake_minimum_required(VERSION 3.10)
project(mega_fm)

# Set C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the STK headers
include_directories(${CMAKE_SOURCE_DIR}/src/stk/include)
# Include Qt headers
include_directories(${Qt5_INCLUDE_DIRS})

# Add source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/audiothread.cpp
    src/fmosc.cpp
    src/sequencer.cpp
    src/eightVoices.cpp
    src/pattern.cpp
    #src/clickdetector.cpp
)

set(CMAKE_AUTOMOC ON)

# Add STK source files
set(STK_SOURCES
    src/stk/src/RtAudio.cpp
    src/stk/src/SineWave.cpp
    src/stk/src/FreeVerb.cpp
    src/stk/src/Delay.cpp
    src/stk/src/OnePole.cpp
    src/stk/src/ADSR.cpp
    src/stk/src/Stk.cpp
)

# file(GLOB STK_SOURCES ${CMAKE_SOURCE_DIR}/src/stk/src/*.cpp)
add_executable(mega_fm ${SOURCES} ${STK_SOURCES})

# Find the Qt libraries
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

# Define the audio API for Linux
target_compile_definitions(mega_fm PRIVATE __LINUX_ALSA__)

# target_link_libraries(stk_synth PRIVATE asound)
target_link_libraries(mega_fm PRIVATE Qt5::Core Qt5::Widgets asound pthread)  # Link with pthread and ALSA

