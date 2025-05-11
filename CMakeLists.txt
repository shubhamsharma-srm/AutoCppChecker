cmake_minimum_required(VERSION 3.14)
project(AutoCheckCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(analyzer)
add_subdirectory(rulebase)

# Executable
add_executable(AutoCheckCpp main.cpp)

# Add include directory for json.hpp manually
target_include_directories(AutoCheckCpp PRIVATE ${CMAKE_SOURCE_DIR}/third_party/json)

# Link internal libraries
target_link_libraries(AutoCheckCpp PRIVATE analyzer rulebase)
