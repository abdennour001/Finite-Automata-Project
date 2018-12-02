
/**
 * @author AMOKRANE Abdennour
 * 
 * "interface.c"
 * 
 * Pour controler l'interface principale de notre programme.
 * 
 * Contient les implementations des fonctions dans le fichier "interface.h"
 * 
 * **/

#include "interface.h"
#include "structure.h"
#include "biblio.h"

void aff_msg_debut() {

}

void aff_menu() {
    
}

Mot *lire_mot() {
    char mot__[MAX_INT]; char **__mot__; int l;
    printf("[?] Faire entrée un mot : (regex : letter_1.lettre_2. ... .lettre_n)\n>>> ");
    scanf("%s", mot__);
    __mot__ = separer_chaine(mot__, ".\n", &l);
    Mot *mot_retour = creer_mot(l, __mot__);     
    return mot_retour;
}