#!/bin/bash

# hash table
declare -A table

print_tree(){
  local file=$1
  local tab=$2

  if [[ ! -f "$file" || ${table["$file"]} ]]; then
    return
  fi

  table["$file"]=1;
  printf "%*s%s\n" "$tab" "" "$(basename "$file")"
  # set separator and read all str
  while IFS= read -r line; do
    lib=$(echo "$line" | awk '{print $3}')
    if [[ -n "$lib" && -f "$lib" ]]; then
      print_tree "$lib" $((tab + 1))
    fi
  done < <(ldd "$file" 2>/dev/null)
}

if [[ $# -ne 1 ]]; then
  echo "usage: $0 /path/to/program"
  exit 1
fi

echo "drawing tree for: $1"
print_tree "$1" 0

