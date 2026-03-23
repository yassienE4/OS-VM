#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
};

// first come first serve
double fcfs(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    double totalWaiting = 0;

    for (auto &p : processes) {
        if (time < p.arrival)
            time = p.arrival;

        totalWaiting += (time - p.arrival);
        time += p.burst;
    }

    return totalWaiting / processes.size();
}

// shortest job first
double sjf(vector<Process> processes) {
    int n = processes.size();
    vector<bool> completed(n, false);

    int time = 0, done = 0;
    double totalWaiting = 0;

    while (done < n) {
        int idx = -1;
        int minBurst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrival <= time) {
                if (processes[i].burst < minBurst) {
                    minBurst = processes[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        totalWaiting += (time - processes[idx].arrival);
        time += processes[idx].burst;
        completed[idx] = true;
        done++;
    }

    return totalWaiting / n;
}

// round robin
double roundRobin(vector<Process> processes, int quantum) {
    int n = processes.size();
    queue<int> q;

    vector<int> remaining(n);

    for (int i = 0; i < n; i++) {
        remaining[i] = processes[i].burst;
    }

    int time = 0, completed = 0;
    double totalWaiting = 0;

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(), [&](int a, int b) {
        return processes[a].arrival < processes[b].arrival;
    });

    int i = 0;

    while (completed < n) {
        while (i < n && processes[order[i]].arrival <= time) {
            q.push(order[i]);
            i++;
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int idx = q.front();
        q.pop();

        int execTime = min(quantum, remaining[idx]);
        remaining[idx] -= execTime;
        time += execTime;

        while (i < n && processes[order[i]].arrival <= time) {
            q.push(order[i]);
            i++;
        }

        if (remaining[idx] > 0) {
            q.push(idx);
        } else {
            completed++;
            totalWaiting += (time - processes[idx].arrival - processes[idx].burst);
        }
    }

    return totalWaiting / n;
}


int main() {
    ifstream file("processes.txt");

    if (!file) {
        cerr << "Error: Could not open processes.txt\n";
        return 1;
    }

    int n;
    file >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        file >> processes[i].arrival >> processes[i].burst;
    }

    int quantum;
    file >> quantum;

    file.close();

    double fcfs_avg = fcfs(processes);
    double sjf_avg = sjf(processes);
    double rr_avg = roundRobin(processes, quantum);

    // output
    cout << "Average Waiting Times:\n";
    cout << "FCFS: " << fcfs_avg << endl;
    cout << "SJF: " << sjf_avg << endl;
    cout << "Round Robin: " << rr_avg << endl;

    // export
    ofstream csv("results.csv");

    if (!csv) {
        cerr << "Error: Could not create results.csv\n";
        return 1;
    }

    csv << "Algorithm,Average Waiting Time\n";
    csv << "FCFS," << fcfs_avg << "\n";
    csv << "SJF," << sjf_avg << "\n";
    csv << "Round Robin," << rr_avg << "\n";

    csv.close();

    cout << "\nResults exported to results.csv\n";

    system("python plot.py");

    return 0;
}