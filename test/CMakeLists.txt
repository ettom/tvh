set(SUBPRROJECT_NAME ${PROJECT_NAME}Test)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)
file(GLOB_RECURSE SRC_LIST *)
add_executable(${SUBPRROJECT_NAME} ${SRC_LIST})

target_link_libraries(${SUBPRROJECT_NAME}
    PRIVATE
        ${PROJECT_NAME}Core
        ${GTEST_BOTH_LIBRARIES}
        ${GMOCK_BOTH_LIBRARIES})

target_include_directories(${SUBPRROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIRS})
