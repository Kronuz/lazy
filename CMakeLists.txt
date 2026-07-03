# lazy: lazy/deferred evaluation (eval, lazy_eval, the LAZY macro, a std::formatter)
#
#   cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build && ctest --test-dir build
#
# Header-only, dependency-free. Standard-library only.

cmake_minimum_required(VERSION 3.16)
project(lazy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

add_library(lazy INTERFACE)
target_include_directories(lazy INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(lazy INTERFACE cxx_std_20)
add_library(lazy::lazy ALIAS lazy)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	enable_testing()
	add_executable(lazy_test test/test.cc)
	target_link_libraries(lazy_test PRIVATE lazy)
	add_test(NAME lazy COMMAND lazy_test)
endif()
