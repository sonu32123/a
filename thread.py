import threading

# Matrix dimensions
MAX_ROWS = 3
MAX_COLS = 3

# Matrices
mat1 = [[0]*MAX_COLS for _ in range(MAX_ROWS)]
mat2 = [[0]*MAX_COLS for _ in range(MAX_ROWS)]
result = [[0]*MAX_COLS for _ in range(MAX_ROWS)]

# Function for matrix addition
def add_row(row):
    global mat1, mat2, result
    for col in range(MAX_COLS):
        result[row][col] = mat1[row][col] + mat2[row][col]

# Input matrices
print("Enter elements for Matrix 1:")
for i in range(MAX_ROWS):
    mat1[i] = list(map(int, input(f"Enter row {i+1} of Matrix 1: ").split()))

print("Enter elements for Matrix 2:")
for i in range(MAX_ROWS):
    mat2[i] = list(map(int, input(f"Enter row {i+1} of Matrix 2: ").split()))

# Create threads for each row
threads = []
for i in range(MAX_ROWS):
    thread = threading.Thread(target=add_row, args=(i,))
    threads.append(thread)
    thread.start()

# Wait for all threads to complete
for thread in threads:
    thread.join()

# Output the result of matrix addition
print("Result of Matrix Addition:")
for i in range(MAX_ROWS):
    print(" ".join(map(str, result[i])))
