#include "Headers.hpp"
#include "Account.hpp"

Message Account::openAccount(int account_id, int password, int balance){

}
int Account::balanceGetter(){
    return this->acc_par.balance;
}
void Account::balanceSetter(int amount){
    this->acc_par.balance -= amount;
}