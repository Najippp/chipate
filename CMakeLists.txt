cmake_minimum_required(VERSION 3.16)
project(chipate)

set(CMAKE_CXX_STANDARD 17)

# Include FetchContent module
include(FetchContent)

# Declare SDL3 repository
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        main # Or use a specific release tag, e.g., 'release-3.2.0'
)

# Make SDL3 available to your CMake script
FetchContent_MakeAvailable(SDL3)

add_subdirectory(src)

# Add executable
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC mylib)