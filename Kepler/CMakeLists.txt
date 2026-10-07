cmake_minimum_required(VERSION 3.10)
project(Kepler)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(
    ../third_party/eigen
    ${CMAKE_BINARY_DIR}/eigen
)
add_executable(kepler main.cpp)
target_link_libraries(kepler Eigen3::Eigen)