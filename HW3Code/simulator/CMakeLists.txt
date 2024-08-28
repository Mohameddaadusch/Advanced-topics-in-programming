# Set the C++ standard to C++17

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Add the executable for the simulator

add_executable(myrobot 

    MySimulator.cpp 

    AlgorithmRegistrar.cpp

    ${CMAKE_SOURCE_DIR}/House/House.cpp

    ${CMAKE_SOURCE_DIR}/score/score.cpp

    ${CMAKE_SOURCE_DIR}/vacuum/vacuum.cpp

)



# Include directories

target_include_directories(myrobot PUBLIC 

    ${CMAKE_SOURCE_DIR}/common

    ${CMAKE_SOURCE_DIR}/algorithm

    ${CMAKE_SOURCE_DIR}/House

    ${CMAKE_SOURCE_DIR}/score

    ${CMAKE_SOURCE_DIR}/vacuum

)



# Link dynamic libraries

target_link_options(myrobot PUBLIC "-rdynamic")

target_link_libraries(myrobot PUBLIC dl algorithm1 algorithm2 pthread)



# Link with stdc++fs if using GCC and needed

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    target_link_libraries(myrobot PUBLIC stdc++fs)

endif()

