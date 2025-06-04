cmake_minimum_required(VERSION 3.30)
project(Shapes)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(Shapes main.cpp
        src/IShape.cpp
        include/IShape.h
        src/CPoint.cpp
        include/CPoint.h
        src/CLineSegment.cpp
        include/CLineSegment.h
        include/ISolidShape.h
        src/CTriangle.cpp
        include/CTriangle.h
        src/CRectangle.cpp
        include/CRectangle.h
        src/CCircle.cpp
        include/CCircle.h
        src/CShapesController.cpp
        include/CShapesController.h
        include/Constants.h)

add_executable(${PROJECT_NAME}Test
        tests/${PROJECT_NAME}Test.cpp
        src/IShape.cpp
        include/IShape.h
        src/CPoint.cpp
        include/CPoint.h
        src/CLineSegment.cpp
        include/CLineSegment.h
        include/ISolidShape.h
        src/CTriangle.cpp
        include/CTriangle.h
        src/CRectangle.cpp
        include/CRectangle.h
        src/CCircle.cpp
        include/CCircle.h
        src/CShapesController.cpp
        include/CShapesController.h
        include/Constants.h
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