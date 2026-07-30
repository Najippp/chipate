cmake_minimum_required(VERSION 3.16)

# Take all .cpp file in current directory
file(GLOB ALL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Add all .cpp file as a library
add_library(mylib STATIC ${ALL_SOURCES})

# Link target include files
target_include_directories(mylib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link mylib to SDL3
target_link_libraries(mylib PUBLIC SDL3::SDL3)