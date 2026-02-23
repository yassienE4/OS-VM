#include <iostream>
#include <pthread.h>

using namespace std;

void* printNumber(void* arg) {
    int* number = (int*) arg;
    cout << "Thread received: " << *number << endl;
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1;
    int value = 42;

    pthread_create(&thread1, NULL, printNumber, &value);
    pthread_join(thread1, NULL);

    return 0;
}

