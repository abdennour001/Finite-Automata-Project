#ifndef _BIBLIO_H
#define _BIBLIO_H


/**
 * @author AMOKRANE Abdennour
 * 
 * "biblio.h"
 * 
 * Contient les prototypes des fonctions qui controle le API des Automate :
 * 
 * Creation d'Automate, Etat, Instruction ... etc. De plus le fichier contient les fonctions
 * 
 * qui manipule les fichier d'entrée et de sortie (Input and Output). 
 * 
 * **/

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

/** Declaration fichier .init **/
extern char fichier_init[30];
FILE* ouvrir_fichier();
/****/

/** Manupilation chaine de caractère pour lire le fichier .init **/

int converter_chaine_entier(char* chaine);
char** separer_chaine(char* chaine, char* separateur, int *longeur);
Automate* lire_fichier_init(char* nom_fichier_init);

/****/

/** API de creation des Automates **/
Etat* creer_etat(int id, char* nom, Status status);
Alphabet* creer_alphabet(char* nom, int nombre_lettres, char** ensemble_lettres);
Mot* creer_mot(int longeur, char** vecteur_mot);
Instruction* creer_instruction(int id, Mot* mot, Etat* etat_src, Etat* etat_dest);
Automate* creer_automate(int n_e, int n_ef, int n_i, char* nom, Alphabet* alphabet, Etat* e_init, Etat** ensemble_etats, Etat** ensemble_etats_finaux, Instruction** ensemble_i);
/****/

/** API de manupilation des Automates **/

int auto_est_simple(Automate* automate);
int auto_est_deterministe(Automate* automate);
int auto_est_complet(Automate* automate);
int etat_est_accessible(Automate* a, Etat* etat);
int etat_est_Co_accessible(Automate* a, Etat* etat);
Automate* rendez_simple(Automate* automate);
Automate* rendez_deterministe(Automate* automate);
Automate* rendez_complet(Automate* automate);

/****/

#endif