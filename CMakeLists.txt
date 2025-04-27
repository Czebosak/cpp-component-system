cmake_minimum_required(VERSION "3.19.2")

option(PRODUCTION_BUILD "Build in production mode" OFF)

project(ComponentSystem)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(ComponentSystem "${MY_SOURCES}")

target_include_directories(ComponentSystem PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

if(PRODUCTION_BUILD)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    target_compile_options(ComponentSystem PRIVATE -O3)
else()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
    target_compile_options(ComponentSystem PRIVATE -O0 -g)
endif()
