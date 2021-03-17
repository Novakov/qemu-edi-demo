set(CMAKE_EXECUTABLE_SUFFIX .elf)

# (embedded) targets without operating system usually don't support shared libraries
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)

# ensure that there are no rogue compiler options from environment
set(CMAKE_C_FLAGS "" CACHE STRING "" )
set(CMAKE_C_FLAGS_DEBUG "" CACHE STRING "")
set(CMAKE_C_FLAGS_RELEASE "" CACHE STRING "")

set(CMAKE_CXX_FLAGS "" CACHE STRING "")
set(CMAKE_CXX_FLAGS_DEBUG "" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "" CACHE STRING "")

set(CMAKE_ASM_FLAGS "" CACHE STRING "")
set(CMAKE_ASM_FLAGS_DEBUG "" CACHE STRING "")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE STRING "")

set(CMAKE_ASM_SOURCE_SUFFIX .s)