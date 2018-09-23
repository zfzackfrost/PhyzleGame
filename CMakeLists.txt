cmake_minimum_required(VERSION 3.1)
project(Phyzle)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add Library CMake files
add_subdirectory(boost-cmake)
add_subdirectory(glfw-3.2.1)

include_directories("glad/include" "include" "glm")

file (GLOB_RECURSE PHYZLE_SOURCES "src/*.cpp" "src/*.c" "src/*.cxx" "glad/src/*.c")
add_executable(Phyzle ${PHYZLE_SOURCES})
target_link_libraries(Phyzle PUBLIC Boost::boost)
target_link_libraries(Phyzle PUBLIC glfw)

