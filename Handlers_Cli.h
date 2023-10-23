#include "Serv_cli_fifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

// Déclaration du handler pour le réveil du client suite à la réception du signal SIGUSR1
void hand_reveil(int sig);

#endif
