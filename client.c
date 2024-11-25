#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

void initClient(Client *c, char *nom, int cin, int pin, int solde){
    strncpy(c->nom, nom, sizeof(c->nom) - 1);
    c->nom[sizeof(c->nom) -  1] = '\0';
    c->cin = cin;
    c->pin = pin;
    c->solde = solde;
}

void affichageInfoClient(Client *c){
    printf("Nom: %s\n", c->nom);
    printf("CIN: %d\n", c->cin);
    printf("Solde: %d\n", c->solde);
}

void fermerCompte(Client *c){
    strcpy(c->nom, "");
    c->cin = 0;
    c->solde = 0;
    c->pin = 0;
    c->solde = 0;
}

int retirerArgent(Client *c, int montant){
    if(montant > c->solde || montant <= 0){
        return -1;
    }
    c->solde -= montant;
    return 1;
}

int depotArgent(Client *c, int montant){
    if(montant <= 0){
        return 0;
    }
    c->solde += montant;
    return 1;
}

int validerClient(Client *c, int pin){
    return c->pin == pin;
}