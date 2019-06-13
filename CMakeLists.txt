cmake_minimum_required(VERSION 3.1.0)

project(spatiumlib VERSION 0.1.0 LANGUAGES CXX)

# Create library target
add_library(spatiumlib INTERFACE)

# Set include directories for target
target_include_directories(spatiumlib INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Unit tests for spatiumlib
add_subdirectory(test)
