#include "Serv_cli_fifo.h"
#include "Handlers_Cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int main() {
    // Déclarations des variables et des tubes nommés ici
    int fd_fifo1, fd_fifo2;
    
    // Création des tubes nommés fifo1 et fifo2 (s'ils n'existent pas déjà)
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);
    
    // Ouverture des tubes nommés fifo1 et fifo2
    fd_fifo1 = open(FIFO1, O_WRONLY);  // Ouvrir en mode écriture
    fd_fifo2 = open(FIFO2, O_RDONLY);  // Ouvrir en mode lecture
    
    // Installation des Handlers pour SIGUSR1 et d'autres signaux si nécessaire
    signal(SIGUSR1, hand_reveil);
    
    // Construction et envoi d'une question au serveur
    struct Question question;
    question.clientID = getpid(); // PID du client
    question.n = rand() % NMAX + 1; // Génère un nombre aléatoire n
    
    // Envoi de la question au serveur via le tube nommé fifo1
    write(fd_fifo1, &question, sizeof(question));
    
    // Attente de la réponse du serveur (taille du tableau d'abord)
    int responseSize;
    if (read(fd_fifo2, &responseSize, sizeof(int)) == -1) {
        perror("Erreur lors de la lecture de la taille de la réponse");
        close(fd_fifo1);
        close(fd_fifo2);
        exit(EXIT_FAILURE);
    }
    
    // Allocation dynamique de mémoire pour stocker les réponses
    int* reponseNumeros = malloc(sizeof(int) * responseSize);
    if (reponseNumeros == NULL) {
        perror("Erreur lors de l'allocation mémoire pour les réponses");
        close(fd_fifo1);
        close(fd_fifo2);
        exit(EXIT_FAILURE);
    }

    // Lecture des réponses depuis le tube nommé fifo2
    if (read(fd_fifo2, reponseNumeros, sizeof(int) * responseSize) == -1) {
        perror("Erreur lors de la lecture des réponses");
        free(reponseNumeros);
        close(fd_fifo1);
        close(fd_fifo2);
        exit(EXIT_FAILURE);
    }

    // Affichage des réponses
    printf("Réponse reçue du serveur (client ID: %d, taille du tableau: %d):\n", question.clientID, responseSize);
    for (int i = 0; i < responseSize; ++i) {
        printf("%d ", reponseNumeros[i]);
    }
    printf("\n");

    // Libération de la mémoire allouée dynamiquement et fermeture des tubes nommés
    free(reponseNumeros);
    close(fd_fifo1);
    close(fd_fifo2);
    
    // Envoi du signal SIGUSR1 au serveur (peut être utilisé pour d'autres traitements)
    kill(getpid(), SIGUSR1);
    
    return 0;
}
