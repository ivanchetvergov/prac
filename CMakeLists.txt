cmake_minimum_required(VERSION 3.10)
project(SearchMinBenchmark)

set(CMAKE_C_STANDARD 11)
enable_testing()

# dir
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)

# database app 
add_subdirectory(database_app)

# def size
if(NOT DEFINED SIZE)
  set(SIZE 100000)
endif()

message("arr size: ${SIZE}")

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/assets/raw_res)

set(BENCH_EX "")
set(OPT_LEVELS O0 O1 O2 Os)

# === static & shared link ===
foreach(opt_level IN LISTS OPT_LEVELS)
  foreach(link_type IN ITEMS static shared)
    foreach(mode IN ITEMS it rec)
      # env.. etc
      set(exec_name bench_${link_type}_${mode}_${opt_level})
      set(source_file ${PROJECT_SOURCE_DIR}/tests/bench_${mode}.c)
      set(lib_name search_min_${link_type})
      set(test_name ${link_type}_${mode}_${opt_level})
      #compile
      if ("${mode}" STREQUAL "rec" AND ${SIZE} GREATER 100000000)
        message("${test_name} skipped: arr size to big!")
      else()
        add_executable(${exec_name} ${source_file})
        target_link_libraries(${exec_name} ${lib_name})
        set_target_properties(${exec_name} PROPERTIES COMPILE_OPTIONS "-${opt_level}")
        add_test(NAME ${test_name} COMMAND ${exec_name} ${SIZE})
        list(APPEND BENCH_EX ${exec_name})
      endif()
    endforeach()
  endforeach()
endforeach()

# === dlopen ===
foreach(mode IN ITEMS it rec)
  set(exec_name bench_dlopen_${mode})
  set(source_file ${PROJECT_SOURCE_DIR}/tests/bench_dlopen_${mode}.c)
  set(test_name dlopen_${mode})

  if("${mode}" STREQUAL "rec" AND ${SIZE} GREATER 100000000)
    message("${test_name} skipped: arr size to big).")
  else()
    add_executable(${exec_name} ${source_file})
    target_link_libraries(${exec_name} dl)
    add_test(NAME ${test_name} COMMAND ${exec_name} ${SIZE})
    list(APPEND BENCH_EX ${exec_name})
  endif()
endforeach()

add_custom_target(bench
  COMMENT "running all benchmarks (static, shared, dlopen)"
  DEPENDS ${BENCH_EX}
  COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/bench.sh
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "bench is done!"
)

add_custom_target(count_size
  DEPENDS bench
  COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/sizeof_files.sh ${SIZE}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "running calculating count_size"
)

add_custom_target(parse_and_build_graph
  DEPENDS bench count_size
  COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/parse_and_build_graph.sh
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "parse raw res and build graph!"
)

add_custom_target(full_cycle
  DEPENDS ${BENCH_EX}
  DEPENDS bench count_size parse_and_build_graph
  COMMENT "full cycle is done!"
)

