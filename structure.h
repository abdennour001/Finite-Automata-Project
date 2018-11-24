#ifndef _STRUCTURE_H
#define _STRUCTURE_H

/**
 * @author AMOKRANE Abdennour
 * 
 * "structure.h"
 * 
 * Contient les prototypes des fonctions qui mettre en place la structure des Automate :
 * 
 * Structure d'Automate, Etat, Instruction, Mot ... etc. De plus le fichier contient les fonctions
 * 
 * qui manipule la machine abstraite de ces structure : Allocations mémoire, setters et getters ... etc.
 * 
 * **/

#define MAX_INT 1000
#define EPSILON "~"

/**/

extern int ID_ETAT_SYS;
extern int ID_INSTRUCTION_SYS;

enum Status { // les 3 status d'un état d'une automate.
    NORMAL = 1, // flag NORMAL 0001
    FINAL = 2, // flag FINAL 0010
    INITIAL = 4, // flag INITIAL 0100
    INITIAL_FINAL = 6 // flag INITIAL_FINAL 0110
};

typedef enum Status Status;

char* status_to_string(Status status);
/**/

/* Structure d'un état Si */
struct Etat
{
    int id;
    char* nom;
    Status status;
};

typedef struct Etat Etat;

Etat* alloc_etat();
void set_nom_etat(Etat* e, char* nom);
void set_id_etat(Etat* e, int id);
void set_status(Etat* e, Status s);

// Recherche.
Etat* rechercher_etat_par_nom(Etat** ensemble_etats, char* nom);

// Affichge.
void afficher_etat(Etat* etat);
void afficher_etat_sans_detail(Etat* etat);

/**/

/* Structure d'une Alphabet X = {lettre_1, lettre_2, ..., lettre_nombre_lettres}*/
struct Alphabet 
{
    char* nom;
    int nombre_lettres; // |X|
    char** ensemble_lettres; // X
};

typedef struct Alphabet Alphabet;

Alphabet* alloc_alphabet();
void set_ensemble_lettres(Alphabet* a, int nombre_lettres, char** ensemble);
void ajouter_lettre(Alphabet* a, char* lettre);
void set_nom_alphabet(Alphabet* a, char* nom);
void afficher_alphabet(Alphabet* a);
/**/

/* Structure d'un mot M = lettre_1 . lettre_2 . ... . lettre_longeur */
struct Mot
{
    int longeur; // |mot| : longeur du mot
    char** vecteur_mot; // concaténationdes alphabets TO_CHANGE
};

typedef struct Mot Mot;

Mot* alloc_mot();
void set_vecteur_mot(Mot* m, int longeur, char** mot);
char** get_vecteur_mot(Mot* m);
void afficher_mot(Mot* m);
int mot_compare(Mot* mot1, Mot* mot2);
/**/

/* Structure d'une instruction II = (Si, mot, Sj) */
struct Instruction
{
    int id;
    Mot* mot; // mot lu
    Etat* etat_src; // Si : état source
    Etat* etat_dest; // Sj : état destination
};

typedef struct Instruction Instruction;

Instruction* alloc_instruction();
void set_mot_instruction(Instruction* i, Mot* mot);
void set_etat_src(Instruction* i, Etat* e_s);
void set_etat_dest(Instruction* i, Etat* e_d);
void set_id_instruction(Instruction* i, int id);
void afficher_instruction(Instruction *i);
void afficher_instruction_sans_detail(Instruction *i);
/**/

/** Structure d'une Automate A = <X, S0, F, S, II> **/
struct Automate
{
    int nombre_etat;
    int nombre_etats_finaux;
    int nombre_instructions;

    char* nom; // A : le nom de l'automate
    Alphabet* alphabet; // X : ensemble des lettres
    Etat* etat_init; // S0 : état initial
    Etat** ensemble_etat; // S : ensemble des états
    Etat** ensemble_etat_finaux; //  F : ensemble des états finaux
    Instruction** ensemble_instruction; // II : ensemble des instructions
};

typedef struct Automate Automate;

Automate* alloc_automate();
void set_alphabet(Automate* a, Alphabet* alphabet);
void set_nom_automate(Automate* a, char* nom);
void set_etat_init(Automate* a, Etat* etat_init);
void set_nombre_etat(Automate* a, int n);
void set_nombre_etat_finaux(Automate* a, int n_f);
void set_nombre_instruction(Automate* a, int n_i);
void afficher_automate(Automate *a);

//---------

void set_ensemble_etat(Automate* a, Etat** e_e);
void ajouter_etat(Automate* a, Etat* etat);
void supprimer_etat(Automate* a, Etat* etat);
void mise_a_jour_etat(Automate *a, Etat *e, int id, char* nom, Status s);

//---------

void set_ensemble_etat_finaux(Automate* a, Etat** e_f);
void ajouter_etat_final(Automate* a, Etat* e_f);

//---------

void set_ensemble_instruction(Automate* a, Instruction** e_i);
void ajouter_instruction(Automate* a, Instruction* i);
void supprimer_instruction(Automate* a, Instruction* i);
Instruction* rechercher_instruction(Automate* a, Etat* src, Etat* dest, Mot* mot);

/****/

#endif