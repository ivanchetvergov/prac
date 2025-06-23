cmake_minimum_required(VERSION 3.15)
project(student_db C)

set(CMAKE_C_STANDARD 99)

add_executable(student_db
    ${PROJECT_SOURCE_DIR}/../src/main.c
    ${PROJECT_SOURCE_DIR}/../src/database.c
    ${PROJECT_SOURCE_DIR}/../src/student_ui.c
    ${PROJECT_SOURCE_DIR}/../src/student_back.c
)

include_directories(student_db PRIVATE ${PROJECT_SOURCE_DIR}/../include)
target_link_libraries(student_db PRIVATE ncurses z)

set(CUSTOM_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set_target_properties(student_db PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CUSTOM_OUTPUT_PATH}
)

add_custom_target(run
    COMMAND ${CUSTOM_OUTPUT_PATH}/student_db
    DEPENDS student_db
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "runnin' student_db..."
)

