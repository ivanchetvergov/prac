import re
import pandas as pd

with open("bench_res/results.txt", "r") as file:
    lines = file.readlines()

arr_size = None
test_results = []

for i in range(len(lines)):
    line = lines[i].strip()

    if "arr size: " in line:
        arr_size = int(re.findall(r"\d+", line)[0])
    elif "===" in line:
        test_name = line.strip("= ").strip()
    elif "real" in line or "user" in line or "sys" in line:
        if test_name:
            time_value = float(re.findall(r"\d+\.\d+", line)[0])
            metric = line.split()[0]
            test_results.append((test_name, metric, time_value))

df = pd.DataFrame(test_results, columns=["test", "metric", "time"])
df = df.pivot_table(
    index="test", columns="metric", values="time", aggfunc="first"
).reset_index()
df.columns.name = None

print(f"arr size: {arr_size}")
print(df)

df.to_csv("analysis/results_parsed.csv", index=False)

