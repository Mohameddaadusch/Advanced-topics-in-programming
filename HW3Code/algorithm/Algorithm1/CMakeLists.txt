# CMake for Algorithm1
add_library(algorithm1 SHARED Algorithm_A_318978152_212001192.cpp)

# Set the output directory for the shared library to be in the build/algorithm directory
set_target_properties(algorithm1 PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/algorithm
)

# Include directories
target_include_directories(algorithm1 PUBLIC 
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/algorithm
    ${CMAKE_SOURCE_DIR}/House
    ${CMAKE_SOURCE_DIR}/score
    ${CMAKE_SOURCE_DIR}/vacuum
)
