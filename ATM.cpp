//includes:
#include "ATM.hpp"
#include "Bank.hpp"

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

        this->executeLine(line_input);
        line_input[0] = '\0'; //initialized for next line read
    }
}

Message ATM::executeLine(char* line_input/*, char* cmd_stirng*/){
    int num_args = 0;
    char* cmd;
    char* args[MAX_ARGS];
    char delimmiters[4] = " \t\n";
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
    if(!strcmp(cmd,"O")){
        int accId = atoi(args[1]);
        int accPass = atoi(args[2]);
        float initAmount = atof(args[3]);
        if(bank.doesAccountExist()==ACC_DOESNT_EXIST){
            return bank.openAccount(accId,accPass, initAmount);
        }
        return FAILED_OPENING_ACC;
    }
    return SUCCESS;
}