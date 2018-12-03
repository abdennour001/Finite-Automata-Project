#ifndef _INTERFACE_H
#define _INTERFACE_H

/**
 * @author AMOKRANE Abdennour
 * 
 * "interface.h"
 * 
 * Pour controler l'interface principale de notre programme.
 * 
 * Contient les prototypes des fonctions "headers", implementation dans le fichier "interface.c"
 * 
 * **/

#include "structure.h"
#include "biblio.h"


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KBLDON  "\e[1m"
#define KBLDOFF "\e[0m"

#define SIGNE1 "195"
#define SIGNE2 "196"
 
void aff_msg_debut();
void aff_menu();
char *lire_nom_automate();
void aff_chemin_reussi(Automate *automate, Mot *mot);

Mot *lire_mot();

#endif