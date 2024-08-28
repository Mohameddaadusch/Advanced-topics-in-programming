cmake_minimum_required(VERSION 3.13)
project(simulator_example VERSION 1.0 LANGUAGES CXX)

# Add subdirectories for the algorithms and simulator
add_subdirectory(algorithm/Algorithm1)
add_subdirectory(algorithm/Algorithm2)
add_subdirectory(simulator)
