#ifndef __ATM_H
#define __ATM_H
//includes:
#include "Headers.hpp"
#include "Bank.hpp"
/*-----------------------------------------------------------------------------
        Auxiliary stractures
-----------------------------------------------------------------------------*/        
/*struct ATM_params{
    int atm_id;
};*/
/*-----------------------------------------------------------------------------
        Class declaration
-----------------------------------------------------------------------------*/
class ATM{
private:
    int atmId;
    Bank &bank;
    string atmFile;
public:
    // int atmId;
    // string atmFile;
    ATM(int atmId, Bank &bank, string atmFile);
    ~ATM();
    void print_welcome_message();
    void run();
    Message executeLine(char* line_input);
    void welcome();
    void printer(Message printMsg, char* args[], int *amount_getter);

};

#endif