cmake_minimum_required(VERSION 3.10)

project(Prep)

# Remember only one sc_main() function should exist.
# Choose "nand_main.cpp" here to test your NAND implementation.
# Choose "exor_main.cpp" here to test your XOR implementation.

add_executable(prep
    main.cpp
    #exor_main.cpp
)

target_include_directories(prep
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(prep
    PRIVATE ${SYSTEMC_LIBRARY}
)
