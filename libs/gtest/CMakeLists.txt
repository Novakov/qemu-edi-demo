# Prevent GoogleTest from overriding our compiler/linker options when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)

set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/kplabs-pl/googletest.git
        GIT_TAG 15122782b24c4f931bfe840ce8295ae4b1d7d67e
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

    file(GLOB_RECURSE gtest_includes LIST_DIRECTORIES false ${googletest_SOURCE_DIR}/googletest/include/gtest/*.h)

    target_sources(gtest
            PUBLIC
            ${gtest_includes}
            )

    file(GLOB_RECURSE gmock_includes LIST_DIRECTORIES false ${googletest_SOURCE_DIR}/googlemock/include/gmock/*.h)

    target_sources(gmock
            PUBLIC
            ${gmock_includes}
            )
endif ()


function(update_target target)
    target_compile_features(${target} PUBLIC cxx_std_17)
    if (CMAKE_CROSSCOMPILING AND ((CMAKE_SYSTEM_NAME STREQUAL "Generic") OR (CMAKE_SYSTEM_NAME STREQUAL "Embedded")))
        target_compile_definitions(${target}
                PUBLIC
                _POSIX_C_SOURCE=200809L
                GTEST_HAS_POSIX_RE=0
                GTEST_HAS_STREAM_REDIRECTION=0
                GTEST_HAS_CLONE=0
                GTEST_HAS_DEATH_TEST=0
                PRIVATE
                GTEST_MOCK_FS=1
                )
    endif ()
endfunction(update_target)

update_target(gtest)
update_target(gmock)
update_target(gtest_main)
update_target(gmock_main)