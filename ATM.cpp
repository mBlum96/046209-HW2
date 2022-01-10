//includes:
#include "ATM.hpp"
#include "Bank.hpp"
#include "Log.hpp"

#define MAX_LINE_SIZE 0//to be determined
#define MAX_ARGS 0//to be determined



ATM::ATM(int atmId, Bank &bank):atmId(atmId), bank(bank){

}

void ATM::welcome(){
    cout<<"*******************************************************************"
    <<endl;
    cout << "** Welcome to Technion Bank ATM **"<<endl;
    cout<<"*******************************************************************"
    <<endl;
    cout<< "To open a new account, enter 'O' followed by:"<<endl;
    cout<< "<account_id> <password> <initial_amount>" << endl;
    cout<<"*******************************************************************"
    <<endl;
    cout << "To deposit money into the account, enter 'D' followed by:"<<endl;
    cout << "<account_id> <password> <depossit_amount>" << endl;
    cout<<"*******************************************************************"
    <<endl;
    cout << "To withdraw money from the account, enter 'W' followed by:"<<endl;
    cout << "<account_id> <password> <withdraw_amount>"<<endl;
    cout<<"*******************************************************************"
    <<endl;
    cout << "To check the accounts balance, enter 'B' followed by:"<<endl;
    cout << "<account_id> <password>" << endl;
    cout<<"*******************************************************************"
    <<endl;
    cout << "To close an account, enter 'Q' followed by:"<<endl;
    cout << "<account_id> <password>";
    cout<<"*******************************************************************"
    <<endl;
    cout << "To transfer money to another bank account, enter 'T' followed by:"
    <<endl;
    cout << "<account> <password> <target_account> <amount_to_transfer>"<<endl;
    cout<<"*******************************************************************"
    <<endl;
}

void ATM::run(int argc, char* argv[]){
    char line_input[MAX_LINE_SIZE];
    /*char cmd_string[strlen(line_input)-1]={'\0'};*/
    while(1){
        cout << "> ";
        fgets(line_input, MAX_LINE_SIZE, stdin);

        Message printMsg = this->executeLine(line_input);

        line_input[0] = '\0'; //initialized for next line read
    }
}

Message ATM::executeLine(char* line_input/*, char* cmd_stirng*/){
    int num_args = 0;
    char* cmd;
    char* args[MAX_ARGS];
    char delimmiters[4] = " \t\n";
    int *amount_getter;
    string delimitered_command = {'\0'};
    cmd = strtok(line_input, delimmiters);
    /*if(cmd==NULL){
        return 0;
    }*/
    args[0] = cmd;
    for(int i=1; i<MAX_ARGS;i++){
        args[i] = strtok(NULL, delimmiters);//passing NULL to strtok tells it
        //to continue working on the last string supplied
        if(args[i] != NULL){
            num_args++;
            delimitered_command.append(args[i]);
        }
    }
    int accId = atoi(args[1]);
    int accPass = atoi(args[2]);
    Message accountExistance = bank.doesAccountExist(accId);
    if(!strcmp(cmd,"O")||!strcmp(cmd,"D")||!strcmp(cmd,"W")){
        int amount = atoi(args[3]);
        if(!strcmp(cmd,"O")){
            if(accountExistance==ACC_DOESNT_EXIST){
                Message retMsg = bank.openAccount(accId,accPass,amount);
                this->printer(retMsg,args,amount_getter);
                return SUCCESS;
            }
            return FAILED_OPENING_ACC;
        }
        else if(!strcmp(cmd,"W")||!strcmp(cmd,"D")){
            if(accountExistance == ACC_EXISTS){
                Message passCheckRes = bank.checkPass(accId,accPass);
                if(passCheckRes == PASSWORD_CURR){
                    if(!strcmp(cmd,"W")){
                        Message retMsg = bank.withDrawMoney
                        (accId,amount,amount_getter);
                        this->printer(retMsg, args, amount_getter);
                    }
                    else{
                        Message retMsg = 
                        bank.depositMoney(accId,amount,amount_getter);
                        this->printer(retMsg,args,amount_getter);
                    }
                }
                else{
                    this->printer(passCheckRes, args, amount_getter);
                }
            }
        }
    }
    else if(!strcmp(cmd,"B")){
        if(accountExistance == ACC_EXISTS){
            Message passCheckRes = bank.checkPass(accId,accPass);
            if(passCheckRes==PASSWORD_CURR){
                int *balanceAmount;
                *balanceAmount = bank.checkAccountBalance(accId);
                this->printer(BALANCE,args,balanceAmount);
            }
            else{
                this->printer(passCheckRes, args, amount_getter);
            }
        }
    }
    else if(!strcmp(cmd,"Q")){
        if(accountExistance == ACC_EXISTS){
            Message passCheckRes = bank.checkPass(accId,accPass);
            if(passCheckRes == PASSWORD_CURR){
                Message retMsg = bank.deleteAccount(accId,amount_getter);
                this->printer(retMsg,args,amount_getter);
            }
            else{
                this->printer(passCheckRes,args,amount_getter);
            }
        }
    }
    else if(!strcmp(cmd,"T")){
        int targetId = atoi(args[3]);
        int amount = atoi(args[4]);
        Message targetExists = bank.doesAccountExist(targetId);
        if(accountExistance!=ACC_EXISTS){
            return ACC_DOESNT_EXIST;
        }
        else if(targetExists==ACC_EXISTS){

        }
        else{
            return TARGET_DOESNT_EXIST;
        }
    }
    return SUCCESS;
}

void ATM::printer(Message printMsg, char* args[],int *amount_getter){
    stringstream lineToPrint;
    switch (printMsg)
    {
    case FAILED_OPENING_ACC:
        lineToPrint << "Error " << this->atmId << ": Your transaction failed "
        <<"- account with the same id existss";
        break;
    case CREATED_NEW_ACC:
        lineToPrint << this->atmId << ": New account id is " << args[1]
        <<"with password " << args[2] << " and initial balance " << args[3];
        break;
    case WITHDREW_MONEY:
        lineToPrint << this->atmId << ": Account " << args[1] <<
        " new balance is " << amount_getter << " after "
        << args[3] << " $ was withdrew";
        break;
    case INSUFFICIANT_FUNDS:
        lineToPrint <<"Error "<<this->atmId <<
        ": Your transaction failed - account id"<<args[1]
        << "balance is lower than " << args[3];
        break;
    case PASSWORD_ERR:
        lineToPrint << "Error" << this->atmId<<": Your transaction failed - "
        << "password for account id" << args[1] << "is incorrect";
        break;
    case DEPOSITED_MONEY:
        lineToPrint << this->atmId << ":Account " << args[1] << "new balance"<<
        "is " << amount_getter << " after " << args[3] << " $ was deposited";
        break;
    case BALANCE:
        lineToPrint << ": Account " << args[1] << " balance is " 
        << amount_getter;
        break;
    case ACCOUNT_DELETED:
        lineToPrint<<this->atmId<<": Account "<<args[1] << " is now closed"<<
        " balance was " << amount_getter;
    default:
        break;
    }
}