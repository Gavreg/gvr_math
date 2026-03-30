cmake_minimum_required(VERSION 4.0)

project (gvr_math)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

message( "path = ${CMAKE_MODULE_PATH}")

set(CMAKE_CXX_STANDARD 23)

message(STATUS "GTest_CONFIG: ${GTest_CONFIG}")
message(STATUS "GTest_DIR: ${GTest_DIR}")

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
message(STATUS "GTest_ROOT: $ENV{GTest_ROOT}")
message(STATUS "GTEST_ROOT: $ENV{GTEST_ROOT}")


enable_testing()

add_executable(testing_exe test.cpp Vector.h)

target_link_libraries(testing_exe
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testing_exe)