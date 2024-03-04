cmake_minimum_required(VERSION 3.10)

project(Trail)

add_executable(trial
    trail.cpp
)

target_include_directories(trial
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(trial
    PRIVATE ${SYSTEMC_LIBRARY}
)
