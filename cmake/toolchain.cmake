
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_SYSTEM_NAME Embedded)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(PREFIX arm-none-eabi-)
find_program(CMAKE_C_COMPILER NAMES ${PREFIX}gcc HINTS ${ARM_TOOLCHAIN})
find_program(CMAKE_ASM_COMPILER NAMES ${PREFIX}gcc HINTS ${ARM_TOOLCHAIN})
find_program(CMAKE_CXX_COMPILER NAMES ${PREFIX}g++ HINTS ${ARM_TOOLCHAIN})
find_program(CMAKE_AR NAMES ${PREFIX}gcc-ar HINTS ${ARM_TOOLCHAIN})
find_program(CMAKE_RANLIB NAMES ${PREFIX}gcc-ranlib HINTS ${ARM_TOOLCHAIN})
find_program(CMAKE_OBJCOPY NAMES ${PREFIX}objcopy HINTS ${ARM_TOOLCHAIN})
find_program(CMAKE_OBJDUMP NAMES ${PREFIX}objdump HINTS ${ARM_TOOLCHAIN})

find_program(OPENOCD NAME openocd PATHS ${OPENOCD_DIR} ${ARM_TOOLCHAIN})

find_program(QEMU NAMES qemu-system-arm HINTS ${QEMU_DIR})

add_compile_options(
        -mcpu=cortex-m3
        -mthumb
        -ffunction-sections
        -fdata-sections
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>

        -Wall
        -Wpedantic
        $<$<CONFIG:Release>:-Werror>
        $<$<CONFIG:Release>:-flto>
        -Wno-error=deprecated-declarations

        -g
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Debug>:-ggdb3>
)

add_link_options(
        LINKER:--build-id=none
        LINKER:-gc-sections
        -g
        -mcpu=cortex-m3
        -mthumb
        $<$<CONFIG:Release>:-flto>
        -fno-exceptions
)

find_package(Python3 COMPONENTS Interpreter)