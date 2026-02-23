#include <iostream>
#include <pthread.h>

using namespace std;

int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    cout << "Final counter: " << counter << endl;
}

