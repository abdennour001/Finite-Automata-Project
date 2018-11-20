#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "biblio.h"

/**
 * @author AMOKRANE Abdennour
 * 
 * "main.c"
 * 
 * Le Fichier principale du programme.
 * 
 * **/


int main(int argc, char const *argv[])
{
    printf("[ DEBUT ]\n\n");
    Automate* automate = lire_fichier_init("./Automate.init");
    afficher_automate(automate);
    printf("\n[ FIN ]\n");
    return 0;
}
