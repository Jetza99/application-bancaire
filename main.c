#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 100
#define MAX_TRANSACTIONS 100



// CLIENT Structure
typedef struct {
    char nom[50];
    int cin;
    int pin;
    int solde;
} Client;

// TRANSACTION Structure
typedef struct {
    int cin_client;
    char type[10]; // "Virement", "Depot", "Retrait"
    int montant;
} Transaction;

// Global Variables
Client clients[MAX_CLIENTS];
Transaction transactions[MAX_TRANSACTIONS];
int nombre_clients = 0;
int nombre_transactions = 0;

// Prototypes for functions
void clientMenu(int cin);
void agentMenu();
void visiteurMenu();
void exitProgram();

// Save clients to file
void sauvegarder_clients() {
    FILE *file = fopen("clients.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier clients.txt\n");
        return;
    }
    for (int i = 0; i < nombre_clients; i++) {
        fprintf(file, "%s %d %d %d\n", clients[i].nom, clients[i].cin, clients[i].pin, clients[i].solde);
    }
    fclose(file);
    printf("Clients sauvegardés avec succès!\n");
}

// Load clients from file
void charger_clients() {
    FILE *file = fopen("clients.txt", "r");
    if (file == NULL) {
        printf("Aucun fichier clients trouvé.\n");
        return;
    }
    while (fscanf(file, "%s %d %d %d", clients[nombre_clients].nom, &clients[nombre_clients].cin, &clients[nombre_clients].pin, &clients[nombre_clients].solde) != EOF) {
        nombre_clients++;
    }
    fclose(file);
    printf("Clients chargés avec succès!\n");
}

// Save transactions to file
void sauvegarder_transactions() {
    FILE *file = fopen("transactions.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier transactions.txt\n");
        return;
    }
    for (int i = 0; i < nombre_transactions; i++) {
        fprintf(file, "%d %s %d\n", transactions[i].cin_client, transactions[i].type, transactions[i].montant);
    }
    fclose(file);
    printf("Transactions sauvegardées avec succès!\n");
}

// Load transactions from file
void charger_transactions() {
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL) {
        printf("Aucun fichier transactions trouvé.\n");
        return;
    }
    while (fscanf(file, "%d %s %d", &transactions[nombre_transactions].cin_client, transactions[nombre_transactions].type, &transactions[nombre_transactions].montant) != EOF) {
        nombre_transactions++;
    }
    fclose(file);
    printf("Transactions chargées avec succès!\n");
}

// Find Client by CIN
int trouver_client(int cin) {
    for (int i = 0; i < nombre_clients; i++) {
        if (clients[i].cin == cin) {
            return i;
        }
    }
    return -1;
}

// Display Client Info
void affichageInfoClient(int cin) {
    int index = trouver_client(cin);
    if (index != -1) {
        printf("Nom: %s\n", clients[index].nom);
        printf("CIN: %d\n", clients[index].cin);
        printf("Solde: %d\n", clients[index].solde);
    } else {
        printf("Client non trouvé.\n");
    }
}


// Close Account
void fermerCompte(int cin) {
    int index = trouver_client(cin);
    if (index != -1) {
        for (int i = index; i < nombre_clients - 1; i++) {
            clients[i] = clients[i + 1];
        }
        nombre_clients--;
        printf("Compte supprimé avec succès!\n");
    } else {
        printf("Client non trouvé.\n");
    }
}

// Withdraw Money
int retirerArgent(int cin, int montant) {
    int index = trouver_client(cin);
    if (index != -1 && montant > 0 && clients[index].solde >= montant) {
        clients[index].solde -= montant;
        transactions[nombre_transactions++] = (Transaction){cin, "Retrait", montant};
        return 1;
    }
    return -1;
}

// Deposit Money
int depotArgent(int cin, int montant) {
    int index = trouver_client(cin);
    if (index != -1 && montant > 0) {
        clients[index].solde += montant;
        transactions[nombre_transactions++] = (Transaction){cin, "Depot", montant};
        return 1;
    }
    return 0;
}


// Validate Client PIN
int validerClient(int cin, int pin) {
    int index = trouver_client(cin);
    if (index != -1 && clients[index].pin == pin) {
        return 1;
    }
    return 0;
}



// Add a Client
void ajouter_client() {
    if (nombre_clients >= MAX_CLIENTS) {
        printf("Nombre maximum de clients atteint.\n");
        return;
    }
    Client c;
    printf("Entrez l'ID du client : ");
    scanf("%d", &c.cin);
    printf("Entrez le nom du client : ");
    scanf("%s", c.nom);
    printf("Entrez le solde initial du client : ");
    scanf("%d", &c.solde);
    printf("Entrez le code PIN du client : ");
    scanf("%d", &c.pin);

    clients[nombre_clients++] = c;
    printf("Client ajouté avec succès !\n");
}

// Display All Clients
void afficher_clients() {
    if (nombre_clients == 0) {
        printf("Aucun client enregistré.\n");
        return;
    }
    printf("\nListe des clients :\n");
    for (int i = 0; i < nombre_clients; i++) {
        printf("CIN : %d, Nom : %s, Solde : %d\n", clients[i].cin, clients[i].nom, clients[i].solde);
    }
}

// Deposit Money
void deposer_argent() {
    int cin, montant;
    printf("Entrez l'ID du client : ");
    scanf("%d", &cin);
    int index = trouver_client(cin);
    if (index == -1) {
        printf("Client non trouvé.\n");
        return;
    }
    printf("Entrez le montant à déposer : ");
    scanf("%d", &montant);

    if (depotArgent(clients[index].cin, montant)) {
        transactions[nombre_transactions++] = (Transaction){cin, "Depot", montant};
        printf("Dépôt effectué avec succès ! Nouveau solde : %d\n", clients[index].solde);
    } else {
        printf("Montant invalide.\n");
    }
}

// Perform a Transfer
void effectuer_virement() {
    int cin_emetteur, cin_destinataire, montant;
    printf("Entrez CIN de l'émetteur : ");
    scanf("%d", &cin_emetteur);
    printf("Entrez CIN du destinataire : ");
    scanf("%d", &cin_destinataire);
    printf("Entrez le montant : ");
    scanf("%d", &montant);

    int idx_emit = trouver_client(cin_emetteur);
    int idx_dest = trouver_client(cin_destinataire);

    if (idx_emit == -1 || idx_dest == -1 || montant <= 0 || clients[idx_emit].solde < montant) {
        printf("Virement échoué.\n");
        return;
    }

    clients[idx_emit].solde -= montant;
    clients[idx_dest].solde += montant;
    transactions[nombre_transactions++] = (Transaction){cin_emetteur, "Virement", montant};
    printf("Virement réussi !\n");
}

// Supprimer un client
void supprimer_client() {
    int cin;
    printf("Entrez CIN du client à supprimer : ");
    scanf("%d", &cin);

    int index = trouver_client(cin);
    if (index == -1) {
        printf("Client non trouvé.\n");
        return;
    }

    for (int i = index; i < nombre_clients - 1; i++) {
        clients[i] = clients[i + 1];
    }
    nombre_clients--;

    printf("Client supprimé avec succès !\n");
}

// Rechercher un client par nom
void rechercher_client_par_nom() {
    char nom[50];
    printf("Entrez le nom du client : ");
    scanf("%s", nom);

    for (int i = 0; i < nombre_clients; i++) {
        if (strcmp(clients[i].nom, nom) == 0) {
            printf("ID : %d, Nom : %s, Solde : %d\n", clients[i].cin, clients[i].nom, clients[i].solde);
            return;
        }
    }
    printf("Client non trouvé.\n");
}

// Afficher l'historique des transactions
void afficher_transactions() {
    if (nombre_transactions == 0) {
        printf("Aucune transaction enregistrée.\n");
        return;
    }

    printf("\nHistorique des transactions :\n");
    for (int i = 0; i < nombre_transactions; i++) {
        printf("ID Client : %d, Type : %s, Montant : %d\n",
               transactions[i].cin_client, transactions[i].type, transactions[i].montant);
    }
}

// Placeholder for exitProgram function
void exitProgram() {
    printf("Programme terminé. Merci !\n");
    exit(0);
}

int authenticateAgent() {
    char enteredUsername[50], enteredPassword[50];
    char fileUsername[50], filePassword[50];
    FILE *file = fopen("agents.txt", "r");

    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier agents.txt.\n");
        return -1;
    }

    printf("Nom d'utilisateur : ");
    scanf("%s", enteredUsername);
    printf("Mot de passe : ");
    scanf("%s", enteredPassword);

    // Check the file for matching credentials
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(enteredUsername, fileUsername) == 0 && strcmp(enteredPassword, filePassword) == 0) {
            fclose(file);
            printf("Authentification réussie !\n");
            return 1;
        }
    }

    fclose(file);
    printf("Échec de l'authentification. Nom d'utilisateur ou mot de passe incorrect.\n");
    return -1;
}



// Main Function
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
            int cin, pin;
                 printf("Entrez votre CIN: ");
                scanf("%d", &cin);
                printf("Entrez votre PIN: ");
                scanf("%d", &pin);
                if (validerClient(cin, pin)) {
                    printf("Client verified successfully.\n");
                    affichageInfoClient(cin);
                    clientMenu(cin);
                } else {
                    printf("Code PIN invalide. Retour au menu principal.\n");
                }
                break;
            case 2:
            
        if (authenticateAgent() == -1) {
        printf("Accès refusé. Retour au menu principal.\n");
        break;
    }else{
                agentMenu();

    }
                break;
            case 3:
                visiteurMenu();
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

void clientMenu(int cin) {
    int option;
    do {
        printf("\n--- Menu Client ---\n");
        printf("1. Retirer\n");
        printf("2. Depot\n");
        printf("3. Fermer Compte\n");
        printf("4. Retour Au Menu Principal\n");
        printf("Entrer votre choix: ");
        scanf("%d", &option);

        int clientIndex = trouver_client(cin);


        switch (option) {
            case 1: {
                int montant;
                int pin;
                printf("Entrez le montant à retirer: ");
                scanf("%d", &montant);
                int result = retirerArgent(cin, montant);
                if (result == 1) {
                    printf("Retrait réussi. Nouveau solde: %d", clients[clientIndex].solde);
                } else if (result == -1) {
                    printf("Le retrait a échoué. Solde insuffisant ou montant invalide.\n");
                }
                break;
            }
            case 2: {
                int montant;
                printf("Entrer le montant à déposer: ");
                scanf("%d", &montant);
                if (depotArgent(cin, montant)) {
                    printf("Dépôt reussi. Nouvel solde: %d", clients[clientIndex].solde);
                } else {
                    printf("Le dépôt a echoue. Montant invalide.\n");
                }
                break;
            }
            case 3:
                char confirmation;
                printf("Etes-vous sûr de fermer votre compte ? (O/N) :");
                scanf(" %c", &confirmation);
                if(confirmation == 'o' || confirmation == 'O'){
                    fermerCompte(cin);
                    printf("Votre compte a ete ferme avec succes.\n");
                    return;
                }else
                {
                    printf("Cloture du compte annulee.\n");
                }
                
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

// Function to verify agent credentials from the file

void agentMenu() {



    // Menu principal
    int choix;
    do {
        printf("\n--- Gestion Banque - Agent ---\n");
        printf("1. Ajouter un client\n");
        printf("2. Afficher les clients\n");
        printf("3. Effectuer un virement\n");
        printf("4. Supprimer un client\n");
        printf("5. Rechercher un client par nom\n");
        printf("6. Deposer de l'argent\n");
        printf("7. Afficher l'historique des transactions\n");
        printf("8. Quitter\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouter_client(); break;
            case 2: afficher_clients(); break;
            case 3: effectuer_virement(); break;
            case 4: supprimer_client(); break;
            case 5: rechercher_client_par_nom(); break;
            case 6: deposer_argent(); break;
            case 7: afficher_transactions(); break;
            case 8: printf("Au revoir !\n"); break;
            default: printf("Option invalide.\n");
        }
    } while (choix != 8);

}

// Placeholder for visiteurMenu function
void visiteurMenu() {
     int choix;
    do {
        printf("\n--- Menu Visiteur ---\n");
        printf("1. Consulter les informations\n");
        printf("2. Ouvrir un compte\n");
        printf("3. Retour au menu principal\n");
        printf("Entrer votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Informations :\n");
                printf("- Horaires d'ouverture : 9h - 17h\n");
                printf("- Contact : contact@banque.com\n");
                printf("- Adresse : 123 Rue Principale, Ville\n");
                break;
            case 2: {
                ajouter_client();
                break;
            }
            case 3:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    } while (choix != 3);
}
