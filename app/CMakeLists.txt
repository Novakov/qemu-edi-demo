add_subdirectory(hw_runner)
add_subdirectory(qemu_runner)

set(NAME app)

add_library(${NAME} STATIC)

target_include_directories(${NAME} PUBLIC include)

target_sources(${NAME} PRIVATE
        src/main.cpp
        )