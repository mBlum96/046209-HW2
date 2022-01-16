#ifndef _GLOBAL_H
#define _GLOBAL_H

/*-----------------------------------------------------------------------------
        Libraries:
-----------------------------------------------------------------------------*/
//Data Structures:
#include <string>
#include <cstring>
#include <unordered_map>
#include <list>

//Streams:
#include <iostream>
#include <fstream>
#include <sstream>

//locks:
#include "pthread.h"
#include "semaphore.h"

//time:
#include <unistd.h>

//rando,:
#include <random>

/*-----------------------------------------------------------------------------
        Typedef:
-----------------------------------------------------------------------------*/
using std::string;
using std::cout;
using std::endl;
using std::strlen;
using std::ofstream;
using std::stringstream;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::list;

typedef enum Message{
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
    TARGET_DOESNT_EXIST,
    FAILED_COLLECTING_COMMISSION,
    COMMISSION_COLLECTED
}Message;

typedef enum Action{
        WITHDRAW,
        DEPOSIT
}Action;

typedef enum Times{
        BANK_UPDATE_INTERVAL = 500000
}Times;

typedef enum Boolean{
        TRUE = 1,
        FALSE = 0
}Boolean;

#endif