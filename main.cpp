#include "Headers.hpp"
#include "Bank.hpp"
#include "ATM.hpp"
#include "Log.hpp"
#include "Account.hpp"

int all_atm_handeled;

typedef struct atmData{
    int atmNum;
    Bank &theBank;
    string atmFile;
    atmData(Bank &bank): theBank(bank){}
}atmData;


void* atmStartRoutine(/*void* ATMinput*/void *atmInfo){
    // ATM atm_new = *(ATM*) ATMinput;
    // atm_new.run();
    // pthread_exit(NULL);
    //atmData* info = (atmData*)atmInfo;
    // cout<<"start routine file:"<<info->atmFile<<endl;
    ATM* atm = (ATM*) atmInfo;
    // cout<<"file is:"<<atm->atmFile<<endl;
    atm->run();
    pthread_exit(NULL);
}
void* bankCommissionStartRoutine(void* bankInput){
    Bank &bank = *(Bank*) bankInput;
    while(all_atm_handeled!=TRUE){
        bank.collectCommission();
        sleep(BANK_COMMISSION_INTERVAL);
    }
    pthread_exit(NULL);
}

void* bankPrintStartRoutine(void* printInput){
    Bank &bank = *(Bank*) printInput;
    usleep (BANK_UPDATE_INTERVAL);
    while(all_atm_handeled!=TRUE){
       // cout<<"***************Im here*****************"<<endl;
        usleep (BANK_UPDATE_INTERVAL);
        bank.printSnapshot();
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int numOfAtms = atoi(argv[1]);
    Log log("log.txt");
    // myMutexLock mLock;
    Bank bank(log);
    list<ATM*> atmList;
    all_atm_handeled = FALSE;
    for(int i=0; i<numOfAtms ; i++){
        // cout<<"main atmFile is :"<<argv[i+2]<<endl;
        ATM *newatm= new ATM(i+1,bank,argv[i+2]);
        atmList.push_back(newatm);
        // cout<<"king:"<<newatm->atmFile<<endl;
    }
    // cout<<"the list size is"<<atmList.size()<<endl;
    //pthread_t atmThreads[numOfAtms];
    vector<pthread_t> atmThreads(numOfAtms);
    int i=0;
    for(auto atm : atmList){
        // cout<<"atm id"<<atm->atmId<<endl;
        // cout<<"yeha:"<<atm->atmFile<<endl;
        if(pthread_create(
            &atmThreads[i],NULL,atmStartRoutine, (void*) (atm)) != 0){
            perror("Unable to create atm Thread");
            exit(1);
        }
        i++;
    }

    pthread_t bankPrintThread;

    if(pthread_create(
        &bankPrintThread,NULL,bankPrintStartRoutine,(void*)&bank)!=0){
        perror("failed to create bank print routine");
        exit(1);
    }

    pthread_t commissionThread;

    if(pthread_create(
        &commissionThread,NULL,bankCommissionStartRoutine,(void *)&bank)!=0){
        perror("failed to create commission thread");
        exit(1);
    }
    

    for(auto thread : atmThreads){
        pthread_join(thread, NULL);
    }
    for(auto atm : atmList){
        delete atm;
    }
    all_atm_handeled = TRUE;
    pthread_join(bankPrintThread,NULL);
    pthread_join(commissionThread, NULL);
    bank.printSnapshot();
    return 0;
}