#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define NMAX 100 // Valeur maximale de n (nombre aléatoire)

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

struct Question {
    int clientID; // pid du client
    int n;  // Nombre de valeurs à générer
};

struct Reponse {
    int clientID;
    int numeros[NMAX]; // Tableau de valeurs générées
};

#endif // SERV_CLI_FIFO_H