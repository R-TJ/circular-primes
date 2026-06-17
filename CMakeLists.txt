cmake_minimum_required(VERSION 3.20)

project(circularprimes LANGUAGES CXX)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS multiprecision)

add_executable(${PROJECT_NAME} primes.cxx)

target_link_libraries(${PROJECT_NAME} Boost::multiprecision)

target_compile_options(${PROJECT_NAME} PRIVATE
    -O3
    -march=native
    -mtune=native
    -flto
    -ffast-math
    -funroll-loops
    -fomit-frame-pointer
    -fstrict-aliasing
    -DNDEBUG
)

target_link_options(${PROJECT_NAME} PRIVATE
    -flto
)
