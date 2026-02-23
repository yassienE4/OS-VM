#include <iostream>
#include <pthread.h>

using namespace std;

int counter = 0;
pthread_mutex_t mutex1;

void* increment(void* arg) 
{
    for (int i = 0; i < 100000; i++) 
    {
        pthread_mutex_lock(&mutex1);
        counter++;
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex1, NULL);
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex1);
    cout << "Final counter: " << counter << endl;
}


