cmake_minimum_required(VERSION 3.12)

project(delphi_cpp VERSION 0.0.1 
                   LANGUAGES C CXX)
####################
# Project Settings #
####################

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "-Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

################
# Dependencies #
################
include(FetchContent)
cmake_policy(SET CMP0135 NEW)

# PhASAR
find_package(phasar COMPONENTS llvm_ifdside REQUIRED)

# Nlohmann JSON
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# spdlog
find_package(spdlog REQUIRED)

# gtest
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  FetchContent_MakeAvailable(googletest)
endif()

################
# Source Files #
################

# Get our source files
file(GLOB_RECURSE SRC_FILES src/core/*.cpp src/utils/*.cpp)

####################
# Main Executables #
####################
set(EXTRACT_EXECUTABLE dcpp_extract)
set(FILTER_EXECUTABLE dcpp_filter)

# executable for extracting a feature map
add_executable(${EXTRACT_EXECUTABLE} src/execs/dcpp_extract.cpp ${SRC_FILES})
target_include_directories(${EXTRACT_EXECUTABLE} PRIVATE src)
target_link_libraries(${EXTRACT_EXECUTABLE} PRIVATE phasar::llvm_ifdside 
                                                    nlohmann_json::nlohmann_json 
                                                    spdlog::spdlog)

# executable for filtering a feature map
add_executable(${FILTER_EXECUTABLE} src/execs/dcpp_filter.cpp ${SRC_FILES})
target_include_directories(${FILTER_EXECUTABLE} PRIVATE src)
target_link_libraries(${FILTER_EXECUTABLE} PRIVATE phasar::llvm_ifdside 
                                                   nlohmann_json::nlohmann_json 
                                                   spdlog::spdlog)

#############
# Add Tests #
#############

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # filter test
  add_executable(filter_test tests/filter_test.cpp ${SRC_FILES})
  target_include_directories(filter_test PRIVATE src )
  target_link_libraries(filter_test PRIVATE phasar::llvm_ifdside 
                                            nlohmann_json::nlohmann_json 
                                            spdlog::spdlog
                                            GTest::gtest_main)
endif()