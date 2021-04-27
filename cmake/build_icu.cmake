include(ExternalProject)

find_program(MAKE_PROGRAM make)

set(ICU_PATH ${CMAKE_CURRENT_BINARY_DIR}/icu)

set(ICU_INCLUDE_DIRS ${ICU_PATH}/include)

foreach(ICU_BASE_NAME data i18n io tu uc)
    set(ICU_SHARED_LIB ${ICU_PATH}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}icu${ICU_BASE_NAME}.so)
    set(ICU_STATIC_LIB ${ICU_PATH}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}icu${ICU_BASE_NAME}.a)

    if (ICU_STATIC)
        list(APPEND ICU_LIBRARIES ${ICU_STATIC_LIB})
    else()
        list(APPEND ICU_LIBRARIES ${ICU_SHARED_LIB})
    endif()
endforeach()

ExternalProject_Add(
    icu
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/icu/icu4c
    BINARY_DIR ${ICU_PATH}
    DOWNLOAD_DIR ""
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND
        <SOURCE_DIR>/source/configure
            --enable-static
            --prefix=${CMAKE_CURRENT_BINARY_DIR}/icu
            --libdir=${CMAKE_CURRENT_BINARY_DIR}/icu/lib/
    BUILD_COMMAND ${MAKE_PROGRAM} -j 4
    BUILD_BYPRODUCTS ${ICU_LIBRARIES}
    INSTALL_COMMAND ""
)

