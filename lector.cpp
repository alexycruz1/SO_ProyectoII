#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <pthread.h>
#include "Semaphore.h"
using namespace std;

#define STRING_SIZE 1024 
struct Segmento{
    sem_t sem;
    int num_orden[10];
    int cantidad_productos[10];
    double total_orden[10];
    int dia[10];
    int mes[10];
    int ano[10];
    char *nombre_cliente[10];
    
};
    Segmento *data;
    
int main(int argc, char *argv[]){
    
    key_t key = 5646;
    int shmid;
    int mode;
    /* Crear el segmento */
    if ((shmid = shmget(key, sizeof(struct Segmento), 0644)) == -1) {
        perror("shmget");
        exit(1);
    }
    
    // /* Crear el segmento */
    // if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) {
    //     perror("shmget");
    //     exit(1);
    // }

    
    data = (Segmento *)shmat(shmid, NULL, 0);
    if (data == (Segmento *)(-1)) {
        perror("shmat");
        exit(1);
    }
    



    // while(true){
    //     data->clienteFlag=true;
    //     while(data->clienteFlag);
    //     cout<< data->mensaje <<endl;
    //     cout<< ":>" <<endl;
    //     cin.getline(cadena,STRING_SIZE);
    //     strcpy(data->mensaje, cadena);        
    //     data->servidorFLag=false;
        
    // }  
    /*
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    */
    return 0;
