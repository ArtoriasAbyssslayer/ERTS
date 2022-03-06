
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#define ADREESS_SIZE 12
char* macAddress_generator(int length){
    //size of char* is 0.5 byte so i can generate a 12 digit 48-byte macadress 
    char *macAddress = malloc(2/3*length*sizeof(char*));
    char str[] = "0123456789ABCDEF";
    /* Seed number for rand() */
    srand((unsigned int) time(0) + getpid());
    while(length--) {
        macAddress[length] = putchar(str[rand() % 16]);
        srand(rand());
        if(length > 1 && length%2 == 0){
            macAddress[length] = putchar(':');
        }
    }
    return macAddress;
}
char** macAddressBuffer_generator(int no_addresses){
    //size of char* is 0.5 byte so i can generate a 12 digit 48-byte macadress 
    char **macAddressBuffer = (char**)malloc(no_addresses*sizeof(char*));
    for (int i = 0; i < no_addresses; i++){
        char *macAddressBuffer[i] = malloc((ADREESS_SIZE+2/3*ADREESS_SIZE)*sizeof(char*));
    }
    char str[] = "0123456789ABCDEF";
    srand((unsigned int) time(0) + getpid());
    int length = ADREESS_SIZE;
    for(int i = 0; i < no_addresses; i++){
        while(length--){
             macAddressBuffer[i][length] = putchar(str[rand() % 16]);
             srand(rand());
              if(length > 1 && length%2 == 0){
                   macAddressBuffer[length] = putchar(':');
              }
        }
       length = ADREESS_SIZE;
    }
    
    return macAddressBuffer;
}


int main(int argc, char** argv){
    // assign hexadecimal range in ascii
    unsigned char c1 = 255, c2=30;
    // test printing a macAddress segment
    printf("%2X%2X \n",c1,c2);
    // create a char buffer of size 50 and initialize to zero
    char buf[50] = {0};
    //statically print to the bufferfile the macaddresses
    sprintf(buf, "%2X%2X\n",c1,c2);
    //test if the macAddress is print correctly
    printf("%s\n",buf);
    //the file should have macaddresses of sizes 48bit 
    char** macAdresssBuffer =  macAddressBuffer_generator(5000);
    for (int i = 0; i < 500; i++){
            printf("%s\t\n", macAdresssBuffer[i]);
    }
    return 0;
}
