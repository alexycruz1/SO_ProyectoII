#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define TOTAL_REGISTERS 1000
struct Segmento{
    sem_t sem;
    int num_orden[TOTAL_REGISTERS];
    int cantidad_productos[TOTAL_REGISTERS];
    double total_orden[TOTAL_REGISTERS];
    int dia[TOTAL_REGISTERS];
    int mes[TOTAL_REGISTERS];
    int ano[TOTAL_REGISTERS];
    char nombre_cliente[TOTAL_REGISTERS][50];
    
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
    
    data = (Segmento *)shmat(shmid, NULL, 0);
    if (data == (Segmento *)(-1)) {
        perror("shmat");
        exit(1);
    }

    int i = 0;

    sem_init(&(data->sem), 0, 1);
    while(i < 10) {
        sem_wait(&(data->sem));
        
        cout << "Nombre de la orden: "<< data->nombre_cliente[i] <<" Numero de Orden: "<<data->num_orden[i]<<" Dia de la orden: "<< data->dia[i]<<" Mes:"<< data->mes[i]<< " Año: "<<data->ano[i]<< " Cantidad de Productos: "<<data->cantidad_productos[i]<< " Cantidad de Productos: "<< data->cantidad_productos[i]<< " Total: "<< data->total_orden[i] << endl;
        cout <<"*************************************************"<<endl;
        
        i++;

        sem_post(&(data->sem));
        sleep(2);
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
}
