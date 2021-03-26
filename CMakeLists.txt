cmake_minimum_required(VERSION 3.15)

set(LOCAL_CFG "" CACHE FILEPATH "Path to local config")

if (NOT LOCAL_CFG)
    message(FATAL_ERROR "LOCAL_CFG variable not set. Use -DLOCAL_CFG=<file> to set local config. See local-example.cmake for available options")
endif ()
include(${LOCAL_CFG})

include(cmake/toolchain.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

project(QemuDemo C CXX ASM${DIALECT})

set(CMAKE_CONFIGURATION_TYPES Debug;Release)


add_subdirectory(app)
add_subdirectory(libs)
add_subdirectory(unit_tests)