#include "Handlers_Cli.h"
#include "Serv_cli_fifo.h" 

void hand_reveil(int sig) {
    // Code à exécuter lorsque le client est réveillé par le signal SIGUSR1
    printf("Le client a été réveillé par le signal SIGUSR1.\n");

    // Mettez ici le code que vous souhaitez exécuter lorsque le client est réveillé.
    // Par exemple, lire la réponse depuis un tube nommé, effectuer un traitement, etc.
    
    // Exemple de lecture depuis le tube nommé fifo2
    int fd_fifo2 = open(FIFO2, O_RDONLY);
    if (fd_fifo2 == -1) {
        perror("Erreur lors de l'ouverture du tube nommé fifo2");
        exit(EXIT_FAILURE);
    }
    
    struct Reponse reponse;
    if (read(fd_fifo2, &reponse, sizeof(reponse)) == -1) {
        perror("Erreur lors de la lecture depuis le tube nommé fifo2");
        close(fd_fifo2);
        exit(EXIT_FAILURE);
    }
    
    // Traitez la réponse comme nécessaire (par exemple, affichez les nombres aléatoires)
     int tailleTableau = reponse.numeros[0]; 
     printf("Réponse reçue du serveur (client ID: %d):\n", reponse.clientID);
    for (int i = 0; i <= tailleTableau; ++i) {
        printf("%d ", reponse.numeros[i]);
    }
    printf("\n");

    // Fermez le tube nommé fifo2 après la lecture
    close(fd_fifo2);
}
