# Define a class to represent a process
class Process:
    def __init__(self, pid, arrival_time, burst_time):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_burst_time = burst_time
        self.completion_time = 0
        self.turnaround_time = 0
        self.waiting_time = 0


# Function to calculate TAT and WT for Non-Preemptive SJF Scheduling
def sjf_non_preemptive(processes):
    n = len(processes)
    total_waiting_time = 0
    total_turnaround_time = 0

    # Sort processes by arrival time first
    processes.sort(key=lambda x: x.arrival_time)

    current_time = 0
    completed = 0
    is_completed = [False] * n

    # Execute processes based on shortest burst time
    while completed < n:
        idx = -1
        min_burst_time = float('inf')

        # Find the process with the shortest burst time that has arrived
        for i in range(n):
            if not is_completed[i] and processes[i].arrival_time <= current_time and processes[i].burst_time < min_burst_time:
                min_burst_time = processes[i].burst_time
                idx = i

        if idx != -1:
            # Update completion time and calculate turnaround and waiting time
            processes[idx].completion_time = current_time + processes[idx].burst_time
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time

            total_waiting_time += processes[idx].waiting_time
            total_turnaround_time += processes[idx].turnaround_time

            current_time = processes[idx].completion_time
            is_completed[idx] = True
            completed += 1
        else:
            current_time += 1  # No process to execute, move forward in time

    # Print the results
    print("\nProcess ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time")
    print("------------------------------------------------------------")
    for p in processes:
        print(f"   P{p.pid}      |     {p.arrival_time}      |     {p.burst_time}      |      {p.completion_time}      |     {p.waiting_time}      |      {p.turnaround_time}")

    print(f"\nAverage Waiting Time: {total_waiting_time / n:.2f}")
    print(f"Average Turnaround Time: {total_turnaround_time / n:.2f}")


# Function to calculate TAT and WT for Preemptive SJF Scheduling
def sjf_preemptive(processes):
    n = len(processes)
    total_waiting_time = 0
    total_turnaround_time = 0

    # Sort processes by arrival time
    processes.sort(key=lambda x: x.arrival_time)

    current_time = 0
    completed = 0
    is_completed = [False] * n
    remaining_burst_time = [p.burst_time for p in processes]

    # Execute processes based on shortest remaining burst time
    while completed < n:
        idx = -1
        min_burst_time = float('inf')

        # Find the process with the shortest remaining burst time
        for i in range(n):
            if not is_completed[i] and processes[i].arrival_time <= current_time and remaining_burst_time[i] < min_burst_time:
                min_burst_time = remaining_burst_time[i]
                idx = i

        if idx != -1:
            remaining_burst_time[idx] -= 1

            if remaining_burst_time[idx] == 0:
                is_completed[idx] = True
                completed += 1
                processes[idx].completion_time = current_time + 1
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time

                total_waiting_time += processes[idx].waiting_time
                total_turnaround_time += processes[idx].turnaround_time

            current_time += 1
        else:
            current_time += 1  # No process to execute, move forward in time

    # Print the results
    print("\nProcess ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time")
    print("------------------------------------------------------------")
    for p in processes:
        print(f"   P{p.pid}      |     {p.arrival_time}      |     {p.burst_time}      |      {p.completion_time}      |     {p.waiting_time}      |      {p.turnaround_time}")

    print(f"\nAverage Waiting Time: {total_waiting_time / n:.2f}")
    print(f"Average Turnaround Time: {total_turnaround_time / n:.2f}")


# Main function to test the SJF Scheduling
def main():
    # Input the number of processes
    n = int(input("Enter the number of processes: "))

    processes = []

    # Input process details
    for i in range(n):
        arrival_time = int(input(f"Enter Arrival Time for P{i + 1}: "))
        burst_time = int(input(f"Enter Burst Time for P{i + 1}: "))
        processes.append(Process(i + 1, arrival_time, burst_time))

    # Choose scheduling type (Non-Preemptive or Preemptive)
    print("\n1. Non-Preemptive SJF Scheduling")
    print("2. Preemptive SJF Scheduling")
    choice = int(input("Enter your choice: "))

    if choice == 1:
        sjf_non_preemptive(processes)
    elif choice == 2:
        sjf_preemptive(processes)
    else:
        print("Invalid choice!")


if __name__ == "__main__":
    main()


  
# 4
# pre 0 5     1 3     2 4      4 1
# nopre 1 3     2 4     1 2     4 4
