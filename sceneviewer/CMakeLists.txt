CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(sceneviewer LANGUAGES CXX)

#find_package(spatiumlib REQUIRED)
#find_package(Qt5Core REQUIRED)
#find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

set(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE resources ${CMAKE_CURRENT_SOURCE_DIR} *.qrc)
file(GLOB_RECURSE uis ${CMAKE_CURRENT_SOURCE_DIR} *.ui)

add_executable(${PROJECT_NAME} ${sources} ${headers} ${resources} ${uis})

target_link_libraries(${PROJECT_NAME} PRIVATE spatiumlib Qt5::Widgets Qt5::Multimedia)

