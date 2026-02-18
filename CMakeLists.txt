#
# The Guild - a text-based adventure by Sepe Ahtosalo, 
# in the spirit of classic roguelikes.
#

cmake_minimum_required(VERSION 3.16)
project(TheGuild)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Source files - add .cpp files here as they're implemented
set(SOURCES
    src/main.cpp
    src/ItemDatabase.cpp
    # src/Game.cpp        # still under construction
    # src/levels/TavernLevel.cpp  # still under construction
)

add_executable(TheGuild ${SOURCES})


if(WIN32)
    target_compile_definitions(TheGuild PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(TheGuild PRIVATE DEBUG)
endif()