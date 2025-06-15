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

if(NOT DEFINED SIZE)
    set(SIZE 100000)
endif()


message("SIZE: ${SIZE}")


add_custom_target(run_all_tests
    COMMAND mkdir -p ../bench_res
    COMMAND echo "arr size: ${SIZE}" > ../bench_res/results.txt
    COMMAND echo "=== STATIC IT O1 ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_static_it_O1 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== STATIC REC O1 ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_static_rec_O1 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== STATIC IT O2 === " >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_static_it_O2 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== STATIC REC O2 ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_static_rec_O2 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== STATIC IT Os ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_static_it_Os ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== STATIC REC Os ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_static_rec_Os ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== SHARED IT O1 ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_shared_it_O1 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== SHARED REC O1 ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_shared_rec_O1 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== SHARED IT O2 ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_shared_it_O2 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== SHARED REC O2 ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_shared_rec_O2 ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== SHARED IT Os ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_shared_it_Os ${SIZE} 2>> ../bench_res/results.txt
    COMMAND echo "=== SHARED REC Os ===" >> ../bench_res/results.txt
    COMMAND /usr/bin/time -p ./bench_shared_rec_Os ${SIZE} 2>> ../bench_res/results.txt
    COMMENT "tests done! file results.txt created..."
)

