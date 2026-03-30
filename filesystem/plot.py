import csv
import matplotlib.pyplot as plt

lower_bounds = []
counts = []

with open("output.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        try:
            if row["lower_bound"] and row["count"]:
                lower_bounds.append(int(row["lower_bound"]))
                counts.append(int(row["count"]))
        except:
            continue


x = list(range(len(counts)))

plt.figure()
plt.bar(x, counts)


step = max(1, len(x) // 10)
plt.xticks(x[::step], [str(lb) for lb in lower_bounds[::step]], rotation=45)

plt.xlabel("File Size Range (bytes)")
plt.ylabel("Number of Files")
plt.title("File Size Histogram")

plt.tight_layout()
plt.savefig("chart.png")
