#include "Headers.hpp"
#include "Account.hpp"

Message Account::openAccount(int account_id, int password, int balance){

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