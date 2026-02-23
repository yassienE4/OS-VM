#include <iostream>
#include <pthread.h>

using namespace std;

void* worker(void* arg) {
    int* id = (int*) arg;
    cout << "Thread " << *id << " running." << endl;
    pthread_exit(NULL);
}

int main() {
    const int N = 5;
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

