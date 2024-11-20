# Function to calculate the Turnaround Time (TAT) and Waiting Time (WT)
def calculate_fcfs(processes, arrival_time, burst_time):
    n = len(processes)
    completion_time = [0] * n
    waiting_time = [0] * n
    turnaround_time = [0] * n
    
    # Calculate completion time for each process
    completion_time[0] = arrival_time[0] + burst_time[0]  # First process completes after its burst time
    for i in range(1, n):
        completion_time[i] = max(completion_time[i-1], arrival_time[i]) + burst_time[i]
    
    # Calculate waiting time and turnaround time
    for i in range(n):
        waiting_time[i] = completion_time[i] - arrival_time[i] - burst_time[i]
        turnaround_time[i] = completion_time[i] - arrival_time[i]
    
    # Calculate average waiting time and average turnaround time
    avg_waiting_time = sum(waiting_time) / n
    avg_turnaround_time = sum(turnaround_time) / n
    
    # Print results
    print("\nProcess | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time")
    print("------------------------------------------------------------")
    for i in range(n):
        print(f"  P{processes[i]}   |     {arrival_time[i]}      |     {burst_time[i]}      |      {completion_time[i]}      |     {waiting_time[i]}      |      {turnaround_time[i]}")
    
    print(f"\nAverage Waiting Time: {avg_waiting_time}")
    print(f"Average Turnaround Time: {avg_turnaround_time}")


# Input number of processes
n = int(input("Enter the number of processes: "))
processes = []
arrival_time = []
burst_time = []

# Input process details (arrival time and burst time)
for i in range(n):
    process_id = input(f"Enter Process ID for P{i + 1}: ")
    arrival = int(input(f"Enter Arrival Time for {process_id}: "))
    burst = int(input(f"Enter Burst Time for {process_id}: "))
    
    processes.append(process_id)
    arrival_time.append(arrival)
    burst_time.append(burst)

# Call the function to calculate TAT and WT using FCFS
calculate_fcfs(processes, arrival_time, burst_time)


# 4
# 0 2      1 2      5 3      6 4
