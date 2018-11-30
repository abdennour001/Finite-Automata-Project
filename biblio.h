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
#include "externe/structure.h"


/** Declaration fichier .init **/
extern char fichier_init[30];
FILE* ouvrir_fichier();
extern int __INIT__;
extern int marquer_vecteur[MAX_INT];
/****/

/** Manupilation chaine de caractère pour lire le fichier .init **/

int converter_chaine_entier(char* chaine);
int deux_chaines_egale(char **ch1, char **cha2, int l1, int l2);
char** separer_chaine(char* chaine, char* separateur, int *longeur);
void concat_chaine(char *a, char *b); // concatener a et b, le resultat dans a
Automate* lire_fichier_init(char* nom_fichier_init);

/****/

/** API de creation des Automates **/
Etat* creer_etat(int id, char* nom, Status status);
Alphabet* creer_alphabet(char* nom, int nombre_lettres, char** ensemble_lettres);
Mot* creer_mot(int longeur, char** vecteur_mot);
Instruction* creer_instruction(int id, Mot* mot, Etat* etat_src, Etat* etat_dest);
Automate* creer_automate(int n_e, int n_ef, int n_i, char* nom, Alphabet* alphabet, Etat* e_init, Etat** ensemble_etats, Etat** ensemble_etats_finaux, Instruction** ensemble_i);
Automate* nouvelle_automate(char* nom_fichier_init); // creer autommate à partir d'un fichier

/****/

/** API de manupilation des Automates **/

int auto_est_simple(Automate* automate);
int auto_est_deterministe(Automate* automate);
int auto_est_complet(Automate* automate);
int etat_est_accessible(Automate* a, Etat* etat);
int etat_est_Co_accessible(Automate* a, Etat* etat);
int rendez_simple(Automate* automate);
Automate *rendez_deterministe(Automate* automate);
void rendez_complet(Automate* automate);
/***
 * 
 * etat_initial_de_parcoure : c'est l'état qu'on va parcourir l'automate a partir de lui
 * 
*/
void depth_first_search(Automate *automate, Etat *etat_initial_de_parcoure); //Algorithme pour parcourir une automate
int index_dans_ensemble(Etat **ensemble_etats, int nombre_etats, Etat *etat); // retourne l'index de l'état dans l'ensemble
void init_marquer_vecteur(Automate *automate);
void chemin_entre_etats(Automate *automate, Etat *etat_depart, Etat *etat_arrive, int *return_value);

void verifier_debut(Mot *mot1, Mot *mot2);
void eclater_mot(Mot *mot, int l);
Instruction **rechercher_chemins_reussi(Automate *automate, Mot *mot, int vect_taille[], int *nombre_chemin_reussi); /** Retourne tous les chemins réussi à la lecture du mot "mot_input" dans un vecteur

    chaque taille d'un chemin réussi "i" est dans "vect_taille[i]", nombre_chemin_reussi contien le nobmbre des chemins trouvés  
**/

/****/

#endif