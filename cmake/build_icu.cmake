include(ExternalProject)

find_program(MAKE_PROGRAM make)

set(ICU_PATH ${CMAKE_CURRENT_BINARY_DIR}/icu)

set(ICU_INCLUDE_DIRS ${ICU_PATH}/include)
set(ICU_LIBRARIES "")

foreach(ICU_BASE_NAME i18n io tu uc data)
    set(ICU_SHARED_LIB ${ICU_PATH}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}icu${ICU_BASE_NAME}.so)
    set(ICU_STATIC_LIB ${ICU_PATH}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}icu${ICU_BASE_NAME}.a)

    if (ICU_STATIC)
        list(APPEND ICU_LIBRARIES "${ICU_STATIC_LIB}")
    else()
        list(APPEND ICU_LIBRARIES "${ICU_SHARED_LIB}")
    endif()
endforeach()

set(PASS_CC ${CMAKE_COMMAND} -E env
        CC=${CMAKE_C_FLAGS}
        CXX=${CMAKE_CXX_FLAGS}
        CFLAGS=${CMAKE_C_FLAGS}
        CXXFLAGS=${CMAKE_CXX_FLAGS}
        LDFLAGS=${CMAKE_MODULE_LINKER_FLAGS}
)

ExternalProject_Add(
    icu_make
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/icu/icu4c
    BINARY_DIR ${ICU_PATH}
    DOWNLOAD_DIR ""
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND
        ${PASS_CC} <SOURCE_DIR>/source/configure
            --enable-static
            --disable-renaming
            $<$<CONFIG:Debug>:--enable-debug>
            --prefix=${CMAKE_CURRENT_BINARY_DIR}/icu
            --libdir=${CMAKE_CURRENT_BINARY_DIR}/icu/lib/
    BUILD_COMMAND ${PASS_CC} ${MAKE_PROGRAM} -j 6
    INSTALL_COMMAND ""
)
# INSTALL_COMMAND ${MAKE_PROGRAM} install
file(MAKE_DIRECTORY ${ICU_INCLUDE_DIRS}) # hack for INTERFACE_INCLUDE_DIRECTORIES

add_library(icu::icu INTERFACE IMPORTED)
set_property(TARGET icu::icu PROPERTY INTERFACE_LINK_LIBRARIES "${ICU_LIBRARIES}")
set_property(TARGET icu::icu PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${ICU_INCLUDE_DIRS}")
add_dependencies(icu::icu icu_make)
