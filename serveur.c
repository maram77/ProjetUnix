#include "Serv_cli_fifo.h"
#include "Handlers_Serv.h"
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
    
    // Initialisation du générateur de nombres aléatoires
    srand(getpid());
    
    // Ouverture des tubes nommés fifo1 et fifo2
    fd_fifo1 = open(FIFO1, O_RDONLY);  // Ouvrir en mode lecture
    fd_fifo2 = open(FIFO2, O_WRONLY);  // Ouvrir en mode écriture
    
    // Installation des Handlers pour SIGUSR1 et d'autres signaux si nécessaire
    signal(SIGUSR1, hand_reveil);
    signal(SIGINT, fin_serveur);

    while(1) {
        // Lecture d'une question depuis le tube nommé fifo1
        int bytesRead = read(fd_fifo1, &latestQuestion, sizeof(struct Question));
        if (bytesRead == -1) {
            perror("Erreur lors de la lecture de la question");
            continue; // Passez à la prochaine itération de la boucle
        }

        // Construction de la réponse
        struct Reponse reponse;
        reponse.clientID = latestQuestion.clientID;

        // Génération des nombres aléatoires pour les valeurs
        for (int i = 0; i < latestQuestion.n; ++i) {
            reponse.numeros[i] = rand() % NMAX + 1;
        }

        // Envoi de la réponse dans le tube nommé fifo2
        int bytesWritten = write(fd_fifo2, &reponse, sizeof(struct Reponse));
        if (bytesWritten == -1) {
            perror("Erreur lors de l'écriture de la réponse");
        }

        // Envoi du signal SIGUSR1 au client concerné (question.clientId)
        kill(latestQuestion.clientID, SIGUSR1);
    }

    // Fermeture des tubes nommés et libération de la mémoire si nécessaire
    close(fd_fifo1);
    close(fd_fifo2);

    return 0;
}







