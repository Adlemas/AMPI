cmake_minimum_required(VERSION 3.21.4 FATAL_ERROR)

set(PROJECT_NAME AMPI)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/external/test.h
    src/external/test.cpp
    src/external/lib/TimeoutManager.h
    src/external/lib/TimeoutManager/TimeoutManager.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)