cmake_minimum_required(VERSION 3.20)
project(SecureAccessKeys VERSION 1.0.0 LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "SecureAccessKeys is a Windows DLL project. Build it on Windows.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SECUREACCESSKEYS_BUILD_TESTS "Build the algorithm unit tests" ON)

add_library(SecureAccessKeys SHARED
    src/GenerateKeyEx.cpp
    src/SecurityAlgorithm.cpp
)

target_include_directories(SecureAccessKeys
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_definitions(SecureAccessKeys PRIVATE SECUREACCESSKEYS_EXPORTS)
set_target_properties(SecureAccessKeys PROPERTIES
    OUTPUT_NAME "SecureAccessKeys"
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
    CXX_VISIBILITY_PRESET hidden
)

if(MSVC)
    target_compile_options(SecureAccessKeys PRIVATE /W4 /permissive-)
endif()

if(SECUREACCESSKEYS_BUILD_TESTS)
    enable_testing()
    add_executable(SecurityAlgorithmTests
        tests/SecurityAlgorithmTests.cpp
        src/SecurityAlgorithm.cpp
    )
    target_include_directories(SecurityAlgorithmTests PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )
    add_test(NAME SecurityAlgorithmTests COMMAND SecurityAlgorithmTests)
endif()
