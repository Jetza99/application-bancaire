#include <stdio.h>
#include <stdlib.h>
#include "client.h"


// Function prototypes for menu options
void option1();
void option2();
void exitProgram();

int main() {
    int choix;

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
                option1();
                break;
            case 2:
                option2();
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
void option1() {
    printf("You selected Option 1.\n");

    Client client;

    initClient(&client, "Omar", 14420533, 2451, 120);
    affichageInfoClient(&client);

    // Add the logic for Option 1 here
}

void option2() {
    printf("You selected Option 2.\n");
    // Add the logic for Option 2 here
}

void exitProgram() {
    printf("Exiting the program. Goodbye!\n");
}
