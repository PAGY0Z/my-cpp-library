if(BUILD_TESTS)
    enable_testing()

    file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

    add_executable(tests_Library ${TEST_SOURCES})

    target_link_libraries(tests_Library gtest_main MyLibrary)
    
    target_include_directories(tests_Library PRIVATE ${MyLibrary_INCLUDE_DIRS})

    include(GoogleTest)
    gtest_discover_tests(tests_Library)
endif()
