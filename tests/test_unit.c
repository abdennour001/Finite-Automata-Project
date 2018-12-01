
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
    Automate* automate = nouvelle_automate("./tests/Automate simple.init");
    printf("LOL");
    //Etat* e=creer_etat(++ID_ETAT_SYS, "new_etat1", FINAL);
    //Etat* e1=creer_etat(++ID_ETAT_SYS, "new_etat2", NORMAL);
    //Etat* e2=creer_etat(++ID_ETAT_SYS, "new_etat3", FINAL);
    char *vect1[MAX_INT];
    char *vect2[MAX_INT];
    vect1[0] = (char *) malloc(MAX_INT * sizeof(char));
    vect1[1] = (char *) malloc(MAX_INT * sizeof(char));
    vect1[2] = (char *) malloc(MAX_INT * sizeof(char));    
    vect2[0] = (char *) malloc(MAX_INT * sizeof(char));
    vect2[1] = (char *) malloc(MAX_INT * sizeof(char));
    vect2[2] = (char *) malloc(MAX_INT * sizeof(char));
    strcpy(vect1[0], "a");
    strcpy(vect1[1], "b");
    strcpy(vect1[2], "a");

    strcpy(vect2[0], "a");strcpy(vect2[1], "b");strcpy(vect2[2], "a");
    Mot *m=creer_mot(2, vect1);
    Mot *m2=creer_mot(3, vect2);
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

    //afficher_mot(m2);puts("");
    //Mot *m4 = eclater_mot(m2, 2);
    //afficher_mot(m4);puts("");
    //afficher_mot(m2);puts("");

    //printf("%d\n", verifier_facteur_gauche(m2, m));

    int vect[MAX_INT]; int i;
    rechercher_chemins_reussi(automate, m2, vect, &i);

    /*Pile_etat_mot *p=NULL;
    PEtat_mot *etat_mot = creer_etat_mot(e, m);
    empiler(&p, etat_mot);
    PEtat_mot *etat_mot2 = creer_etat_mot(e1, m2);
    empiler(&p, etat_mot2);

    afficher_etat(p->etat_mot->etat);*/

    //depiler_etat_mot(&p);

    //afficher_pile_etat_mot(p);

    //rendez_simple(automate);
    //afficher_automate(automate);
    //Automate *automate_deter = rendez_deterministe(automate);
    //afficher_automate(automate_deter);

    //depth_first_search(automate, automate->ensemble_etat[automate->nombre_etat-1]);
    //printf("%d\n", etat_est_Co_accessible(automate, automate->ensemble_etat[automate->nombre_etat-2]));

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