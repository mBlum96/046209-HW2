#include "Headers.hpp"

class myMutexLock{
private:
    pthread_mutex_t writers;
    pthread_mutex_t critical;
    int readers;
public:
    myMutexLock();
    ~myMutexLock();
    void enterWriter();
    void leaveWriter();
    void enterReader();
    void leaveReader();
};