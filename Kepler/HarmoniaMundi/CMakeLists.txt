add_library(KeplerConversions STATIC
    cartesianToKeplerian.cpp
    keplerianToCartesian.cpp
    trueToEccentric.cpp
    eccentricToTrue.cpp
    solveKeplerEquation.cpp
)

target_compile_features(KeplerConversions PUBLIC cxx_std_17)

target_include_directories(KeplerConversions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(KeplerConversions PUBLIC
    Eigen3::Eigen
)

set_target_properties(KeplerConversions PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
