# PhAse 1: Data Loading and Search Engine

cmake_minimum_required(VERSION 3.10)
project(MotorVehicleCollisions)

set(CMAKE_CXX_STANDARD 17)

add_executable(collision_analysis src_phase1/main.cpp src_phase1/DataLoader.cpp src_phase1/SearchEngine.cpp)

# PhAse 2: Data Loading and Search Engine

# cmake_minimum_required(VERSION 3.10)
# project(MotorVehicleCollisions)

# set(CMAKE_CXX_STANDARD 17)

# Enable OpenMP
# find_package(OpenMP REQUIRED)
# add_executable(collision_analysis src_phase2/main.cpp src_phase2/DataLoader.cpp src_phase2/SearchEngine.cpp)
# target_link_libraries(collision_analysis OpenMP::OpenMP_CXX)