#sizeof_files.sh

PROJECT_DIR=$(dirname "$(realpath "$0")")/..
BUILD_DIR="${PROJECT_DIR}/build"

OUTPUT_FILE="${PROJECT_DIR}/assets/raw_res/sizes.txt"

touch ${OUTPUT_FILE}
echo "arr size: ${1}" > "${OUTPUT_FILE}"

files=$(find "${BUILD_DIR}" -maxdepth 1 -type f -name "bench*")

for file in ${files}; do
  size=$(stat -c "%s" "$file")
  echo "$(basename "$file") : ${size}" >> "${OUTPUT_FILE}"
done

echo "sizeof exec files in assets/raw_res.sizes.txt"

