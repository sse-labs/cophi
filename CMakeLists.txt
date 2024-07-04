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

################
# Dependencies #
################

find_package(phasar COMPONENTS llvm_ifdside REQUIRED)

##################
# Add Executable #
##################

# Get our source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Our main executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} phasar::llvm_ifdside)

# TODO: figure out how this works
# install(TARGETS ${PROJECT_NAME}
#         DESTINATION bin)