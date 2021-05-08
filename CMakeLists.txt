cmake_minimum_required(VERSION 3.9)
# cmake_policy(SET CMP0004 OLD)
cmake_policy(SET CMP0065 OLD)
project(bench-timetamp)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# enable_testing()
# find_package(GTest REQUIRED)
# include(GoogleTest)
find_package(benchmark REQUIRED)

# sudo apt-get install googletest
set(GoogleTest_ROOT /usr/src/googletest/googletest)
add_subdirectory(${GoogleTest_ROOT}
                ${CMAKE_CURRENT_BINARY_DIR}/googletest
                EXCLUDE_FROM_ALL)
add_subdirectory(c-dt)
add_subdirectory(cctz)
add_subdirectory(re2c)

# set(ICU_STATIC 1)

include(build_icu)

add_custom_command(
OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/parse-date.cpp
COMMAND
    $<TARGET_FILE:re2c> -W -g
        -o ${CMAKE_CURRENT_BINARY_DIR}/parse-date.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/common/parse-date.re
DEPENDS
    re2c ${CMAKE_CURRENT_SOURCE_DIR}/common/parse-date.re
VERBATIM
)

add_executable(tests
    tests/test-cdt.cpp
    tests/test-cctz.cpp
    tests/test-icudt.cpp
    tests/test-re2c.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/parse-date.cpp
)

#target_compile_definitions(tests PUBLIC 
#    U_DISABLE_RENAMING=1
#)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/unicode
    ${CMAKE_CURRENT_SOURCE_DIR}/c-dt/
)
target_link_libraries(tests gtest_main cdt cctz::cctz icu::icu dl)

add_executable(bench
    benchs/bench-cdt.cpp
    benchs/bench-cctz.cpp
    benchs/bench-icudt.cpp
    benchs/bench-cdt-re.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/parse-date.cpp
)
target_include_directories(bench PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/c-dt/
)
target_link_libraries(bench benchmark::benchmark cdt cctz::cctz icu::icu dl)
# gtest_discover_tests(tests)
