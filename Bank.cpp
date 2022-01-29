#include "Bank.hpp"

Bank::Bank(Log &log):
bankBalance(0),bankLog(log){
    myMutexLock mLock;
    // pthread_mutex_init(&commissionLock,NULL);
    // pthread_mutex_init(&printLock,NULL);
}

Bank::~Bank(){
    mLock.~myMutexLock();
    // pthread_mutex_destroy(&commissionLock);
    // pthread_mutex_destroy(&printLock);
    // for(auto account : account_map){
    //     account.second.~Account();
    // }
}

Message Bank::doesAccountExist(const int accId){
    
    mLock.enterReader();
    if(account_map.find(accId)!=account_map.end()){
        mLock.leaveReader();
        return ACC_EXISTS;
    }
    mLock.leaveReader();
    return ACC_DOESNT_EXIST;
}

Message Bank::openAccount(const int accId,const int accPass,
const int initAmount){
    Account_params new_acc_prm;
    new_acc_prm.account_id = accId;
    new_acc_prm.balance = initAmount;
    new_acc_prm.password = accPass;
    Account newAccount(new_acc_prm);
    mLock.enterWriter();
    account_map.insert({new_acc_prm.account_id, newAccount});
    mLock.leaveWriter();
    return CREATED_NEW_ACC;
}

Message Bank::withDrawMoney(const int accId,const int amount,
 int *amount_getter){
    // mLock.enterWriter();
    mLock.enterReader();
    auto it = account_map.find(accId);
    *amount_getter = it->second.balanceGetter();
    if(*amount_getter < amount){
        *amount_getter -= amount;
        mLock.leaveReader();

        return INSUFFICIANT_FUNDS;
    }
    *amount_getter -= amount;
    //cout<<"before calling the function balance setter, the balance we read is "<<
    it->second.balanceSetter(amount,WITHDRAW);
    // mLock.leaveWriter();
    mLock.leaveReader();
    return WITHDREW_MONEY;
}

Message Bank::depositMoney(const int accId,
const int amount, int *amount_getter){
    //mLock.enterWriter();
    mLock.enterReader();
    auto it = account_map.find(accId);
    // cout<<"the account I found is " << it->first << "with balance "<< it->second.balanceGetter()<<endl;
    // cout<<"the amount before calling the func is "<< amount<< endl;
    //*amount_getter = it->second.balanceGetter()+amount;
    // cout<<"the ammoutn is " << amount <<endl;
    it->second.balanceSetter(amount,DEPOSIT);
    *amount_getter = it->second.balanceGetter();
    // cout<<"amount getter is"<<*amount_getter<<endl;
    // cout<<"the updated balance is" << it->second.balanceGetter();
    // mLock.leaveWriter();
    mLock.leaveReader();
    return DEPOSITED_MONEY;
}
int Bank::checkAccountBalance(int accId){
    auto it = account_map.find(accId);
    return it->second.balanceGetter();
}

Message Bank::checkPass(const int accId, const int accPass){
    try
    {
        mLock.enterReader();
        auto it = account_map.find(accId);
        if(it->second.passwordGetter()==accPass){
            mLock.leaveReader();
    
            return PASSWORD_CURR;
        }
        else{
            throw (-1);
        }
    }
    catch(...)
    {
        mLock.leaveReader();

        return PASSWORD_ERR;
    }
}

Message Bank::deleteAccount(const int accId, int *amount_getter){
    mLock.enterWriter();
    auto it = account_map.find(accId);
    *amount_getter = it->second.balanceGetter();
    it->second.~Account();
    account_map.erase(it);
    mLock.leaveWriter();
    return ACCOUNT_DELETED;
}

Message Bank::transfer(const int sourceId, const int sourcePass,
const int targetId, const int amount, int *amount_getter){
    mLock.enterWriter();
    auto itSource = account_map.find(sourceId);
    auto itTarget = account_map.find(targetId);
    int sourceBalance = itSource->second.balanceGetter();
    if(sourceBalance < amount){
        mLock.leaveWriter();
        return INSUFFICIANT_FUNDS;
    }
    itSource->second.balanceSetter(amount,WITHDRAW);
    itTarget->second.balanceSetter(amount,DEPOSIT);
    *amount_getter = itTarget->second.balanceGetter();
    mLock.leaveWriter();
    return TRANSFER_SUCCESS;
}

void Bank::collectCommission(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(3,5);
    int commission = distr(gen);
    int arbitrary_amount = -1;
    int *amount_getter = &arbitrary_amount;
    // mLock.enterReader();
    // pthread_mutex_lock(&commissionLock);
    // bankLeaveWriter();
    for(auto account : account_map){
        int desired_amnt = commission * 0.01 * account.second.balanceGetter();
        //int curr_amnt = account.second.balanceGetter();
        // int withdraw_amnt = curr_amnt-desired_amnt;
        int acc_id = account.first;
        // pthread_mutex_lock(&commissionLock);

        if(withDrawMoney(acc_id,desired_amnt,amount_getter)!=WITHDREW_MONEY){

            // pthread_mutex_unlock(&commissionLock);

            // sleep(1);
            // bankLeaveWriter();
            commissionPrinter(FAILED_COLLECTING_COMMISSION, amount_getter,
            commission,acc_id,desired_amnt);
            // mLock.leaveWriter();
        }
        else{
            // pthread_mutex_lock(&commissionLock);
            // bankEnterWriter();
            this->bankBalance += desired_amnt;
            // pthread_mutex_unlock(&commissionLock);
            // bankEnterWriter();
            commissionPrinter(COMMISSION_COLLECTED,amount_getter,
            commission,acc_id, desired_amnt);
        }
    }
    // pthread_mutex_unlock(&commissionLock);
    // sleep(1);
    // mLock.leaveReader();
    // bankLeaveWriter();
    //Here I need to call the commissionPrinter with the COLLECTED_COMMISSION
    //Message
}
//REMEMBER TO CREATE AN ACCOUNT FOR THE BANKJ
void Bank::commissionPrinter(Message message, int* ammount_getter,
int commission, int acc_id, int desired_amnt){
    stringstream lineToPrint;
    switch (message)
    {
    case FAILED_COLLECTING_COMMISSION:
        lineToPrint << "Failed collecting commision from user "<< acc_id;
        break;
    
    case COMMISSION_COLLECTED:
        lineToPrint << "Bank: comissions of " << commission <<
         " % were charged, the bank gained " << desired_amnt <<
          " $ from account " << acc_id ;
        break;
    default:
        break;
    }
    this->bankLog.writeStream(lineToPrint);
}

void Bank::printSnapshot(){
    // cout<<"hello world"<<endl;
    stringstream lineToPrint;
    cout<<("\033[2J");
    cout<<("\033[1;H");
    lineToPrint << "Current Bank Status"<<endl;
    mLock.enterReader();
    for(auto account : account_map){
        int acc_id  = account.first;
        int acc_balance = account.second.balanceGetter();
        int acc_pass = account.second.passwordGetter();
        lineToPrint << "Account " << acc_id << ": Balance - " << acc_balance<<
        " $ , Account Password - " << acc_pass << endl;
    }
    mLock.leaveReader();
    // pthread_mutex_lock(&commissionLock);
    bankEnterWriter();
    lineToPrint << "The Bank has " << this->bankBalance << " $";
    // pthread_mutex_unlock(&commissionLock);
    // bankLeaveWriter();
    // sleep(1);
    // pthread_mutex_lock(&printLock);
    cout << lineToPrint.str();
    // pthread_mutex_unlock(&printLock);
    bankLeaveWriter();
    // sleep(1);
}

Log& Bank::logGetter(){
    return this->bankLog;
}


void Bank::bankEnterReader(){
    mLock.enterReader();
}

void Bank::bankLeaveReader(){
    mLock.leaveReader();
}

void Bank::bankEnterWriter(){
    mLock.enterWriter();
}

void Bank::bankLeaveWriter(){
    mLock.leaveWriter();
}