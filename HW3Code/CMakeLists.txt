cmake_minimum_required(VERSION 3.13)

project(simulator_example VERSION 1.0 LANGUAGES CXX)

add_library(algorithm2 SHARED algorithm/Algorithm2/Algo_123456789.cpp)
# Include all relevant directories in ex3_skeleton
target_include_directories(algorithm2 PUBLIC 
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/algorithm
    ${CMAKE_SOURCE_DIR}/House
    ${CMAKE_SOURCE_DIR}/score
    ${CMAKE_SOURCE_DIR}/vacuum
)

add_library(algorithm1 SHARED algorithm/Algorithm1/MyAlgorithm.cpp)
# Include all relevant directories in ex3_skeleton
target_include_directories(algorithm1 PUBLIC 
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/algorithm
    ${CMAKE_SOURCE_DIR}/House
    ${CMAKE_SOURCE_DIR}/score
    ${CMAKE_SOURCE_DIR}/vacuum
)

# Add the executable for the simulator
add_executable(main 
    simulator/MySimulator.cpp 
    simulator/AlgorithmRegistrar.cpp
    House/House.cpp
    score/score.cpp
    vacuum/vacuum.cpp
)# Include all relevant directories in ex3_skeleton
target_include_directories(algorithm1 PUBLIC 
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/algorithm
    ${CMAKE_SOURCE_DIR}/House
    ${CMAKE_SOURCE_DIR}/score
    ${CMAKE_SOURCE_DIR}/vacuum
)
target_link_options(main PUBLIC "-rdynamic")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")
target_link_libraries(main PUBLIC dl)
