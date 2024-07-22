# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	MatterLightOverThread_test
	VERSION 1.0
	LANGUAGES C CXX ASM
)

# Include the definition of the slc_MatterLightOverThread_test target,
# which contains the content of the SLC project
include(MatterLightOverThread_test.cmake)

add_executable(MatterLightOverThread_test
    # Add additional sources here
)

target_include_directories(MatterLightOverThread_test PUBLIC
    # Add additional include paths here
)

target_compile_definitions(MatterLightOverThread_test PUBLIC
    # Add additional macros here
)

target_compile_options(MatterLightOverThread_test PUBLIC
    # Set additional compiler flags here
)

target_link_options(MatterLightOverThread_test PUBLIC
    # Set additional linker flags here
)

# Link with the content defined in the SLC project
target_link_libraries(MatterLightOverThread_test PRIVATE
    slc_MatterLightOverThread_test
)

# Include managed project content if available
include(MatterLightOverThread_test_project.cmake OPTIONAL RESULT_VARIABLE managed_project)
if(managed_project)
    message(STATUS "Using managed project content from ${managed_project}")
endif()

# Force the gcc linker command
set_target_properties(MatterLightOverThread_test PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET MatterLightOverThread_test
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:MatterLightOverThread_test>" "$<TARGET_FILE_DIR:MatterLightOverThread_test>/$<TARGET_FILE_BASE_NAME:MatterLightOverThread_test>.s37"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:MatterLightOverThread_test>" "$<TARGET_FILE_DIR:MatterLightOverThread_test>/$<TARGET_FILE_BASE_NAME:MatterLightOverThread_test>.hex"
    COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:MatterLightOverThread_test>" "$<TARGET_FILE_DIR:MatterLightOverThread_test>/$<TARGET_FILE_BASE_NAME:MatterLightOverThread_test>.bin" 
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET MatterLightOverThread_test
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()