#ifndef _LOG_H
#define _LOG_H

#include "Headers.hpp"

class Log
{
private:
    ofstream logStream;
    pthread_mutex_t logLock;      
public:
    Log(const char *filename);
    ~Log();

    void Log::writeLine(string newLine);
    void writeStream(stringstream &newStream);
};

#endif