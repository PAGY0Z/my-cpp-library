add_executable(Template program_main.cpp)

target_link_libraries(Template PRIVATE MyLibrary)

target_include_directories(Template PRIVATE ${MyLibrary_INCLUDE_DIRS})

set_target_properties(Template PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Bin/
)
