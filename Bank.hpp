#ifndef _BANK_H
#define _BANK_H

#include "Headers.hpp"
#include "Account.hpp"


using namespace std;

class Bank
{
private:
    unordered_map<int, Account> account_map;
    int bankBalance;
    pthread_mutex_t logLock;
    pthread_mutex_t accountReadLock;
    pthread_mutex_t accountWriteLock;
public:
    Bank();
    ~Bank();
    Message openAccount(int accId,int accPass,float initAmount);
    Message doesAccountExist();
};



#endif