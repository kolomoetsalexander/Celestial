cmake_minimum_required(VERSION 3.15)

project(Kepler)

add_subdirectory(
    ../third_party/eigen
    ${CMAKE_BINARY_DIR}/eigen
)

add_subdirectory(HarmoniaMundi)

option(BUILD_EXAMPLES "Build C++ examples" OFF)

if(BUILD_EXAMPLES)
    add_executable(kepler main.cpp)

    target_compile_features(kepler PRIVATE cxx_std_17)

    target_link_libraries(kepler PRIVATE KeplerConversions)
endif()

option(BUILD_PYTHON_BINDINGS "Build Python bindings" OFF)

if(BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()
