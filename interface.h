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

void aff_msg_debut();
void aff_menu();


Mot *lire_mot();

#endif