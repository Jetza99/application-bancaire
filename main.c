#include <stdio.h>
#include <stdlib.h>
#include "client.h"


// Function prototypes for menu options
void clientMenu(Client *client);

void agentMenu();
void exitProgram();

int main() {
    int choix;

    Client client;

    initClient(&client, "Omar", 14420533, 2451, 1200);


    while (1) { // Infinite loop for the menu
        // Display the menu
        printf("\n===== Menu Banque =====\n");
        printf("1. Client\n");
        printf("2. Agent\n");
        printf("3. Visiteur\n");
        printf("4. Quitter\n");
        printf("========================\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choix);

        // Handle the user's choix
        switch (choix) {
            case 1:
            int pin;
                printf("Entrer votre PIN: ");
                scanf("%d", &pin);
                if (validerClient(&client, pin)) {
                    printf("Client verified successfully.\n");
                    affichageInfoClient(&client);
                    clientMenu(&client);
                } else {
                    printf("Invalid PIN. Returning to main menu.\n");
                }
                break;
            case 2:
                agentMenu();
                break;
            case 3:
                option2();
                break;
            case 4:
                exitProgram();
                return 0; // Exit the program
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}

// Function definitions for each option
void clientMenu(Client *client) {
    int option;
    do {
        printf("\n--- Menu Client ---\n");
        printf("1. Retirer\n");
        printf("2. Depot\n");
        printf("3. Fermer Compte\n");
        printf("4. Retour Au Menu Principal\n");
        printf("Entrer votre choix: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                int montant;
                int pin;
                printf("Entrez le montant à retirer: ");
                scanf("%d", &montant);
                int result = retirerArgent(client, montant);
                if (result == 1) {
                    printf("Retrait réussi. Nouveau solde: %d", client->solde);
                } else if (result == -1) {
                    printf("Le retrait a échoué. Solde insuffisant ou montant invalide.\n");
                }
                break;
            }
            case 2: {
                int montant;
                printf("Entrer le montant à déposer: ");
                scanf("%d", &montant);
                if (depotArgent(client, montant)) {
                    printf("Dépôt reussi. Nouvel solde: %d", client->solde);
                } else {
                    printf("Le dépôt a echoue. Montant invalide.\n");
                }
                break;
            }
            case 3:
                printf("La clôture du compte\n");
                break;
            case 4:
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide. Essayer à nouveau.\n");
                break;
        }
    } while (option != 4);

}

void agentMenu() {
    printf("Menu Agent\n");
}

void exitProgram() {
    printf("Quitter le programme. Au revoir!\n");
}
