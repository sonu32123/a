#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Process {
public:
    int pid;              // Process ID
    int arrival_time;     // Arrival Time
    int burst_time;       // CPU Burst Time
    int priority;         // Priority
    int waiting_time;     // Waiting Time
    int turnaround_time;  // Turnaround Time
    int completion_time;  // Completion Time
    int remaining_time;   // Remaining Time for Preemptive Scheduling

    Process(int pid, int arrival_time, int burst_time, int priority)
        : pid(pid), arrival_time(arrival_time), burst_time(burst_time), priority(priority), 
          waiting_time(0), turnaround_time(0), completion_time(0), remaining_time(burst_time) {}
};

bool compareArrival(Process &a, Process &b) {
    return a.arrival_time < b.arrival_time;
}

bool comparePriority(Process &a, Process &b) {
    if (a.priority == b.priority) {
        return a.arrival_time < b.arrival_time;  // If priorities are same, use arrival time to break the tie
    }
    return a.priority < b.priority;  // Lower priority number indicates higher priority
}

// Function to calculate TAT and WT for Non-Preemptive Priority Scheduling
void prioritySchedulingNonPreemptive(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    vector<bool> is_completed(n, false);
    int completed = 0;

    while (completed < n) {
        // Find the process with highest priority (smallest priority value)
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            // Update completion time, turnaround time, and waiting time
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

            total_waiting_time += processes[idx].waiting_time;
            total_turnaround_time += processes[idx].turnaround_time;

            current_time = processes[idx].completion_time;
            is_completed[idx] = true;
            completed++;
        } else {
            current_time++;  // No process is ready, increment time
        }
    }

    // Display the results
    cout << "\nProcess ID | Arrival Time | Burst Time | Priority | Completion Time | Waiting Time | Turnaround Time" << endl;
    for (const auto& p : processes) {
        cout << "   P" << p.pid << "      |     " << p.arrival_time
             << "      |     " << p.burst_time
             << "      |     " << p.priority
             << "      |      " << p.completion_time
             << "      |     " << p.waiting_time
             << "      |      " << p.turnaround_time << endl;
    }

    cout << "\nAverage Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}

// Function to calculate TAT and WT for Preemptive Priority Scheduling
void prioritySchedulingPreemptive(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    vector<bool> is_completed(n, false);
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Find the process with highest priority (smallest priority value)
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            // Execute the process by reducing its remaining burst time
            processes[idx].remaining_time--;
            current_time++;

            if (processes[idx].remaining_time == 0) {
                // Process is completed
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

                total_waiting_time += processes[idx].waiting_time;
                total_turnaround_time += processes[idx].turnaround_time;

                is_completed[idx] = true;
                completed++;
            }
        } else {
            current_time++;  // If no process is ready to execute, increment time
        }
    }

    // Display the results
    cout << "\nProcess ID | Arrival Time | Burst Time | Priority | Completion Time | Waiting Time | Turnaround Time" << endl;
    for (const auto& p : processes) {
        cout << "   P" << p.pid << "      |     " << p.arrival_time
             << "      |     " << p.burst_time
             << "      |     " << p.priority
             << "      |      " << p.completion_time
             << "      |     " << p.waiting_time
             << "      |      " << p.turnaround_time << endl;
    }

    cout << "\nAverage Waiting Time: " << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (double)total_turnaround_time / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;

    // Input process details
    for (int i = 0; i < n; i++) {
        int arrival_time, burst_time, priority;
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> arrival_time;
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> burst_time;
        cout << "Enter Priority for P" << i + 1 << ": ";
        cin >> priority;

        processes.push_back(Process(i + 1, arrival_time, burst_time, priority));
    }

    // Choose scheduling type (Non-Preemptive or Preemptive)
    int choice;
    cout << "\n1. Non-Preemptive Priority Scheduling" << endl;
    cout << "2. Preemptive Priority Scheduling" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        prioritySchedulingNonPreemptive(processes);
    } else if (choice == 2) {
        prioritySchedulingPreemptive(processes);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

// 4
// pre 0 5      1 4       2 2      4 1 
