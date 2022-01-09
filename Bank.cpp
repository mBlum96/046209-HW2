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
    sleep(1);
    pthread_mutex_unlock(&accountWriteLock);
    return CREATED_NEW_ACC;
}

Message Bank::withDrawMoney(int accId,int accPass,int amount){
    pthread_mutex_lock(&accountWriteLock);
    auto it = account_map.find(accId);
    if(it->second.balanceGetter() < amount){
        return INSUFFICIANT_FUNDS;
    }
    it->second.balanceSetter(amount);
    sleep(1);
    pthread_mutex_unlock(&accountWriteLock);
    return WITHDREW_MONEY;
}

Message Bank::checkPass(int accId, int accPass){

}