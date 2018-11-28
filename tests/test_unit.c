
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
#include "../externe/structure.h"

void test_unitaire() {
    Automate* automate = nouvelle_automate("./tests/Automate deterministe.init");
    Etat* e=creer_etat(++ID_ETAT_SYS, "new_etat1", FINAL);
    Etat* e1=creer_etat(++ID_ETAT_SYS, "new_etat2", NORMAL);
    Etat* e2=creer_etat(++ID_ETAT_SYS, "new_etat3", FINAL);
    //ajouter_etat(automate, e);
    //ajouter_etat(automate, e1);
    //ajouter_etat(automate, e2);
    //supprimer_etat(automate, automate->ensemble_etat[3]);
    //supprimer_etat(automate, automate->ensemble_etat[1]);
    //ajouter_instruction(automate, automate->ensemble_instruction[0]);
    //ajouter_etat(automate, e2);
    //rendez_simple(automate);
    /*Pile *p=NULL;
    empiler(&p, e);
    //empiler(&p, e1);
    //empiler(&p, e2);
    /*Etat* e9 = depiler(&p);
    afficher_etat(e9);
    e9 = depiler(&p);
    printf("%d\n", e9 == NULL);*/

    //rendez_simple(automate);
    //afficher_automate(automate);
    Automate *automate_deter = rendez_deterministe(automate);
    afficher_automate(automate_deter);

    //printf("%d - %d * %d\n", auto_est_complet(automate), auto_est_simple(automate), auto_est_deterministe(automate));
    //rendez_complet(automate);
    //printf("%d - %d * %d\n", auto_est_complet(automate), auto_est_simple(automate), auto_est_deterministe(automate));

    //afficher_automate(automate);
    //Automate* automate2 = nouvelle_automate("./Automate2.init");
    //afficher_automate(automate2);
    /*char **l1, **l2; int l11, l12;
    char nom1[MAX_INT], nom2[MAX_INT];
    strcpy(nom1, "S0;S2");
    strcpy(nom2, "S0;S1");
    l1 = separer_chaine(nom1, " ;\n", &l11);
    l2 = separer_chaine(nom2, " ;\n", &l12);
    //char *l1[]={"S0", "S2"};
    //char *l2[]={"S0", "S1"};
    printf("%d\n", deux_chaines_egale(l1, l2, l11, l12));*/

}