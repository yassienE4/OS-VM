#include <iostream>
#include <pthread.h>

using namespace std;

void* sayHello(void* arg) {
    cout << "Hello from thread!" << endl;
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1;

    pthread_create(&thread1, NULL, sayHello, NULL);

    pthread_join(thread1, NULL);

    cout << "Back in main thread." << endl;
    return 0;
}

