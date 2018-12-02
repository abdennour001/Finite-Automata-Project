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

typedef struct Petat_mot {
    Etat *etat;
    Mot *mot;
} PEtat_mot;

PEtat_mot *creer_etat_mot(Etat *etat, Mot *mot);

typedef struct Pile_etat_mot {
    PEtat_mot *etat_mot;
    struct Pile_etat_mot *suiv;
} Pile_etat_mot;

typedef struct Pile {
    Etat* etat;
    struct Pile *suiv;
} Pile;

typedef struct Pile_instruction {
    Instruction* instruction;
    struct Pile_instruction *suiv;
} Pile_instruction;

/** API : Pile simple **/

Pile *allouer();
void aff_val(Pile *p,Etat* etat);
void aff_adr(Pile *p,Pile *q);
Pile *suivant(Pile *p);
Etat* valeur(Pile *p);
void empiler(Pile **p, Etat* c);
Etat *depiler(Pile **p);
int pilevide(Pile *p);
void afficher_pile(Pile *p); //Afficher une LLc, si la liste est vide donc rien va afficher a l'ecran ...

/**
 * 
*/

/** 
 * API : Pile etat_mot
 * 
 * **/


Pile_etat_mot *allouer_pile_etat_mot();
void aff_val_etat_mot(Pile_etat_mot *p,PEtat_mot *etat_mot);
void aff_adr_etat_mot(Pile_etat_mot *p,Pile_etat_mot *q);
Pile_etat_mot *suivant_etat_mot(Pile_etat_mot *p);
PEtat_mot* valeur_etat_mot(Pile_etat_mot *p);
void empiler_etat_mot(Pile_etat_mot **p, PEtat_mot* c);
PEtat_mot *depiler_etat_mot(Pile_etat_mot **p);
int pilevide_etat_mot(Pile_etat_mot *p);
void afficher_pile_etat_mot(Pile_etat_mot *p); //Afficher une LLc, si la liste est vide donc rien va afficher a l'ecran ...

/**
 * **/

/**
 * API : Pile Instruction 
 * **/


Pile_instruction *allouer_pile_instruction();
void aff_val_instruction(Pile_instruction *p,Instruction* Instruction);
void aff_adr_instruction(Pile_instruction *p,Pile_instruction *q);
Pile_instruction *suivant_instruction(Pile_instruction *p);
Instruction* valeur_instruction(Pile_instruction *p);
void empiler_instruction(Pile_instruction **p, Instruction* c);
Instruction *depiler_instruction(Pile_instruction **p);
int pilevide_instruction(Pile_instruction *p);
void afficher_pile_instruction(Pile_instruction *p); //Afficher une LLc, si la liste est vide donc rien va afficher a l'ecran ...


/**
 * **/

#endif