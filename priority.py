def find_turnaround_and_waiting_time_non_preemptive(processes, n, burst_time, priority, arrival_time):
    wt = [0] * n
    tat = [0] * n

    # Sorting processes according to priority (non-preemptive)
    for i in range(n):
        for j in range(i + 1, n):
            if priority[i] > priority[j]:
                # Swap burst times, priorities, and process IDs
                burst_time[i], burst_time[j] = burst_time[j], burst_time[i]
                priority[i], priority[j] = priority[j], priority[i]
                arrival_time[i], arrival_time[j] = arrival_time[j], arrival_time[i]
                processes[i], processes[j] = processes[j], processes[i]

    # Calculate waiting time for non-preemptive
    for i in range(1, n):
        wt[i] = burst_time[i - 1] + wt[i - 1]

    # Calculate turnaround time for non-preemptive
    for i in range(n):
        tat[i] = burst_time[i] + wt[i]

    return wt, tat


def find_turnaround_and_waiting_time_preemptive(processes, n, burst_time, arrival_time, priority):
    wt = [0] * n
    tat = [0] * n
    remaining_burst_time = burst_time[:]
    completed = [False] * n
    current_time = 0
    process_queue = []

    while True:
        idx = -1
        min_priority = float('inf')

        # Find the process with the highest priority (smallest priority number) that's ready
        for i in range(n):
            if not completed[i] and arrival_time[i] <= current_time:
                if priority[i] < min_priority:
                    min_priority = priority[i]
                    idx = i

        # If no process is found, break
        if idx == -1:
            break

        # Process execution (preemptive)
        remaining_burst_time[idx] -= 1
        current_time += 1

        if remaining_burst_time[idx] == 0:
            completed[idx] = True
            tat[idx] = current_time - arrival_time[idx]
            wt[idx] = tat[idx] - burst_time[idx]

    return wt, tat


def main():
    n = int(input("Enter the number of processes: "))
    processes = []
    burst_time = []
    arrival_time = []
    priority = []

    for i in range(n):
        process_id = int(input(f"Enter process ID for process {i + 1}: "))
        burst = int(input(f"Enter CPU burst time for process {i + 1}: "))
        arrival = int(input(f"Enter arrival time for process {i + 1}: "))
        pr = int(input(f"Enter priority for process {i + 1}: "))
        processes.append(process_id)
        burst_time.append(burst)
        arrival_time.append(arrival)
        priority.append(pr)

    # Calculate for Non-Preemptive Priority Scheduling
    print("\nNon-Preemptive Priority Scheduling:")
    wt_non_preemptive, tat_non_preemptive = find_turnaround_and_waiting_time_non_preemptive(
        processes, n, burst_time, priority, arrival_time)
    
    print("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time")
    for i in range(n):
        print(f"{processes[i]}\t\t{burst_time[i]}\t\t{priority[i]}\t\t{wt_non_preemptive[i]}\t\t{tat_non_preemptive[i]}")

    # Calculate for Preemptive Priority Scheduling
    print("\nPreemptive Priority Scheduling:")
    wt_preemptive, tat_preemptive = find_turnaround_and_waiting_time_preemptive(
        processes, n, burst_time, arrival_time, priority)
    
    print("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time")
    for i in range(n):
        print(f"{processes[i]}\t\t{burst_time[i]}\t\t{priority[i]}\t\t{wt_preemptive[i]}\t\t{tat_preemptive[i]}")

if __name__ == "__main__":
    main()

#4
#5 0      4 1     2 2      1 4
