#ifndef _ACC_H
#define _ACC_H

#include "Headers.hpp"

struct Account_params{
    int account_id;
    int password;
    int balance;
};

class Account
{
private:
    Account_params acc_par;
    pthread_mutex_t accLock;
public:
    Account(Account_params acc_par);
    ~Account();
    // Message openAccount(int account_id, int password, int balance);
    void balanceSetter(int amount, Action action);
    int balanceGetter();
    int passwordGetter();
    int idGetter();
};

#endif