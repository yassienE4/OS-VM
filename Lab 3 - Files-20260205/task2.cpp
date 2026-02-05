#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();
    if (pid < 0){
        cout << "Error during fork\n Exiting program...\n";
        exit(1);
    }
    if (pid == 0){
        cout << "Fork returned: " << pid << endl;
        cout << "I am the child: My PID is " << getpid() << endl;
        // exit(1);
    }
    else {
        cout << "Fork returned: " << pid << endl;
        cout << "I am the parent: my PID is " << getpid() << endl;
        // exit(1);
        wait(NULL);
        cout << "Finishing parent execution\n";
    }
    
}