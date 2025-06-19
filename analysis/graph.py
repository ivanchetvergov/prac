import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

project_root = Path(__file__).resolve().parents[1]

csv_path = project_root / "assets/data_tables"
output_dir = project_root / "assets/graphs"

data = []

for linking_type in ("static", "shared", "dlopen"):
    files_dir = csv_path / linking_type
    csv_files = list(files_dir.glob("*.csv"))
    # print(f"dir: {files_dir} \n files: {csv_files}")
    if not csv_files: continue

    csv_file = max(csv_files, key=lambda f: f.stat().st_mtime)
    filename = csv_file.stem # without .csv
    df = pd.read_csv(csv_file)
    df["source"] = linking_type.upper()
    data.append(df)

if not data: exit(1)

# all in one DataFrame
full_df = pd.concat(data, ignore_index=True)
full_df["label"] = full_df["source"] + " " + full_df["test_name"]

# sorting OX labels
full_df = full_df.sort_values("label")

# drawing
fig, ax1 = plt.subplots(figsize=(14, 7))

x = full_df["label"]
# building first OY (time)
ax1.plot(x, full_df["real"], marker="o", label="real")
ax1.plot(x, full_df["user"], marker="o", label="user")
ax1.plot(x, full_df["sys"], marker="o", label="sys")
# set up OX and label
ax1.set_xlabel("test name")
ax1.set_ylabel("time (sec)")
ax1.tick_params(axis="x", rotation=45)
ax1.legend(loc="upper left")
# building second OY (size)
ax2 = ax1.twinx()
ax2.plot(x, full_df["file_size"], marker="x", linestyle="--", color="gray", label="file_size")
ax2.set_ylabel("file size (bytes)")
ax2.legend(loc="upper right")

plt.title(f"performance for arr_size{filename}")
plt.tight_layout()
plt.savefig(output_dir / f"{filename}_graph.png")
    
