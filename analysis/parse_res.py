import re
import pandas as pd
from pathlib import Path

project_root = Path(__file__).resolve().parents[1]  # укажет на ~/praci

input_path = project_root / "assets/raw_res"
output_dir = project_root / "assets/data_tables"
sizes_file = input_path / "sizes.txt"

size_map = {}
arr_size = None

#read sizes.txt
with open(sizes_file, "r") as f:
    for line in f:
        line = line.strip()
        if line.startswith("arr size:") or not line:
            s = line.split(":")[1]
            arr_size = int(s.strip())
            continue
        name, size = line.split(":")
        size_map[name.strip()] = int(size.strip())

# parse raw res
def parse_line(line: str):
    parts = line.strip().split(":")
    if len(parts) != 2: return None
    temp_name = parts[0].strip()
    name = '_'.join(temp_name.split("_")[1:])
    values = parts[1].strip().split()
    if len(values) != 3: return None
    return {
        "test_name": name,
        "real": float(values[0]),
        "user": float(values[1]),
        "sys": float(values[2]),
    }

# for loop in every test
for test in ("static", "shared", "dl"):
    file_path = input_path / f"{test}.txt"
    if not file_path.exists(): continue

    parsed_data = []

    with open(file_path, "r") as f:
        for line in f:
            parsed = parse_line(line)
            if parsed:
                full_name = f"bench_{test}_{parsed['test_name']}"
                size = size_map.get(full_name)
                if size is None: continue
                parsed["file_size"] = size
                parsed_data.append(parsed)

    csv_path = output_dir / f"{test}/{arr_size}.csv"
    
    df = pd.DataFrame(parsed_data)
    df.to_csv(csv_path, index = False)
    print(f"saved in {csv_path}")
