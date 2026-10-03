cmake_minimum_required(VERSION 3.10)
project(Celestial)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third_party/eigen)

add_executable(kepelem kepelem.cpp)
target_link_libraries(kepelem Eigen3::Eigen)