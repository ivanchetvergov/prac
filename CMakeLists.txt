cmake_minimum_required(VERSION 3.10)
project(SearchMinBenchmark)

set(CMAKE_C_STANDARD 11)

# headers 
include_directories(${PROJECT_SOURCE_DIR}/include)

# libs src
link_directories(${PROJECT_SOURCE_DIR}/libs)

# bench files
set(BENCH_REC tests/bench_rec.c)
set(BENCH_IT tests/bench_it.c)

# static bench
foreach(opt_level O0 O1 O2 Os)
    add_executable(bench_static_rec_${opt_level} ${BENCH_REC})
    target_link_libraries(bench_static_rec_${opt_level} search_min_static)
    set_target_properties(bench_static_rec_${opt_level} PROPERTIES COMPILE_OPTIONS "-${opt_level}")

    add_executable(bench_static_it_${opt_level} ${BENCH_IT})
    target_link_libraries(bench_static_it_${opt_level} search_min_static)
    set_target_properties(bench_static_it_${opt_level} PROPERTIES COMPILE_OPTIONS "-${opt_level}")
endforeach()

# shared bench
foreach(opt_level O0 O1 O2 Os)
    add_executable(bench_shared_rec_${opt_level} ${BENCH_REC})
    target_link_libraries(bench_shared_rec_${opt_level} search_min_shared)
    set_target_properties(bench_shared_rec_${opt_level} PROPERTIES COMPILE_OPTIONS "-${opt_level}")

    add_executable(bench_shared_it_${opt_level} ${BENCH_IT})
    target_link_libraries(bench_shared_it_${opt_level} search_min_shared)
    set_target_properties(bench_shared_it_${opt_level} PROPERTIES COMPILE_OPTIONS "-${opt_level}")
endforeach()

