#include <stdio.h>
#include "../inc/BTutils.h"
#include <stdlib.h>
#include "../inc/covidTrace.h"
#include <sys/types.h> //nedded for getpid()
#include <unistd.h> //needed for getpid()
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_cond_t 
/***Pipelined Covid-Trace-Test RPI4 ****/
#define SPEEDUP 1000
#define SUBPROCESSES 5
/* global viariables */

void *eventTimer(void *arg){
    gettimeofday(&)
}
int main(int argc, char** argv){
    /* Simulation of MAC addresses collect 
     * Case: Random Generated in file
     */
     FILE *file_p = fopen("MAC_addrs.txt","r");

     for(int i = 0; i<ADDRESSES_NUM; i++){
         for(int j = 0; j < CHARS; j++){
             fscanf(file_p,"%c",&addresses[i][j]);
         }
     }
     fclose(file_p);

    int num_of_workers = SUBPROCESSES;

    /* generate 5 subprocesses with 5 threads for the task 
       The number of subprocesses are 4 based on that I have 4 seperate tasks in the pipeline : CovidTracing,CovidTest,UploadContacts,ClearNonUploadedContacts (4)
       So I need 5parallelThreads to do each task. In order to lapse the time of the experiment i use a speedup=1000 for 1000times timelapsing
        The below numbers are for the program to change state so i can stop the experiment in 7 hours (this works better with signals and not delays)
            This means that every thread should run a task so we could make BT_NEAR_me_Search every 202/10 minutes (based on the fact that the program runs 1000 times faster)
            10secs -> 10/1000
            4minutes => 0.04/10 minutes or 0.24s
            20minutes => 0.2/10 minutes or 1.2secs
            4hours => 0.004hours or 14.4secs - Covid Test
            The event driven functions are only triggered by time passage so i need to specify the correct intervals. Also need a thread to calculate the time passage
            so 5 threads are needed.
    */

    
    // allocate memory for pthreads 

    pthread_t *threads = (pthread_t*) malloc(SUBPROCESSES*num_of_workers*sizeof(pthread_t));

    /* create a thread/subprocess to time the whole experiment and stop it */
    // eventTimer callback starts and stops the timer 
    if(pthread_create(&threads[0],NULL,&eventTimer,NULL)){
        printf("Error creating eventTimer thread");
        return 1;
    }
    if(pthread_create(&threads[1],NULL,,BTnearMe,NULL)){
        printf("Main BTSearch thread failed while creation!");
        return 1;
    }
    //Create thread for covidTracing returning macAddress
    if(pthread_create(&threads[2],nullp))
    // example : pthread_create(&threads[1],NULL,BTnearMe,m);
    //Create Thread to perform a covid test with
    //Create Thread to clear all close uploadContacts
    //Create Thread to upload all possible contacts 

    // pthread_join
    for(int i = 0; i < num_of_workers; i++)
        pthread_join(threads[i],NULL);
    }



    printf("Hello Dump!");
}
