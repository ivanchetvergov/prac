cmake_minimum_required(VERSION 3.10)
project(student_db_app)

set(CMAKE_C_STANDARD 99)

add_executable(student_db 
  ${PROJECT_SOURCE_DIR}/../src/main.c
  ${PROJECT_SOURCE_DIR}/../src/database.c
  ${PROJECT_SOURCE_DIR}/../src/student_ui.c
)

target_include_directories(student_db PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(student_db PRIVATE ncurses z)

set_target_properties(student_db PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
