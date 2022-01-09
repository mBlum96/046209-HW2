#include "Headers.hpp"
#include "Bank.hpp"

int isLegalPass(int accPass){

}

Bank::openAccount(){
    
}

Message Bank::doesAccountExist(int accId){
    if(account_map.find(accId)!=account_map.end()){
        return ACC_EXISTS;
    }
    return ACC_DOESNT_EXIST;
}

Message Bank::openAccount(int accId,int accPass,float initAmount){
    Account_params new_acc_prm;
    new_acc_prm.account_id = accId;
    new_acc_prm.balance = initAmount;
    new_acc_prm.password = accPass;
    Account newAccount(new_acc_prm);
    pthread_mutex_lock()
    account_map.insert();
}