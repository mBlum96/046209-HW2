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

//locks:
#include "pthread.h"

/*-----------------------------------------------------------------------------
        Typedef:
-----------------------------------------------------------------------------*/
using std::string;
using std::cout;
using std::endl;
using std::strlen;

typedef enum{
    SUCCESS,
    PASSWORD_ERR,
    AMOUNT_ERR,
    ACC_EXISTS,
    ACC_DOESNT_EXIST,
    FAILED_OPENING_ACC,
    INITIAL_AMOUNT_ERR
}Message;


#endif