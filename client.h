#ifndef CLIENT_H
#define CLIENT_H

typedef struct {
    char nom[50];
    int cin;
    int pin;
    int solde;
} Client;

void affichageInfoClient(Client *c);
void initClient(Client *c, char *nom, int cin, int pin, int solde);
void fermerCompte(Client *c);
int retirerArgent(Client *c, int montant);
int depotArgent(Client *c, int montant);
int validerClient(Client *c, int pin);


#endif