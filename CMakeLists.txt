cmake_minimum_required(VERSION 3.2)
project(breakout)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(breakout PROPERTY CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(lib/raylib)

add_executable(breakout
	src/breakout.cpp
	src/brick.cpp
	src/main.cpp
)

target_link_libraries(breakout raylib)
