cmake_minimum_required(VERSION 3.9)

# enable_testing()
# find_package(GTest REQUIRED)
# include(GoogleTest)

# sudo apt-get install googletest
set(GoogleTest_ROOT /usr/src/googletest/googletest)
add_subdirectory(${GoogleTest_ROOT}
                ${CMAKE_CURRENT_BINARY_DIR}/googletest
                EXCLUDE_FROM_ALL)
add_subdirectory(c-dt)

add_executable(tests tests/test-cdt.cpp)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCEDIR}/c-dt/)

target_link_libraries(tests PUBLIC gtest_main cdt)
# gtest_discover_tests(tests)
