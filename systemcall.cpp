#include <iostream>
#include <unistd.h>   // For fork, getpid, getppid
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    // For open
#include <cstring>    // For strlen
#include <cstdlib>    // For exit
#include <sys/wait.h> // For wait

using namespace std;

int main() {
    cout << "Demonstrating 5 system calls:\n";

    // 1. Fork system call
    cout << "\n1. Fork System Call:\n";
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        exit(1);
    } else if (pid == 0) {
        // Child process
        cout << "In Child Process (PID: " << getpid() << ", Parent PID: " << getppid() << ")\n";
        exit(0);
    } else {
        // Parent process
        cout << "In Parent Process (PID: " << getpid() << "), Child PID: " << pid << endl;
        wait(NULL); // Wait for the child process to complete
        cout << "Child process completed.\n";
    }

    // 2. getpid system call
    cout << "\n2. getpid and getppid System Calls:\n";
    cout << "Current Process ID: " << getpid() << endl;
    cout << "Parent Process ID: " << getppid() << endl;

    // 3. open and write system calls
    cout << "\n3. open and write System Calls:\n";
    const char *filename = "example.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        cerr << "Failed to open file!" << endl;
        exit(1);
    }
    const char *message = "Hello, this is a system call demonstration.\n";
    write(fd, message, strlen(message)); // Write to the file
    cout << "Data written to file: " << filename << endl;
    close(fd); // Close the file

    // 4. read system call
    cout << "\n4. read System Call:\n";
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        cerr << "Failed to open file for reading!" << endl;
        exit(1);
    }
    char buffer[1024];
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1); // Read file content
    if (bytesRead < 0) {
        cerr << "Failed to read file!" << endl;
        exit(1);
    }
    buffer[bytesRead] = '\0'; // Null-terminate the string
    cout << "Contents of the file:\n" << buffer << endl;
    close(fd);

    // 5. execvp system call
    cout << "\n5. execvp System Call:\n";
    pid = fork(); // Create another child process
    if (pid == 0) {
        // In child process
        char *args[] = {(char *)"ls", (char *)"-l", NULL};
        execvp("ls", args); // Execute the `ls -l` command
        cerr << "Exec failed!" << endl;
        exit(1);
    } else if (pid > 0) {
        wait(NULL); // Parent waits for the child
        cout << "Execvp executed successfully.\n";
    } else {
        cerr << "Fork failed for execvp demonstration!" << endl;
    }

    return 0;
}
