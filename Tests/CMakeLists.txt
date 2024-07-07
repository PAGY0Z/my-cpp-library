if(BUILD_TESTS)
    enable_testing()

    function(add_all_subdirectories base_dir)
        file(GLOB children RELATIVE ${base_dir} ${base_dir}/*)
        foreach(child ${children})
            if(IS_DIRECTORY ${base_dir}/${child})
                add_subdirectory(${base_dir}/${child})
            endif()
        endforeach()
    endfunction()

    add_all_subdirectories(${CMAKE_CURRENT_SOURCE_DIR})
endif()
