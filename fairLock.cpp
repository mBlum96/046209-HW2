#include "fairLock.hpp"

fairLock::fairLock(){
    readers = 0;
    pthread_mutex_unlock(&queue);
    pthread_mutex_unlock(&writers);
    pthread_mutex_unlock(&critical);
}

fairLock::~fairLock(){
    pthread_mutex_destroy(&queue);
    pthread_mutex_destroy(&writers);
    pthread_mutex_destroy(&critical);
}

void fairLock::enterWriter(){
    pthread_mutex_lock(&queue);
    pthread_mutex_lock(&writers);
    pthread_mutex_unlock(&queue);
}

void fairLock::leaveWriter(){
    pthread_mutex_unlock(&writers);
}

void fairLock::enterReader(){
    pthread_mutex_lock(&queue);
    pthread_mutex_lock(&critical);
    readers++;
    if(readers==1){
        pthread_mutex_lock(&writers);
    }
    pthread_mutex_unlock(&critical);
    pthread_mutex_unlock(&queue);
}

void fairLock::leaverReader(){
    pthread_mutex_lock(&critical);
    readers--;
    if(readers==1){
        pthread_mutex_unlock(&writers);
    }
    pthread_mutex_unlock(&critical);
}