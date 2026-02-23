#include <iostream>
#include <pthread.h>

using namespace std;

struct ThreadData {
    int id;
    int value;
};

void* printData(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    cout << "Thread " << data->id << " received "<< data->value << endl;
    pthread_exit(NULL);
}

int main() {
    const int N = 3;
    pthread_t threads[N];
    ThreadData threadData[N];

    for (int i = 0; i < N; i++) {
        threadData[i].id = i;
        threadData[i].value = i * 10;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i],NULL,printData,&threadData[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}