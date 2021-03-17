set(NAME app_hw)

add_executable(${NAME})

target_sources(${NAME} PRIVATE
        src/bootstrap.cpp
        )

target_link_libraries(${NAME} PRIVATE
        app
        cm3
        )

target_link_options(${NAME} PRIVATE
        LINKER:-T${CMAKE_CURRENT_SOURCE_DIR}/link.ld
        -specs=nano.specs
        -specs=nosys.specs
        -nostartfiles
        )

set_target_properties(${NAME} PROPERTIES LINK_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/link.ld
        )

add_custom_target(${NAME}.flash
        COMMAND
        ${OPENOCD}
        -f interface/stlink.cfg
        -f target/stm32f1x.cfg
        -c "program $<TARGET_FILE:${NAME}> verify reset exit"
        DEPENDS
        ${ELF_FILE}
        USES_TERMINAL
        )