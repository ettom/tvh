cmake_minimum_required(VERSION 3.6)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if(BUILD_TESTS) 	# cmake .. -DBUILD_TESTS=ON
	enable_testing()
	add_subdirectory(test)
endif()

add_subdirectory(app)
add_subdirectory(core)
