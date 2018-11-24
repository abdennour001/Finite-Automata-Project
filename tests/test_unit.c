
/**
 * @author AMOKRANE Abdennour
 * 
 * "test_unit.c"
 * 
 * Contient les tests unitaires.
 * 
 * **/

#include <stdio.h>
#include <stdlib.h>
#include "test_unit.h"
#include "../structure.h"
#include "../biblio.h"

void test_unitaire() {
    Automate* automate = nouvelle_automate("./Automate simple.init");
    //Etat* e=creer_etat(++ID_ETAT_SYS, "new_etat1", FINAL);
    //Etat* e1=creer_etat(++ID_ETAT_SYS, "new_etat2", NORMAL);
    //Etat* e2=creer_etat(++ID_ETAT_SYS, "new_etat3", FINAL);
    //ajouter_etat(automate, e);
    //ajouter_etat(automate, e1);
    //ajouter_etat(automate, e2);
    //supprimer_etat(automate, automate->ensemble_etat[2]);
    //supprimer_etat(automate, automate->ensemble_etat[1]);
    //ajouter_instruction(automate, automate->ensemble_instruction[0]);
    //ajouter_etat(automate, e2);
    printf("%d\n", auto_est_complet(automate));
    //afficher_automate(automate);
    //Automate* automate2 = nouvelle_automate("./Automate2.init");
    //afficher_automate(automate2);   
}