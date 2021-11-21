cmake_minimum_required(VERSION 3.21.4 FATAL_ERROR)

set(PROJECT_NAME AMPI)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    src/programm.cpp
    src/Renderer/ShaderProgramm.cpp
    src/Renderer/ShaderProgramm.h
    src/Renderer/Texture2D.cpp
    src/Renderer/Texture2D.h
    src/Resources/ResourceManager.cpp
    src/Resources/ResourceManager.h
    src/Resources/stb_image.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)