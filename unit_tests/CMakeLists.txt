set(NAME unit_tests)

add_executable(${NAME})

target_sources(${NAME} PRIVATE
        src/test.cpp
        )

target_link_libraries(${NAME} PRIVATE
        qemu_startup
        gmock_main
        )

target_link_options(${NAME} PRIVATE
        LINKER:-T${CMAKE_CURRENT_SOURCE_DIR}/link.ld
        -specs=nano.specs
        -specs=rdimon.specs
        )

set_target_properties(${NAME} PROPERTIES LINK_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/link.ld
        )