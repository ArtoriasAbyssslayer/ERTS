#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
// buffer_size is the size of the 
#define BUFFER_SIZE 500
#define LOOP 1000
#define ADDRESS_LENGTH 12
#define SPEEDUP 1000
//mutex initializations
pthread_mutex_t BTSearchmutex,TestCovidmutex, UploadContactsmutex, DeleteContactsmutex;

//race conditions
pthread_mutex_t BTSearchCond,TestCovidcond,UploadContactscond,DeleteContacscond;
/*
  Some defines I do based on producers and consumers task
*/
/*
    macAdresses are 48-bit unsigned numbers
    so we need to create a 48-bit number variable type
    48-bit struct number and its manipulation follows 
    In the particular example i manipulate macaresses as char bytes so the conversion is easier
    The uint48t is not in the stdlib so this could be another implementation 
            
        //---------------------------------------------------------
        typedef uint64_t uint48;
        const uint48 uint48mask = 0xFFFFFFFFFFFFFFFFull; 

        uint48 uint48_get(const uint48 *a48, size_t index) {
          const uint16_t *a16 = (const uint16_t *) a48;
          index *= 3;
          return a16[index] | (uint32_t) a16[index + 1] << 16
                  | (uint64_t) a16[index + 2] << 32;
        }

        void uint48_set(uint48 *a48, size_t index, uint48 value) {
          uint16_t *a16 = (uint16_t *) a48;
          index *= 3;
          a16[index] = (uint16_t) value;
          a16[++index] = (uint16_t) (value >> 16);
          a16[++index] = (uint16_t) (value >> 32);
        }

        uint48 *uint48_new(size_t n) {
          size_t size = n * 3 * sizeof(uint16_t);
          // Insure size allocated is a multiple of `sizeof(uint64_t)`
          // Not fully certain this is needed - but doesn't hurt.
          if (size % sizeof(uint64_t)) {
            size += sizeof(uint64_t) - size % sizeof(uint64_t);
          }
          return malloc(size);
        }
        //---------------------------------------------------------
    
*/

/*
  global variables needed
*/
bool isNearMePositive = false;
bool BTsearchDone = false;
bool TestCovid = false;
bool ContactUploadingDone = false;
bool time_passed = false;


/* addresses buffer wont be dynamically allocated 
 *  because the task prompts us to do so 
 */
char MacAddressesBuffer[ADDRESS_LENGTH][BUFFER_SIZE];
// need a buffer to store timestamps in float (initially think is manageble from rpi)
float BTtestTimestamps[LOOP];

typedef struct MacAddressStructure{
    char macAddress[ADDRESS_LENGTH];   
    bool  isNearMe;
    struct timeval start, end;
    double elapsed;
}macaddress;

// queue model from producers/consumers was implemented here on buffer
typedef struct macAddressBuffer{
  macaddress mac_buffer[BUFFER_SIZE];
  long head,tail;
  int full,empty;
  pthread_mutex_t *mut;
  pthread_mutex_cond_t *notFull,*notEmpty;
}mac_buffer;
/***********************Queue Utility functions for macAdressbuffer*******************/
mac_buffer *mac_bufferInit(void) {
    mac_buffer *q;

    q = (mac_buffer *)malloc(sizeof(mac_buffer));
    if (q == NULL) return (NULL);

    q->prod = producers;
    q->finished_prod = 0;
    q->times = (double *)malloc(producers * LOOP * sizeof(double));
    if (q->times == NULL) {
        printf("Unable to initialize times array.\n");
        exit(-1);
    }
    q->index = 0;

    q->empty = 1;
    q->full = 0;
    q->head = 0;
    q->tail = 0;
    q->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(q->mut, NULL);
    q->notFull = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    pthread_cond_init(q->notFull, NULL);
    q->notEmpty = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    pthread_cond_init(q->notEmpty, NULL);

    return (q);
}

void mac_bufferDelete(mac_buffer *q) {
    free(q->times);
    pthread_mutex_destroy(q->mut);
    free(q->mut);
    pthread_cond_destroy(q->notFull);
    free(q->notFull);
    pthread_cond_destroy(q->notEmpty);
    free(q->notEmpty);
    free(q);
}

void mac_bufferAdd(mac_buffer *q, macaddress in) {
    q->buf[q->tail] = in;
    q->tail++;
    if (q->tail ==BUFFER_SIZE) q->tail = 0;
    if (q->tail == q->head) q->full = 1;
    q->empty = 0;

    return;
}

void mac_bufferDel(mac_buffer *q, macaddress *out) {
    *out = q->buf[q->head];
    gettimeofday(&out->end, NULL);
    out->arg = (void *)out;
    out->work(out->arg);
    q->times[q->index] = out->elapsed;
    q->index++;

    q->head++;
    if (q->head == BUFFER_SIZE) q->head = 0;
    if (q->head == q->tail) q->empty = 1;
    q->full = 0;
    return;
}
/*******************---END OF FIFO QUEUE STUFF--------------************************/

macaddress BTnearMe(){
  srand(time(NULL));
  struct timeval t0,t1,dt;
  gettimeofday(&t0,NULL);
  gettimeofday(&t1,NULL);
  timersub(&t1,%t0,&dt);
  while(true) {
    if(dt.tv_sec >= 10/SPEEDUP){
      //figure out a way to initialize the buffer
      macaddressBuffer = macAddressBuffer_generator(ADDRESS_LENGTH,BUFFER_SIZE);
      //startmeasuring time for getting the mac
      gettimeofday(&macadress.start);
      return macaddressBuffer[rand()%(sizeof(macaddress)+1)];
    }else {
      //measure time interval for macaddress search
      gettimeofday(&t1,NULL);
      timersub(&t1,%t0,&dt);
      //calculate scaled time interval
      time_interval(&t0,&t1);
    }
  }
  
}

bool* testCOVID(void*){
  while(true) {
    //let this run in serial in order not to have interferance with covidTest boolean change (made by other threads)
    pthread_mutex_lock(&TestCovidmutex);
    //stall process until it is mutually excluded 
    while()
        pthread_cond_wait(&TestCovidcond);
    pthread_mutex_unlock(&TestCovidmutex);
  }
  TestCOVID = rand()%2;
}

void* uploadContacts(void *arg){
  //all threads are running in a for loop until threir process is done so they are mutually excluded
   while(true){
     
     pthread_mutex_lock(&UploadContactsmutex);
     while(isNearMePositive == false)
      pthread_cond_wait(&UploadContactscond,&UploadContactsmutex);
     pthread_mutex_unlock(&UploadContactsmutex);
   }
    if(BTnearMe().isNearMe==True)
}

void deleteContacts(macAddressBuffer **buffer){
  mac_buffer *fifo = (mac_buffer *)(mac_buffer->)
  while(true){
    pthread_mutex_lock(&DeleteContactsmutex);
    while(time_passed == true){
      pthread_cond_wait(&DeleteContactscond,&DeleteContactsmutex);
    }
    pthread_mutex_unlock(&DeleteContactsmutex);
    printf("Clearing contacts file\n---------|");

  }
}