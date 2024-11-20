#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTATandWT(vector<Process>& processes, int quantum) {
    int n = processes.size();
    int time = 0;
    queue<Process*> readyQueue;

    // Initialize waiting time and turnaround time for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    int completed = 0;
    int i = 0;
    while (completed < n) {
        // Add processes to the ready queue based on arrival time
        if (i < n && processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
            readyQueue.push(&processes[i]);
            i++;
        }

        if (!readyQueue.empty()) {
            Process* current = readyQueue.front();
            readyQueue.pop();

            // Execute the process for the time quantum or until it's finished
            int execution_time = min(current->remaining_time, quantum);
            current->remaining_time -= execution_time;
            time += execution_time;

            // Calculate waiting time for all other processes
            for (int j = 0; j < n; j++) {
                if (processes[j].remaining_time > 0 && j != current->id) {
                    processes[j].waiting_time += execution_time;
                }
            }

            // If process is completed
            if (current->remaining_time == 0) {
                current->turnaround_time = time - current->arrival_time;
                completed++;
            } else {
                // Otherwise, push it back into the ready queue
                readyQueue.push(current);
            }
        } else {
            // If no process is ready, increment time
            time++;
        }
    }
}

void printResults(vector<Process>& processes) {
    cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < processes.size(); i++) {
        cout << processes[i].id << "\t\t"
             << processes[i].burst_time << "\t\t"
             << processes[i].arrival_time << "\t\t"
             << processes[i].waiting_time << "\t\t"
             << processes[i].turnaround_time << endl;
    }
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    vector<Process> processes(n);
    cout << "Enter the burst time for each process: \n";
    for (int i = 0; i < n; i++) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        processes[i].id = i + 1;
    }

    cout << "Enter the arrival time for each process: \n";
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
    }

    calculateTATandWT(processes, quantum);
    printResults(processes);

    return 0;
}


//4
//5 4 2 1        0 1 2 4
