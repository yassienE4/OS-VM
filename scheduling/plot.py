import csv
import matplotlib.pyplot as plt

algorithms = []
waiting_times = []

with open('results.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        algorithms.append(row['Algorithm'])
        waiting_times.append(float(row['Average Waiting Time']))

plt.figure()
plt.bar(algorithms, waiting_times)

plt.xlabel('Scheduling Algorithm')
plt.ylabel('Average Waiting Time')
plt.title('CPU Scheduling Comparison')


plt.savefig("chart.png")

print("Chart saved as chart.png")