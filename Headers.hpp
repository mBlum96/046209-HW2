#ifndef _GLOBAL_H
#define _GLOBAL_H

/*-----------------------------------------------------------------------------
        Libraries:
-----------------------------------------------------------------------------*/
//Data Structures:
#include <string>
#include <cstring>
#include <unordered_map>

//Streams:
#include <iostream>
#include <fstream>
#include <sstream>

//locks:
#include "pthread.h"

//time:
#include <unistd.h>

/*-----------------------------------------------------------------------------
        Typedef:
-----------------------------------------------------------------------------*/
using std::string;
using std::cout;
using std::endl;
using std::strlen;
using std::ofstream;
using std::stringstream;

typedef enum Messageflags{
    SUCCESS,
    PASSWORD_ERR,
    AMOUNT_ERR,
    ACC_EXISTS,
    ACC_DOESNT_EXIST,
    FAILED_OPENING_ACC,
    INITIAL_AMOUNT_ERR,
    CREATED_NEW_ACC,
    PASSWORD_CURR,
    WITHDREW_MONEY,
    INSUFFICIANT_FUNDS,
    DEPOSITED_MONEY,
    BALANCE,
    ACCOUNT_DELETED,
    TRANSFER_SUCCESS,
    TARGET_DOESNT_EXIST
}Message;

typedef enum Actionflags{
        WITHDRAW,
        DEPOSIT
}Action;

#endif