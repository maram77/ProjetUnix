#include "Handlers_Serv.h"
#include "Serv_cli_fifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

struct Question latestQuestion; // Define the global variable to store the latest question

void hand_reveil(int sig) {
    int fd;
    struct Reponse reponse;
    reponse.clientID = latestQuestion.clientID;

    // La première valeur dans le tableau est la taille du tableau
    reponse.numeros[0] = latestQuestion.n;

    // Générer des nombres aléatoires pour les valeurs
    for (int i = 1; i < latestQuestion.n; ++i) {
        reponse.numeros[i] = rand() % NMAX + 1;
    }

    // Ouvrir le tube nommé fifo2 en mode écriture
    fd = open(FIFO2, O_WRONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du tube nommé fifo2");
        exit(EXIT_FAILURE);
    }

    // Écrire la réponse dans le tube nommé fifo2
    if (write(fd, &reponse, sizeof(struct Reponse)) == -1) {
        perror("Erreur lors de l'écriture dans le tube nommé fifo2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Fermer le tube nommé fifo2 après l'écriture
    close(fd);
    
    printf("Le serveur a répondu avec les nombres aléatoires générés.\n");
}


void fin_serveur(int sig) {
    // Fermeture des tubes nommés et nettoyage des ressources avant de quitter le serveur
    int fd_fifo1, fd_fifo2;

    // Fermeture du tube nommé fifo1
    fd_fifo1 = open(FIFO1, O_WRONLY);  // Ouvrir en mode écriture pour débloquer d'éventuelles attentes en écriture
    close(fd_fifo1);

    // Fermeture du tube nommé fifo2
    fd_fifo2 = open(FIFO2, O_WRONLY);  // Ouvrir en mode écriture pour débloquer d'éventuelles attentes en écriture
    close(fd_fifo2);

    printf("Le serveur se termine suite à la réception d'un signal.\n");

    // Nettoyage et fermeture d'autres ressources si nécessaire...

    exit(EXIT_SUCCESS); // Terminez le serveur proprement
}
