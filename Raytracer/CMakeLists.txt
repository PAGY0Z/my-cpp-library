add_executable(MyRaytracer main.cpp)

target_link_libraries(MyRaytracer PRIVATE MyLibrary)

target_include_directories(MyRaytracer PRIVATE ${MyLibrary_INCLUDE_DIRS})

set_target_properties(MyRaytracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
