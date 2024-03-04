add_executable(nand_exercise2
    main.cpp
)

target_include_directories(nand_exercise2
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(nand_exercise2
    PRIVATE ${SYSTEMC_LIBRARY}
)
