#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "biblio.h"
#include "interface.h"
#include "tests/test_unit.h"
#include "externe/structure.h"

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
    test_unitaire();
    printf("\n[ FIN ]\n");
    return 0;
}