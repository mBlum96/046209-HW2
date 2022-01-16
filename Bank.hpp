#ifndef _BANK_H
#define _BANK_H

#include "Headers.hpp"
#include "Account.hpp"
#include "Log.hpp"
#include "myMutexLock.hpp"


using namespace std;

class Bank
{
private:
    unordered_map<int, Account> account_map;
    int bankBalance;
    //pthread_mutex_t logLock;
    //sem_t accountReadLock;
    //pthread_mutex_t accountWriteLock;
    myMutexLock mLock;
    pthread_mutex_t commissionLock;
    Log &bankLog;
     
public:
    //Bank();
    Bank(Log &log);
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
    void collectCommission();
    int checkAccountBalance(const int accId);
    void commissionPrinter(Message message, int* ammount_getter,
    int commission, int acc_id, int desired_amnt);
    void printSnapshot();
    Log& logGetter();
};



#endif