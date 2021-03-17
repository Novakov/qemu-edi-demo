include(FetchContent)

FetchContent_Declare(
        edi
        GIT_REPOSITORY https://github.com/kplabs-pl/edi.git
        GIT_TAG 915fc0d3346bb372464f1d0947954438576289b6
)

FetchContent_GetProperties(edi)
if (NOT edi_POPULATED)
    FetchContent_Populate(edi)
    add_subdirectory(${edi_SOURCE_DIR} ${edi_BINARY_DIR})
endif ()