#include "Headers.hpp"

class fairLock{
private:
    pthread_mutex_t queue;
    pthread_mutex_t writers;
    pthread_mutex_t critical;
    int readers;
public:
    fairLock();
    ~fairLock();
    void enterWriter();
    void leaveWriter();
    void enterReader();
    void leaverReader();
};