cmake_minimum_required(VERSION 3.0)

project(cpp_3d_eindopdracht)

#zet de dll library automatisch in de exe folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources src/*.cpp src_dependecies/*.c)

add_executable(cpp_3d_eindopdracht ${sources})

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/Debug/resources
    COMMENT "Copying resources!")
add_dependencies(cpp_3d_eindopdracht copy_resources)

target_include_directories(cpp_3d_eindopdracht PUBLIC "${CMAKE_SOURCE_DIR}/header/")
target_include_directories(cpp_3d_eindopdracht PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_link_directories(cpp_3d_eindopdracht PUBLIC "${CMAKE_SOURCE_DIR}/lib/")

target_link_libraries(cpp_3d_eindopdracht SDL2 opengl32)