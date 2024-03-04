cmake_minimum_required(VERSION 3.10)

project(XOR)

add_executable(XOR
    xor.cpp
)

target_include_directories(XOR
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(XOR
    PRIVATE ${SYSTEMC_LIBRARY}
)
