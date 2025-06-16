import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("analysis/results_parsed.csv")

plt.figure(figsize=(12, 6))

for metric in ["real", "user", "sys"]:
    plt.plot(df["test"], df[metric], marker='o', label=metric)

plt.xlabel("test")
plt.ylabel("time (sec)")
plt.title("comparison `real, 'user', 'sys' time of dif tests")
plt.xticks(rotation=45)
plt.legend()
plt.grid()

plt.savefig("analysis/results_plot.png", bbox_inches="tight")
print("graph saved in analysis/results_plot1.png")
