#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        char *args[] = { (char*)"./task1", nullptr };
        execvp(args[0], args);
        perror("execvp failed");
    } else {
        cout << "Parent PID: " << getpid() << endl;
        wait(NULL);
        cout << "Finishing parent execution\n";
    }

    return 0;
}
