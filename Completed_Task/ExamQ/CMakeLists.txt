cmake_minimum_required(VERSION 3.10)

project(ExamQ)

add_executable(examq
    #and.cpp
    #or.cpp
    main.cpp
)

target_include_directories(examq
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(examq
    PRIVATE ${SYSTEMC_LIBRARY}
)
