cmake_minimum_required(VERSION 3.21.4 FATAL_ERROR)

set(PROJECT_NAME ampi)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/external/lib/TimeoutManager.h
    src/external/lib/TimeoutManager/TimeoutManager.cpp
    src/external/lib/FileManager.h
    src/external/lib/FileManager/FileManager.cpp
    src/external/lib/CommandManager.h
    src/external/lib/CommandManager/CommandManager.cpp
    src/external/lib/Additional/Additional.cpp
    src/external/lib/Additional.h
    src/external/json/single_include/nlohmann/json.hpp
    src/external/AST/ast.cpp
    src/external/AST/ast.h
    src/external/AST/token.cpp
    src/external/AST/token.h
    src/external/AST/tokenizer.cpp
    src/external/AST/tokenizer.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)