cmake_minimum_required(VERSION 3.10)
project(Kepler)

add_subdirectory(
    ../third_party/eigen
    ${CMAKE_BINARY_DIR}/eigen
)

add_library(KeplerConversions STATIC
    library/cartesianToKeplerian.cpp
    library/keplerianToCartesian.cpp
)

target_compile_features(KeplerConversions PUBLIC cxx_std_17)

target_include_directories(KeplerConversions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/library
)

target_link_libraries(KeplerConversions PUBLIC Eigen3::Eigen)

add_executable(kepler main.cpp)

target_compile_features(kepler PRIVATE cxx_std_17)

target_link_libraries(kepler PRIVATE KeplerConversions)