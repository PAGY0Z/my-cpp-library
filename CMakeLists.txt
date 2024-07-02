cmake_minimum_required(VERSION 3.14)

project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

set(INCLUDE_DIRS "")
foreach(_header IN ITEMS ${HEADER_FILES})
    get_filename_component(_header_path "${_header}" PATH)
    list(APPEND INCLUDE_DIRS "${_header_path}")
endforeach()

list(REMOVE_DUPLICATES INCLUDE_DIRS)

foreach(_dir IN LISTS INCLUDE_DIRS)
    target_include_directories(${PROJECT_NAME} PRIVATE "${_dir}")
endforeach()

target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -Wextra -Werror)

set_target_properties(${PROJECT.name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/..
)
