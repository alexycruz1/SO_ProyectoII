#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
using namespace std;

#define STRING_SIZE 1024
struct Segmento {
     bool serverFlag;
     bool clientFlag;
     char mensaje[STRING_SIZE];
};

int main(int argc, char *argv[])
{
    char cadena[STRING_SIZE];
    key_t key = 7851;
    int shmid;
    Segmento *data;
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
    while (true) {
        data->clientFlag = true;
        while (data->clientFlag); // spinlock
        cout << data->mensaje << endl;
        cout << ":>";
        cin.getline(cadena,STRING_SIZE);
        strcpy(data->mensaje, cadena);
        data->serverFlag = false;
    }
    /*
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    */
    return 0;
}