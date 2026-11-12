find_package(Python 3.10 REQUIRED
    COMPONENTS Interpreter Development.Module
)

execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_VARIABLE nanobind_ROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    COMMAND_ERROR_IS_FATAL ANY
)

find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(celestial
    bind.cpp
)

target_link_libraries(celestial PRIVATE
    KeplerConversions
)
