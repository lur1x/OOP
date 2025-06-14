cmake_minimum_required(VERSION 3.30)
project(CHTTPUrl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

cmake_minimum_required(VERSION 3.30)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)


add_executable(CHTTPUrl main.cpp
        CHTTPUrl.cpp
        CHTTPUrl.h
        Constants.h
        CUrlParsingError.h
        CUrlParsingError.cpp
        Controller.cpp
        Controller.h
)


add_executable(${PROJECT_NAME}Test
        ${PROJECT_NAME}Test.cpp
        CHTTPUrl.cpp
        CHTTPUrl.h
        Constants.h
        CUrlParsingError.h
        CUrlParsingError.cpp
        Controller.cpp
        Controller.h
)

target_link_libraries(${PROJECT_NAME}Test gtest gtest_main)

enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)
add_definitions(-DGTEST_HAS_PTHREAD=0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CODE_COVERAGE "Enable code coverage" OFF)
if (CODE_COVERAGE)
    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
        target_compile_options(${PROJECT_NAME}Test PRIVATE -fprofile-instr-generate -fcoverage-mapping)
        target_link_options(${PROJECT_NAME}Test PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    else ()
        target_compile_options(${PROJECT_NAME}Test PRIVATE --coverage)
        target_link_options(${PROJECT_NAME}Test PRIVATE --coverage)
    endif ()
endif ()