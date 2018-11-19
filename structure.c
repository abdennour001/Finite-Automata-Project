#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structure.h"

int ID_ETAT_SYS=0;
int ID_INSTRUCTION_SYS=0;


char* status_to_string(Status status) {
    if (status == FINAL) {
        return "FINAL";
    } else if (status == INITIAL) {
        return "INIT";
    } else {
        return "N";
    }
}

/* Implementation des fonctions d'Etat */

Etat* alloc_etat() {
    Etat* e;
    e = (Etat* ) malloc(sizeof(Etat));
    e->nom = (char* ) malloc(sizeof(char));
    return e;
}
void set_nom_etat(Etat* e, char* nom) {
    strcpy(e->nom, nom);
}
void set_id_etat(Etat* e, int id) {
    e->id = id;
}
void set_status(Etat* e, Status s) {
    e->status = s;
}
void afficher_etat(Etat* etat) {
    printf("| %3d | %5s | %5s |", etat->id, etat->nom, status_to_string(etat->status));
}

void afficher_etat_sans_detail(Etat* etat) {
    printf("| %4s |", etat->nom);
}


Etat* rechercher_etat_par_nom(Etat** ensemble_etats, char* nom) {
    for (int i=0; ensemble_etats[i] != NULL; i++) {
        if (strcmp(ensemble_etats[i]->nom, nom) == 0) {
            return ensemble_etats[i];
        }
    }
}

/**/

/* Implementation des fonctions de Alphabet */

Alphabet* alloc_alphabet() {
    Alphabet* a;
    a = (Alphabet* ) malloc(sizeof(Alphabet));
    a->nom  = (char* ) malloc(sizeof(char));
    a->ensemble_lettres = (char**) malloc(sizeof(char));
    return a;
}
void set_ensemble_lettres(Alphabet* a, int nombre_lettres, char** ensemble) {
    for (int i=0; i < nombre_lettres; i++) {
        a->ensemble_lettres[i] = (char* ) malloc(sizeof(char));
        strcpy(a->ensemble_lettres[i], ensemble[i]);
    };
    a->nombre_lettres = nombre_lettres;
}
void ajouter_lettre(Alphabet* a, char* lettre) {
    a->ensemble_lettres[a->nombre_lettres++] = lettre;
}
void set_nom_alphabet(Alphabet* a, char* nom) {
    strcpy(a->nom, nom);
}
void afficher_alphabet(Alphabet* a) {
    char output[50];
    sprintf(output, "%s {", a->nom);
    for (int i=0; a->ensemble_lettres[i] != NULL; i++) {
        if (i==0) {
            sprintf (output, "%s%s", output, a->ensemble_lettres[i]);
        } else {
            sprintf (output, "%s, %s", output, a->ensemble_lettres[i]);
        }
    }
    sprintf(output, "%s}\n", output);
    printf("%s", output);
}

/**/

/* Implementation des fonctions de Mot */

Mot* alloc_mot() {
    Mot* m;
    m = (Mot *) malloc(sizeof(Mot));
    m->vecteur_mot = (char **) malloc(sizeof(char));
    return m;
}
void set_vecteur_mot(Mot* m, int longeur, char** mot) {
    m->longeur = longeur;
    for (int i=0; i < longeur; i++) {
        m->vecteur_mot[i] = (char* ) malloc(sizeof(char));
        strcpy(m->vecteur_mot[i], mot[i]);
    }
}
char** get_vecteur_mot(Mot* m) {
    return m->vecteur_mot;
}

void afficher_mot(Mot* m) {
    char output[30]="";
    for (int i=0; m->vecteur_mot[i] != NULL; i++) {
        if (strcmp(output, "") == 0) {
        sprintf(output, "%s", m->vecteur_mot[i]);
        } else {
        sprintf(output, "%s.%s", output, m->vecteur_mot[i]);
        }
    }
    printf("%s", output);
}

/**/

/* Implementation des fonctions d'Instruction */

Instruction* alloc_instruction() {
    return (Instruction* ) malloc(sizeof(Instruction));
}
void set_mot_instruction(Instruction* i, Mot* mot) {
    i->mot = mot;
}
void set_etat_src(Instruction* i, Etat* e_s) {
    i->etat_src = e_s;
}
void set_etat_dest(Instruction* i, Etat* e_d) {
    i->etat_dest = e_d;
}
void set_id_instruction(Instruction* i, int id) {
    i->id = id;
}

void afficher_instruction(Instruction *i) {
    afficher_etat(i->etat_src);
    printf("\t--\t");
    afficher_mot(i->mot);
    printf("\t-->\t");
    afficher_etat(i->etat_dest);
}

void afficher_instruction_sans_detail(Instruction *i) {
    afficher_etat_sans_detail(i->etat_src);
    printf("\t--\t");
    afficher_mot(i->mot);
    printf("\t-->\t");
    afficher_etat_sans_detail(i->etat_dest);
}


/**/

/*** Implementation des fonctions d'Automate ***/

Automate* alloc_automate() {
    Automate* a;
    a = (Automate* ) malloc(sizeof(Automate));
    a->nom = (char *) malloc(sizeof(char));
    return a;
}
void set_alphabet(Automate* a, Alphabet* alphabet) {
    a->alphabet = alphabet;
}
void set_nom_automate(Automate* a, char* nom) {
    strcpy(a->nom, nom);
}
void set_etat_init(Automate* a, Etat* etat_init) {
    a->etat_init = etat_init;
}
void set_nombre_etat(Automate* a, int n) { 
    a->nombre_etat = n;
}
void set_nombre_etat_finaux(Automate* a, int n_f) {
    a->nombre_etats_finaux = n_f;
}
void set_nombre_instruction(Automate* a, int n_i) {
    a->nombre_instructions = n_i;
}

//---------

void set_ensemble_etat(Automate* a, Etat** e_e) {
    a->ensemble_etat = e_e;
}
void ajouter_etat(Automate* a, Etat* etat) {
    a->ensemble_etat[a->nombre_etat++] = etat;
}

//---------

void set_ensemble_etat_finaux(Automate* a, Etat** e_f) {
    a->ensemble_etat_finaux = e_f;
}
void ajouter_etat_final(Automate* a, Etat* e_f) {
    a->ensemble_etat_finaux[a->nombre_etats_finaux++] = e_f;
}

//---------

void set_ensemble_instruction(Automate* a, Instruction** e_i) {
    a->ensemble_instruction = e_i;
}
void ajouter_instruction(Automate* a, Instruction* i) {
    a->ensemble_instruction[a->nombre_instructions++] = i;
}
void afficher_automate(Automate *a) {
    printf("%s < X, S0, F, S, II >\n\n", a->nom);
    // Afficher X
    printf("Alphabet X : \n\n");
    afficher_alphabet(a->alphabet);printf("\n");
    // Afficher S0
    printf("Etat initial S0 : \n\n");
    afficher_etat(a->etat_init);
    printf("\n\n");
    // Afficher F
    printf("Etats finaux F : \n\n");
    for (int i=0; a->ensemble_etat_finaux[i] != NULL; i++) {
        afficher_etat(a->ensemble_etat_finaux[i]);
        printf("\n");
    }
    printf("\n");
    // Afficher S
    printf("Etats S : \n\n");
    for (int i=0; a->ensemble_etat[i] != NULL; i++) {
        afficher_etat(a->ensemble_etat[i]);
        printf("\n");
    }
    // Afficher II
    printf("\nInstructions II : \n\n");
    for (int i=0; a->ensemble_instruction[i] != NULL; i++) {
        afficher_instruction_sans_detail(a->ensemble_instruction[i]);
        printf("\n");
    }
}

/******/