cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME Template)

project(${PROJECT_NAME} VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TESTS "Build unit tests" OFF)
option(CODE_COVERAGE "Enable coverage reporting" OFF)

if(CODE_COVERAGE AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Building with code coverage enabled")
    add_compile_options(--coverage -O0)
    add_link_options(--coverage)
endif()

add_subdirectory(Library)
add_subdirectory(${PROJECT_NAME})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)

    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
      DOWNLOAD_EXTRACT_TIMESTAMP true
    )
    FetchContent_MakeAvailable(googletest)
endif()
