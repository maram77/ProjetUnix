#include "Serv_cli_fifo.h"
#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H


 extern struct Question latestQuestion; // Declare a global variable to store the latest question
 
// Déclaration du handler pour le réveil du serveur suite à la réception du signal SIGUSR1
// serveur chnowa ya3mel 

void hand_reveil(int sig);

// Déclaration du handler pour la fin du serveur suite à la réception de n'importe quel signal
void fin_serveur(int sig);

#endif