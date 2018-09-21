#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <vector>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
using namespace std;

#define TOTAL_REGISTERS 1000 
#define STRING_SIZE 1024 
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
char cadena[STRING_SIZE];
Segmento *data;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    char cadena[STRING_SIZE];
    key_t key = 5646;
    int shmid;
    int mode;
    /* Crear el segmento */
    if ((shmid = shmget(key, sizeof(struct Segmento), 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    
    data = (Segmento *)shmat(shmid, NULL, 0);
    if (data == (Segmento *)(-1)) {
        perror("shmat");
        exit(1);
    }
    
    int i=0;
    char nombres[10][50]={"Jordi","Oscar","Alexy","Juan","Andrea","Stephanie","Maria","Marcela","Andres","Gabriela"};

    sem_init(&(data->sem), 0, 1);
    //"Nombre del Cliente: "<<data->nombre_cliente[i]<<
    while(i < 10){
        sem_wait(&(data->sem));
        int opcion=  (rand() % 2) + 1;
        if(opcion==1){
            cout<<"Escribiendo Orden" <<endl;
                //agregar numero de orden
            data->num_orden[i]=i;
                //agregar mes
            int mes = (rand() % 12) + 1;
            data->mes[i]=mes;
            if(mes==1||mes==3||mes==5||mes==7||mes==9||mes==11){
                //agregar dia si el mes tiene 31 dias
                int dia= (rand() % 31) + 1;
                data-> dia[i]=dia;
            }else if(mes==2){
                //agregar dia si es febrero
                int dia= (rand() % 29) + 1;
                data-> dia[i]=dia;
            }else{
                //agregar dia si el mes tiene 30 dias
                int dia= (rand() % 30) + 1;
                data-> dia[i]=dia;
            }
                //agregar año
            int ano = rand()%(2018-2010 + 1) + 2010;
            data->ano[i]=ano;
                // agregar cantidad de productos
            int cantidad_productos=(rand() % 20) + 1;
            data->cantidad_productos[i]=cantidad_productos;
                //agregar total de la orden
            double total= (double)rand()/(RAND_MAX + 1)+300+(rand()%300);
            data->total_orden[i]=total;
                // agregar nombre del cliente        
            int nom=(rand() % 10) + 0;                
            
            strcpy(data->nombre_cliente[i], (nombres[nom]));
            cout<<i<<endl;                 
            cout<<"Nombre del Cliente: "<<data->nombre_cliente[i]<<" Numero de Orden: "<<data->num_orden[i]<<" Dia de la orden: "<< data->dia[i]<<" Mes:"<< data->mes[i]<< " Año: "<<data->ano[i]<< " Cantidad de Productos: "<<data->cantidad_productos[i]<< " Cantidad de Productos: "<< data->cantidad_productos[i]<< " Total: "<< data->total_orden[i] << endl;
            cout<<"*************************************************"<<endl;

            i++;
        }else{
            cout<<"Eliminar"<<endl;
        }
        sem_post(&(data->sem));
        sleep(6);
    }
    // for (int i = 0; i < 10; ++i)
    // {

    //     cout<< "Numero de Orden: "<<data->num_orden[i]<<" Dia de la orden: "<< data->dia[i]<<" Mes:"<< data->mes[i]<< endl;
    // }
    
    // while(true){
    //     data->clienteFlag=true;
    //     while(data->clienteFlag);
    //     cout<< data->mensaje <<endl;
    //     cout<< ":>" <<endl;
    //     cin.getline(cadena,STRING_SIZE);
    //     strcpy(data->mensaje, cadena);        
    //     data->servidorFLag=false;

    //}  
    /*
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    */
    return 0;
}

