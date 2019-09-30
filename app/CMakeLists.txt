file(GLOB_RECURSE SRC_LIST *.cpp *.h)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}Core)
target_link_libraries(${PROJECT_NAME} ncursesw)
target_link_libraries(${PROJECT_NAME} stdc++fs)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall -Wextra -pedantic -Wconversion
        -Wsign-conversion)
