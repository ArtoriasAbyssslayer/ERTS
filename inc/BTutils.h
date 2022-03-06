/* BTutils.h*/
#ifndef __BT_UTILS_H_
#define __BT_UTILS_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define NUMBER_OF_ADRESSES 5000
#define ADRRESS_BYTE_LENGTH 12   // char* is 4/8bytes => 6 bytes = 48bits per address

char** macAddressBuffer_generator(int length, int no_addresses){
    //size of char* is 0.5 byte so i can generate a 12 digit 48-byte macadress 
    //length_extend computes the length of the address with the delimmiter : 
    length_ext = length + length/3;
    char **macAddressBuffer = (char **)malloc(no_addresses*sizeof(char*));
    for(int i=0; i < number_of_adresses; i++){
        macAddressBuffer[i] =(char *)malloc(*length*sizeof(char*));
    }
    char str[] = "0123456789ABCDEF";
    /* Seed number for rand() */
    srand((unsigned int) time(0) + getpid());
    for(int i=0; i < number_of_adresses; i++){
      for(int length = 0; i < length; i++){
            // put a random number from buffer str to macAddressBuffer
            // This done for testing purposes : macAddressBuffer[i][length] = putchar(str[rand() % 16]);
            macAddressBuffer[i][length] = str[rand() % 16];
            srand(rand());
            if(length > 1 && (length+1)%3 == 0){
               // macAddressBuffer[i][length] = putchar(':');
               macAddressBuffer[i][length] = ':'
            }
        }
    }
    return macaddressBuffer;
}

bool isSameMac(char *mac1, char *mac2){
  for(int i=0; i < ADRRESS_BYTE_LENGTH; i++){
    if(mac1[i] == mac2[i])
      return false;
  }else{
    return true;
  }
}

double time_interval(struct timeval start, struct timeval end){
  //do this timeval postprocessing in order to get right time-intervals
  double time_passed = ((double)(end.tv_sec - start.tv_sec)) / (double)(end.tv_usec - start)*1000 + ((double)(end.tv_usec - start.tv_usec)/1000);
  time_passed = time_passed*SPEEDUP;
}
#endif /*BT_UTILS_H*/