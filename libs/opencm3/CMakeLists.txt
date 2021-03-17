include(FetchContent)

FetchContent_Declare(
        opencm3
        GIT_REPOSITORY https://github.com/libopencm3/libopencm3.git
        GIT_TAG 0fd4f74ee301af5de4e9b036f391bf17c5a52f02
)

FetchContent_GetProperties(opencm3)
if (NOT opencm3_POPULATED)
    FetchContent_Populate(opencm3)
endif ()

set(OPENCM3_ROOT ${opencm3_SOURCE_DIR} CACHE INTERNAL "")
set(LD_SCRIPTS ${CMAKE_CURRENT_BINARY_DIR}/ld CACHE INTERNAL "")

file(MAKE_DIRECTORY ${LD_SCRIPTS})

set(DEVICE stm32f103c8t8)

set(GENLINK ${OPENCM3_ROOT}/scripts/genlink.py)
set(LD_SRC ${OPENCM3_ROOT}/ld/linker.ld.S)
set(DEVICES_DATA ${OPENCM3_ROOT}/ld/devices.data)

execute_process(
        COMMAND ${Python3_EXECUTABLE} ${GENLINK} ${DEVICES_DATA} ${DEVICE} DEFS
        OUTPUT_VARIABLE LD_DEFS
)

string(REPLACE " " ";" LD_DEFS_LIST ${LD_DEFS})

execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} ${LD_DEFS_LIST} ${LD_SRC} -P -E
        OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/ld/${DEVICE}.ld
)

add_library(cm3 STATIC
        ${OPENCM3_ROOT}/lib/cm3/vector.c
        ${OPENCM3_ROOT}/include/libopencm3/stm32f1/nvic.h

        ${OPENCM3_ROOT}/lib/cm3/nvic.c
        ${OPENCM3_ROOT}/lib/cm3/dwt.c

        ${OPENCM3_ROOT}/lib/stm32/common/rcc_common_all.c
        ${OPENCM3_ROOT}/lib/stm32/f1/rcc.c

        ${OPENCM3_ROOT}/include/libopencm3/stm32/gpio.h
        ${OPENCM3_ROOT}/lib/stm32/common/gpio_common_all.c
        ${OPENCM3_ROOT}/lib/stm32/f1/gpio.c

        ${OPENCM3_ROOT}/lib/stm32/common/exti_common_all.c

        ${OPENCM3_ROOT}/lib/stm32/common/flash_common_all.c
        ${OPENCM3_ROOT}/lib/stm32/f1/flash.c

        ${OPENCM3_ROOT}/lib/stm32/common/usart_common_all.c
        ${OPENCM3_ROOT}/lib/stm32/common/usart_common_f124.c

        ${OPENCM3_ROOT}/include/libopencm3/cm3/dwt.h
        ${OPENCM3_ROOT}/include/libopencm3/cm3/common.h
        ${OPENCM3_ROOT}/include/libopencm3/cm3/memorymap.h
        )

target_include_directories(cm3
        PUBLIC
        ${OPENCM3_ROOT}/include
        )

target_compile_definitions(cm3 PUBLIC
        STM32F1
        STM32F103C8T8
        )

set(IRQ_IN_FILE include/libopencm3/stm32/f1/irq.json)
add_custom_command(
        OUTPUT ${OPENCM3_ROOT}/include/libopencm3/stm32f1/nvic.h
        COMMAND ${Python3_EXECUTABLE} ${OPENCM3_ROOT}/scripts/irq2nvic_h ./${IRQ_IN_FILE}
        WORKING_DIRECTORY ${OPENCM3_ROOT}
)