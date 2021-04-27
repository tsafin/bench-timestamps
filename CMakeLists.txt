cmake_minimum_required(VERSION 3.9)

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

include(build_icu)

add_executable(tests tests/test-cdt.cpp tests/test-cctz.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/c-dt/)
target_link_libraries(tests PUBLIC gtest_main cdt cctz::cctz)

add_executable(bench benchs/bench-cdt.cpp benchs/bench-cctz.cpp)
target_include_directories(bench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/c-dt/)
target_link_libraries(bench benchmark::benchmark cdt cctz::cctz)
# gtest_discover_tests(tests)
