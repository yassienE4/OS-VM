#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    char *args[] = { (char*)"ls", nullptr };
    execvp("ls", args);
    perror("execvp");  // runs only if exec fails
}
