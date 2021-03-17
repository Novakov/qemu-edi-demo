set(NAME app_qemu)

add_executable(${NAME})

target_sources(${NAME} PRIVATE
        src/bootstrap.cpp
        )

target_link_libraries(${NAME} PRIVATE
        app
        qemu_startup
        edi
        )

target_link_options(${NAME} PRIVATE
        LINKER:-T${CMAKE_CURRENT_SOURCE_DIR}/link.ld
        -specs=nano.specs
        -specs=rdimon.specs
        )

set_target_properties(${NAME} PROPERTIES LINK_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/link.ld
        )