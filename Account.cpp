#include "Headers.hpp"
#include "Account.hpp"

// Message Account::openAccount(int account_id, int password, int balance){

// }

Account :: Account(Account_params acc_params)
{
    acc_par.account_id = acc_params.account_id;
    acc_par.password = acc_params.password;
    acc_par.balance = acc_params.balance;
}
Account::~Account(){
    
}
int Account::balanceGetter(){
    return this->acc_par.balance;
}
void Account::balanceSetter(int amount, Action action){
    if(action == WITHDRAW){
        this->acc_par.balance -= amount;
    }
    else if (action==DEPOSIT){
        this->acc_par.balance += amount;
    }
}

int Account::passwordGetter(){
    return this->acc_par.password;
}

int Account::idGetter(){
    return this->acc_par.account_id;
}