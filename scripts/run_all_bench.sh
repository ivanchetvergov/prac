#run_all_bench.sh

PROJECT_DIR=$(dirname "$(realpath "$0")")/..
RAW_RES_DIR="${PROJECT_DIR}/assets/raw_res"

mkdir -p "$RAW_RES_DIR"

parse_output() {
  local file="$1"
  awk '/^(real|user|sys)/ {printf "%s ", $2} END {print ""}' "$file"
}

echo "starting all benchs..."

types_of_links=("static" "shared" "dl")

cd build

for type in "${types_of_links}"; do
  echo " " > "${RAW_RES_DIR}/${type}.txt"
  for test in $(ctest -N -R "^${type}" | grep -E "Test #|Test  #" | awk '{print $3}'); do
    echo "${test} done."
    temp=$(mktemp)
    /usr/bin/time -p ctest -R "^${test}$" 2>"$temp" 1 > /dev/null 
    bench_time=$(parse_output "$temp")
    echo "${test} : ${bench_time}" >> "${RAW_RES_DIR}/${type}.txt"
    rm "$temp"
  done
done

echo "bench is done! results in assets/raw_res"
