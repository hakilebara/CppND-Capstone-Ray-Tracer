cmake_minimum_required(VERSION 3.28)
project(Raytracer VERSION 0.1 DESCRIPTION "A Ray Tracer Project")
include_directories(${PROJECT_SOURCE_DIR}/src)
# add_executable(raytracer src/main.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB_RECURSE SRC "src/*.cpp")
add_library(raytracer_src ${SRC})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Wpedantic")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Define the test executable
file(GLOB_RECURSE TST "tests/*.cpp")
add_executable(unit_tests ${TST})
target_link_libraries(unit_tests raytracer_src GTest::gtest_main)
