#include "myMutexLock.hpp"

myMutexLock::myMutexLock(){
    readers = 0;
    pthread_mutex_init(&writers,NULL);
    pthread_mutex_init(&critical, NULL);
    pthread_mutex_init(&queue, NULL);
}

myMutexLock::~myMutexLock(){
    pthread_mutex_unlock(&queue);
    pthread_mutex_unlock(&writers);
    pthread_mutex_unlock(&critical);
    pthread_mutex_destroy(&queue);
    pthread_mutex_destroy(&writers);
    pthread_mutex_destroy(&critical);
}

void myMutexLock::enterWriter(){
    pthread_mutex_lock(&queue);
    pthread_mutex_lock(&writers);
    pthread_mutex_unlock(&queue);
}

void myMutexLock::leaveWriter(){
    pthread_mutex_unlock(&writers);
    sleep(1);
}

void myMutexLock::enterReader(){
    // pthread_mutex_lock(&queue);
    pthread_mutex_lock(&critical);
    readers++;
    if(readers==1){
        pthread_mutex_lock(&writers);
    }
    pthread_mutex_unlock(&critical);
    // pthread_mutex_unlock(&queue);
}

void myMutexLock::leaveReader(){
    pthread_mutex_lock(&critical);
    readers--;
    if(readers==0){
        pthread_mutex_unlock(&writers);
    }
    pthread_mutex_unlock(&critical);
    sleep(1);
}