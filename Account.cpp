#include "Headers.hpp"
#include "Account.hpp"

// Message Account::openAccount(int account_id, int password, int balance){

// }

Account :: Account(Account_params acc_params)
{
    acc_par.account_id = acc_params.account_id;
    acc_par.password = acc_params.password;
    acc_par.balance = acc_params.balance;
    pthread_mutex_init(&accLock,NULL);
}
Account::~Account(){
    pthread_mutex_unlock(&accLock);
    pthread_mutex_destroy(&accLock);
}
int Account::balanceGetter(){
    // cout<<"the balance we get from the function is "<<this->acc_par.balance;
    return this->acc_par.balance;
}
void Account::balanceSetter(int amount, Action action){
    //cout<<"the ammount is"<<amount<<endl;
    if(action == WITHDRAW){
        // cout << "the amount to withdraw is"<<amount<<endl;
        pthread_mutex_lock(&accLock);
        this->acc_par.balance -=amount;
        pthread_mutex_unlock(&accLock);
        sleep(1);
        // cout<<"the new balance withdraw is "<<this->acc_par.balance<<endl;
    }
    else if (action == DEPOSIT){
        // cout << "the amount to deposit is "<<amount<<endl;
        pthread_mutex_lock(&accLock);
        int balance_after_dep = acc_par.balance + amount;
        // cout << "this is the balance I see right now looking at account " << acc_par.account_id << " " << acc_par.balance << endl;
        // cout << "this is what I, a dumb computer has calculated as the new balance: " << balance_after_dep <<endl;
        this->acc_par.balance = balance_after_dep;
        pthread_mutex_unlock(&accLock);
        sleep(1);
        // cout<<"the new balance deposit is "<<this->acc_par.balance<<endl;
    }
}

int Account::passwordGetter(){
    return this->acc_par.password;
}

int Account::idGetter(){
    return this->acc_par.account_id;
}