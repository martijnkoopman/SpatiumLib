CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(Test_SpatiumLib
        LANGUAGES CXX)

find_package(Qt5Test REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
ENABLE_TESTING()

# Imaging tests
#if(TEST_IMAGING)
    find_package(Qt5Gui REQUIRED)

    SET(test_files ImageIO_test.cpp Image_test.cpp GlobalThresholdFilter_test.cpp Graphics2D_test.cpp Graphics3D_test.cpp)
    FOREACH(test_file ${test_files})
        get_filename_component(test_name ${test_file} NAME_WE)
        add_executable(${test_name} ${test_file})
        add_test(${test_name} COMMAND $test_name)
        target_link_libraries(${test_name} PRIVATE Qt5::Test Qt5::Gui spatiumlib)
    ENDFOREACH()
# endif()

# Other tests
# file(GLOB test_files . "*.cpp")
SET(test_files TestUtilities_test.cpp Matrix_test.cpp Vector3_test.cpp Matrix4x4_test.cpp Math_test.cpp Statistics_test.cpp)

FOREACH(test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    add_test(${test_name} COMMAND $test_name)
    target_link_libraries(${test_name} PRIVATE Qt5::Test spatiumlib)
ENDFOREACH()
