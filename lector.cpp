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
#include <map> 
#include <iterator> 

using namespace std;

#define TOTAL_REGISTERS 1000
struct Segmento{
    sem_t sem;
    sem_t sem2;

    int numLec = 0;

    int num_orden[TOTAL_REGISTERS];
    int cantidad_productos[TOTAL_REGISTERS];
    double total_orden[TOTAL_REGISTERS];
    int dia[TOTAL_REGISTERS];
    int mes[TOTAL_REGISTERS];
    int ano[TOTAL_REGISTERS];
    char nombre_cliente[TOTAL_REGISTERS][50];

    int i = 0;
};
    Segmento *data;
    
int main(int argc, char *argv[]){

    srand(time(NULL));
    
    key_t key = 5643;
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
    char nombres[10][50]={"Jordi","Oscar","Alexy","Juan","Andrea","Stephanie","Maria","Marcela","Andres","Gabriela"};

    sem_init(&(data->sem), 0, 1);
    sem_init(&(data->sem2), 0, 1);
    while(true) {
        sem_wait(&(data->sem2));
        if((data->numLec == 0) || (data->numLec == 10)) {
            sem_wait(&(data->sem));
        }

        data->numLec++;
        sem_post(&(data->sem2));
        
        int opcion =  (rand() % 4) + 1;
        if(opcion == 1) {
            //Imprimir ordenes por año
            int regTempYear[data->i];
            int regTempIndex[data->i];

            int j = 0;
            for(j = 0; j < data->i; j++) {
                regTempYear[j] = data->ano[j];
                regTempIndex[j] = j;
            }

            for(j = 0; j < data->i - 1; j++) {
                for(int k = 0; k < data->i - j - 1; k++) {
                    if((regTempYear[k]) > (regTempYear[k + 1])) {
                        int temp = regTempYear[k];
                        int tempIndex = regTempIndex[k];

                        regTempYear[k] = regTempYear[k + 1];
                        regTempYear[k + 1] = temp;

                        regTempIndex[k] = regTempIndex[k + 1];
                        regTempIndex[k + 1] = tempIndex;
                    }
                }
            }

            for(j = 0; j < data->i; j++) {
                if(data->num_orden[regTempIndex[j]] != -1) {
                    cout << "Nombre de la orden: "<< data->nombre_cliente[regTempIndex[j]] <<" Numero de Orden: "<<data->num_orden[regTempIndex[j]]<<" Dia de la orden: "<< data->dia[regTempIndex[j]]<<" Mes:"<< data->mes[regTempIndex[j]]<< " Año: "<<data->ano[regTempIndex[j]]<< " Cantidad de Productos: "<<data->cantidad_productos[regTempIndex[j]]<< " Cantidad de Productos: "<< data->cantidad_productos[regTempIndex[j]]<< " Total: "<< data->total_orden[regTempIndex[j]] << endl;
                    cout <<"*************************************************"<<endl;
                    cout << endl;
                }
            }
        } else if (opcion == 2) {
            //Imprimir todas las ordenes
            for(int j = 0; j < data->i; j++) {
                if((data->num_orden[j] != -1)) {
                    cout << "Nombre de la orden: "<< data->nombre_cliente[j] <<" Numero de Orden: "<<data->num_orden[j]<<" Dia de la orden: "<< data->dia[j]<<" Mes:"<< data->mes[j]<< " Año: "<<data->ano[j]<< " Cantidad de Productos: "<<data->cantidad_productos[j]<< " Cantidad de Productos: "<< data->cantidad_productos[j]<< " Total: "<< data->total_orden[j] << endl;
                    cout <<"*************************************************"<<endl;
                    cout << endl;
                } 
            }
        } else if (opcion == 3) {
            //Calcular total de ordenes
            double total = 0;

            for(int j = 0; j < data->i; j++) {
                if(data->num_orden[j] != -1) {
                    total += data->total_orden[j];
                }
            }

            cout << "El total de las ordenes es: " << total << endl;
            cout <<"*************************************************"<<endl;
            cout << endl;
        } else {
            //Imprimir ordenes de un cliente
            int cliente = (rand() % 10) + 0;
            cout << "El cliente " << nombres[cliente] << " tiene las siguientes ordenes: " << endl << endl;
            for(int j = 0; j < data->i; j++) {
                if((strcmp(data->nombre_cliente[j], nombres[cliente]) == 0) && (data->num_orden[j] != -1)) {
                    cout << "Nombre de la orden: "<< data->nombre_cliente[j] <<" Numero de Orden: "<<data->num_orden[j]<<" Dia de la orden: "<< data->dia[j]<<" Mes:"<< data->mes[j]<< " Año: "<<data->ano[j]<< " Cantidad de Productos: "<<data->cantidad_productos[j]<< " Cantidad de Productos: "<< data->cantidad_productos[j]<< " Total: "<< data->total_orden[j] << endl;
                    cout <<"*************************************************"<<endl;
                    cout << endl;
                }
            }
        }
        i++;

        sem_wait(&(data->sem2));
        data->numLec--;

        if((data->numLec == 0) || (data->numLec == 10)) {
            sem_post(&(data->sem));
        }

        sem_post(&(data->sem2));
        sleep(1);
    }
    return 0;
}
