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
    Message openAccount(int accId,int accPass,int initAmount);
    Message doesAccountExist(int accId);
    Message withDrawMoney(int accId,int accPass,int amount);
    Message checkPass(int accId, int accPass);
};



#endif