cmake_minimum_required(VERSION 3.6)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# build type handling
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(
        STATUS
        "Setting build type to '${default_build_type}' as none was specified."
        )
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
endif()

# gtest isnt needed when build type is release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(debug_libs "gtest")
    set(pmm_debug "DEBUG")
    include(cmake/pmm.cmake)
    pmm(
        VCPKG
        REVISION 8c77506c4fc47c3ea4790d30fc78c45265b3e41a
        REQUIRES ${debug_libs}
        ${pmm_debug}
        )
endif()


if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -ggdb \
    -fno-limit-debug-info -fsanitize=undefined \
    -fsanitize=implicit-conversion -fsanitize=integer \
    -fno-limit-debug-info -fprofile-arcs -ftest-coverage")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    enable_testing()
    add_subdirectory(test)
endif()

add_subdirectory(app)
add_subdirectory(core)
