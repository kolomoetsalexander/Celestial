cmake_minimum_required(VERSION 3.15)

project(Kepler LANGUAGES CXX)

add_subdirectory(
    ../third_party/eigen
    ${CMAKE_BINARY_DIR}/eigen
)

add_subdirectory(library)

add_executable(kepler main.cpp)

target_compile_features(kepler PRIVATE cxx_std_17)

target_link_libraries(kepler PRIVATE
    KeplerConversions
)

option(BUILD_PYTHON_BINDINGS "Build Python bindings" OFF)

if(BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()
