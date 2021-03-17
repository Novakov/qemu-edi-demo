set(NAME qemu_startup)

add_library(${NAME} STATIC)

target_sources(${NAME} PRIVATE
        src/interrupt.S
        src/interrupt.c
        src/startup_ARMCM3.S
        src/startup.c

        private/arm.h
        private/swi.h

        include/ARMCM3.h
        include/cmsis_compiler.h
        include/cmsis_gcc.h
        include/cmsis_version.h
        include/core_cm3.h
        include/mpu_armv7.h
        )

target_include_directories(${NAME}
        PRIVATE private
        PUBLIC include
        )

target_compile_definitions(${NAME} PRIVATE
        __START=_startup
        __STARTUP_CLEAR_BSS
        GENERATE_ALIASED_INTERRUPTS
        )