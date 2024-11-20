#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Function to calculate TAT and WT for Non-Preemptive SJF Scheduling
void sjf_non_preemptive(vector<Process>& processes) {
    int n = processes.size();
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Sort processes by arrival time first
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    vector<bool> is_completed(n, false);
    int completed = 0;

    // Execute processes based on shortest burst time
    while (completed < n) {
        int idx = -1;
        int min_burst_time = 1000000;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].arrival_time <= current_time && processes[i].burst_time < min_burst_time) {
                min_burst_time = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx != -1) {
            // Update completion time and calculate turnaround and waiting time
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

            total_waiting_time += processes[idx].waiting_time;
            total_turnaround_time += processes[idx].turnaround_time;

            current_time = processes[idx].completion_time;
            is_completed[idx] = true;
            completed++;
        } else {
            current_time++; // No process to execute, move forward in time
        }
    }

    // Print the results
    cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "   P" << processes[i].id << "      |     " << processes[i].arrival_time << "      |     " << processes[i].burst_time << "      |      " << processes[i].completion_time << "      |     " << processes[i].waiting_time << "      |      " << processes[i].turnaround_time << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << endl;
}

// Function to calculate TAT and WT for Preemptive SJF Scheduling
void sjf_preemptive(vector<Process>& processes) {
    int n = processes.size();
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    vector<int> remaining_burst_time(n);
    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    int current_time = 0;
    vector<bool> is_completed(n, false);
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst_time = 1000000;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].arrival_time <= current_time && remaining_burst_time[i] < min_burst_time) {
                min_burst_time = remaining_burst_time[i];
                idx = i;
            }
        }

        if (idx != -1) {
            remaining_burst_time[idx]--;

            if (remaining_burst_time[idx] == 0) {
                is_completed[idx] = true;
                completed++;
                processes[idx].completion_time = current_time + 1;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

                total_waiting_time += processes[idx].waiting_time;
                total_turnaround_time += processes[idx].turnaround_time;
            }

            current_time++;
        } else {
            current_time++; // No process to execute, move forward in time
        }
    }

    // Print the results
    cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "   P" << processes[i].id << "      |     " << processes[i].arrival_time << "      |     " << processes[i].burst_time << "      |      " << processes[i].completion_time << "      |     " << processes[i].waiting_time << "      |      " << processes[i].turnaround_time << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << endl;
}

int main() {
    int n;

    // Input the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    // Choose scheduling type (Non-Preemptive or Preemptive)
    int choice;
    cout << "\n1. Non-Preemptive SJF Scheduling\n2. Preemptive SJF Scheduling\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        sjf_non_preemptive(processes);
    } else if (choice == 2) {
        sjf_preemptive(processes);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}


// 4
// 0 5     1 3     2 4      4 1
