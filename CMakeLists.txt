cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

# Specify the C standard
set(CMAKE_C_STANDARD 99)

# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/Unity/src)

# Add the library
add_library(mylib src/mylib.c)

# Add the main executable
add_executable(HelloWorld src/main.c)
target_link_libraries(HelloWorld mylib)

# Enable testing
enable_testing()

# Add the test directory
add_subdirectory(test)
