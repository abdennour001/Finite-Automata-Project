#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "biblio.h"
#include "interface.h"

/**
 * @author AMOKRANE Abdennour
 * 
 * "main.c"
 * 
 * Le Fichier principale du programme.
 * 
 * **/

Automate* nouvelle_automate(char* nom_fichier_init);
void test_unitaire();

int main(int argc, char const *argv[])
{
    printf("[ DEBUT ]\n\n");
    test_unitaire();
    printf("\n[ FIN ]\n");
    return 0;
}

Automate* nouvelle_automate(char* nom_fichier_init) {
    Automate* automate=lire_fichier_init(nom_fichier_init);
    return automate;
}

void test_unitaire() {
    Automate* automate = nouvelle_automate("./Automate2.init");
    Etat* e=creer_etat(++ID_ETAT_SYS, "new_etat1", FINAL);
    Etat* e1=creer_etat(++ID_ETAT_SYS, "new_etat2", NORMAL);
    Etat* e2=creer_etat(++ID_ETAT_SYS, "new_etat3", FINAL);
    //ajouter_etat(automate, e);
    //ajouter_etat(automate, e1);
    //ajouter_etat(automate, e2);
    supprimer_etat(automate, automate->ensemble_etat[2]);
    supprimer_etat(automate, automate->ensemble_etat[1]);
    //ajouter_etat(automate, e2);
    afficher_automate(automate);
    //Automate* automate2 = nouvelle_automate("./Automate2.init");
    //afficher_automate(automate2);
    
}