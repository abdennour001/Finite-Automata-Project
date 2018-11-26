#ifndef _EXTERNE_STRUCTURE_H
#define _EXTERNE_STRUCTURE_H


/**
 * @author AMOKRANE Abdennour
 * 
 * "externe/structure.h"
 * 
 * Contient les  structures et les prototypes des fonctions qui manipule les structure 
 * 
 * externe dans le programme comme Les piles, les files, ...
 * 
 * **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"


typedef struct Pile {
    Etat* etat;
    struct Pile *suiv;
} Pile;


Pile *allouer();
void aff_val(Pile *p,Etat* etat);
void aff_adr(Pile *p,Pile *q);
Pile *suivant(Pile *p);
Etat* valeur(Pile *p);
void empiler(Pile **p, Etat* c);
Etat *depiler(Pile **p);
int pilevide(Pile *p);
void afficher_pile(Pile *p); //Afficher une LLc, si la liste est vide donc rien va afficher a l'ecran ...


#endif