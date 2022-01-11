#ifndef __ATM_H
#define __ATM_H
//includes:
#include "Headers.hpp"

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
public:
    ATM(int atmId, Bank &bank);
    ~ATM();
    void print_welcome_message();
    void run(int argc, char* argv[]);
    Message executeLine(char* line_input);
    void welcome();
    void printer(Message printMsg, char* args[], int *amount_getter);

};

#endif