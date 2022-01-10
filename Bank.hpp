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
    sem_t accountReadLock;
    pthread_mutex_t accountWriteLock;
public:
    Bank();
    ~Bank();
    Message openAccount(const int accId,const int accPass,
    const int initAmount);
    Message doesAccountExist(const int accId);
    Message withDrawMoney(const int accId,const int amount, int *amount_getter);
    Message depositMoney(const int accId,const int amount, int *amount_getter);
    Message checkPass(const int accId,const int accPass);
    Message deleteAccount(const int accId, int *amount_getter);
    Message transfer(const int sourceId, const int sourcePass,
    const int targetId, const int amount, int *amount_getter);
    int checkAccountBalance(const int accId);
};



#endif