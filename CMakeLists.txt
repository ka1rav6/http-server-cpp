cmake_minimum_required(VERSION 3.10)

project(HttpServer)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files from ./include
include_directories(include)

# Find all .cpp files inside src/
file(GLOB SRC_FILES "src/*.cpp")

# Create executable
add_executable(server ${SRC_FILES})
