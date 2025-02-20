cmake_minimum_required(VERSION 3.10)
project(MotorVehicleCollisions)

set(CMAKE_CXX_STANDARD 17)

# Phase 1.1
#add_executable(test src_phase1.1/Main.cpp src_phase1.1/CrashData.cpp)

# Phase 1.2
#add_executable(test src_phase1.2/Main.cpp src_phase1.2/CrashData.cpp)

# Enable OpenMP
find_package(OpenMP REQUIRED)
SET(OPENMP_CXX_FLAGS "-O3 -fopenmp")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}" )

# Phase 2
add_executable(test src_phase2.3/Main.cpp src_phase2.3/CrashData.cpp)
target_link_libraries(test OpenMP::OpenMP_CXX)