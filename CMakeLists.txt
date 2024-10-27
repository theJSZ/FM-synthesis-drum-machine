cmake_minimum_required(VERSION 3.10)
project(mega_fm)

# Set C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the STK headers
include_directories(${CMAKE_SOURCE_DIR}/../stk/include)

# Add your source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/audiothread.cpp
    src/fmosc.cpp
    src/sequencer.cpp
    src/eightVoices.cpp
    src/pattern.cpp
    #src/clickdetector.cpp
    # Your project source files
    # Add more source files here if needed
)

set(CMAKE_AUTOMOC ON)




# Add STK source files to your project
file(GLOB STK_SOURCES ${CMAKE_SOURCE_DIR}/../stk/src/*.cpp)

# Add executable for your project
add_executable(mega_fm ${SOURCES} ${STK_SOURCES})


##### Define the audio API for STK
#### target_compile_definitions(mega_fm PRIVATE __LINUX_ALSA__)

# Find the Qt libraries
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

# Link SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Platform-specific settings
if (WIN32)
# Define Windows-specific audio API (STK supports DirectSound and WASAPI on Windows)
target_compile_definitions(mega_fm PRIVATE __WINDOWS_DS__)  # or __WINDOWS_WASAPI__

# Link Windows-specific libraries
target_link_libraries(mega_fm PRIVATE Qt5::Core Qt5::Widgets dsound pthread)
else()
# Define the audio API for Linux
target_compile_definitions(mega_fm PRIVATE __LINUX_ALSA__)

# Link the ALSA library for Linux
target_link_libraries(mega_fm PRIVATE Qt5::Core Qt5::Widgets asound pthread ${SDL2_LIBRARIES})
endif()

# Link the ALSA library
# find_package(ASound REQUIRED)

# target_link_libraries(stk_synth PRIVATE asound)
target_link_libraries(mega_fm PRIVATE Qt5::Core Qt5::Widgets asound pthread)  # Link with pthread and ALSA


# Include Qt headers
include_directories(${Qt5_INCLUDE_DIRS})

# Link Qt libraries
# target_link_libraries(stk_synth Qt5::Core Qt5::Widgets)

# Link any necessary libraries (if STK has them)
# You can specify more libraries here as needed

qt5_add_resources(RESOURCES src/mega_fm.qrc)
target_sources(mega_fm PRIVATE ${RESOURCES})
