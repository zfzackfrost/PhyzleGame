cmake_minimum_required(3.0)
project(Phyzle)

add_subdirectory(boost-cmake)

file (GLOB_RECURSE PHYZLE_SOURCES "src/*.cpp" "src/*.c" "src/*.cxx")
add_executable(Phyzle ${PHYZLE_SOURCES})
target_link_libraries(Phyzle PUBLIC Boost::boost)


