CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(Test_SpatiumLib
        LANGUAGES CXX)

find_package(Qt5Test REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
ENABLE_TESTING()

file(GLOB test_files . "*.cpp")

FOREACH(test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    add_test(${test_name} COMMAND $test_name)
    target_link_libraries(${test_name} PRIVATE Qt5::Test spatiumlib)
ENDFOREACH()
