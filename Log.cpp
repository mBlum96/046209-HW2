#include "Log.hpp"

Log::Log(const char* filename){
    logStream.open(filename);
    pthread_mutex_init(&logLock, NULL);
}

Log::~Log(){
    logStream.close();
    pthread_mutex_destroy(&logLock);
}

void Log::writeLine(string newLine){
    pthread_mutex_lock(&logLock);
    this->logStream << newLine << endl;
    pthread_mutex_unlock(&logLock);
}

void Log::writeStream(stringstream &newStream){
    this->writeLine(newStream.str()); 
}