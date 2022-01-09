#include "Headers.hpp"
#include "Bank.hpp"

int isLegalPass(int accPass){

}

Message Bank::doesAccountExist(int accId){
    if(account_map.find(accId)!=account_map.end()){
        return ACC_EXISTS;
    }
    return ACC_DOESNT_EXIST;
}

Message Bank::openAccount(int accId,int accPass,int initAmount){
    Account_params new_acc_prm;
    new_acc_prm.account_id = accId;
    new_acc_prm.balance = initAmount;
    new_acc_prm.password = accPass;
    Account newAccount(new_acc_prm);
    pthread_mutex_lock(&accountWriteLock);
    account_map.insert({new_acc_prm.account_id, newAccount});
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return CREATED_NEW_ACC;
}

Message Bank::withDrawMoney(int accId,int accPass,
int amount, int *amount_getter){
    pthread_mutex_lock(&accountWriteLock);
    auto it = account_map.find(accId);
    *amount_getter = it->second.balanceGetter();
    if(*amount_getter <= amount){
        *amount_getter -= amount;
        pthread_mutex_unlock(&accountWriteLock);
        return INSUFFICIANT_FUNDS;
    }
    it->second.balanceSetter(amount,WITHDRAW);
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return WITHDREW_MONEY;
}

Message Bank::depositMoney(int accId,int accPass, int amount
, int *amount_getter){
    pthread_mutex_lock(&accountWriteLock);
    auto it = account_map.find(accId);
    *amount_getter = it->second.balanceGetter()+amount;
    it->second.balanceSetter(amount,DEPOSIT);
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return DEPOSITED_MONEY;
}
int Bank::checkAccountBalance(int accId){
    auto it = account_map.find(accId);
    return it->second.balanceGetter();
}

Message Bank::checkPass(int accId, int accPass){

}