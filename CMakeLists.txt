cmake_minimum_required(VERSION 3.13.4)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS ON)
set (CMAKE_CXX_STANDARD_REQUIRED YES)

project(cplox C CXX)

add_subdirectory(src)

add_executable(${PROJECT_NAME} Lox.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE cplox_lib)