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


int main(int argc, char const *argv[])
{
    printf("[ DEBUT ]\n\n");
    Automate* automate = nouvelle_automate("./Automate.init");
    Automate* automate2 = nouvelle_automate("./Automate2.init");
    afficher_automate(automate);
    afficher_automate(automate2);
    printf("\n[ FIN ]\n");
    return 0;
}

Automate* nouvelle_automate(char* nom_fichier_init) {
    Automate* automate=lire_fichier_init(nom_fichier_init);
    return automate;
}