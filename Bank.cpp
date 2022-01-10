#include "Headers.hpp"
#include "Bank.hpp"

int isLegalPass(int accPass){

}

Message Bank::doesAccountExist(const int accId){
    pthread_mutex_lock(&accountWriteLock);
    if(account_map.find(accId)!=account_map.end()){
        return ACC_EXISTS;
    }
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return ACC_DOESNT_EXIST;
}

Message Bank::openAccount(const int accId,const int accPass,
const int initAmount){
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

Message Bank::withDrawMoney(const int accId,const int amount,
 int *amount_getter){
    pthread_mutex_lock(&accountWriteLock);
    auto it = account_map.find(accId);
    *amount_getter = it->second.balanceGetter();
    if(*amount_getter <= amount){
        *amount_getter -= amount;
        pthread_mutex_unlock(&accountWriteLock);
        sleep(1);
        return INSUFFICIANT_FUNDS;
    }
    it->second.balanceSetter(amount,WITHDRAW);
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return WITHDREW_MONEY;
}

Message Bank::depositMoney(const int accId,
const int amount, int *amount_getter){
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

Message Bank::checkPass(const int accId, const int accPass){
    try
    {
        pthread_mutex_lock(&accountWriteLock);
        auto it = account_map.find(accId);
        if(it->second.passwordGetter()==accPass){
            pthread_mutex_unlock(&accountWriteLock);
            sleep(1);
            return PASSWORD_CURR;
        }
        else{
            throw (-1);
        }
    }
    catch(...)
    {
        pthread_mutex_unlock(&accountWriteLock);
        sleep(1);
        return PASSWORD_ERR;
    }
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return PASSWORD_ERR;
}

Message Bank::deleteAccount(const int accId, int *amount_getter){
    pthread_mutex_lock(&accountWriteLock);
    auto it = account_map.find(accId);
    *amount_getter = it->second.balanceGetter();
    it->second.~Account();
    account_map.erase(it);
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return ACCOUNT_DELETED;
}

Message Bank::transfer(const int sourceId, const int sourcePass,
const int targetId, const int amount, int *amount_getter){
    pthread_mutex_lock(&accountWriteLock);
    auto itSource = account_map.find(sourceId);
    auto itTarget = account_map.find(targetId);
    int sourceBalance = itSource->second.balanceGetter();
    if(sourceBalance <= amount){
        pthread_mutex_unlock(&accountWriteLock);
        sleep(1);
        return INSUFFICIANT_FUNDS;
    }
    itSource->second.balanceSetter(amount,WITHDRAW);
    itTarget->second.balanceSetter(amount,DEPOSIT);
    *amount_getter = itTarget->second.balanceGetter();
    pthread_mutex_unlock(&accountWriteLock);
    sleep(1);
    return TRANSFER_SUCCESS;
}