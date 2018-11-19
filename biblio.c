#include "biblio.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fichier_init[30];

FILE* ouvrir_fichier() {
    FILE* fichier = fopen(fichier_init, "r");
    if (fichier == NULL) {
        perror("Erreur : ");
        return -1;
    }
    return fichier;
}

/** Manupilation chaine de caractère pour lire le fichier .init **/

int converter_chaine_entier(char* chaine) {
    char* ptr;
    int n;
    n = strtol(chaine, &ptr, 10);
    return n;
}
char** separer_chaine(char* chaine, char* separateur, int *longeur) {
    char** splits;
    char* token;
    int i=0;
    splits = malloc(sizeof(char*));
    token = strtok(chaine, separateur);
	splits[i] = malloc(sizeof(char));
    while (token != NULL) {
		splits[i++] = token;
        token = strtok(NULL, separateur);
    }
    *longeur = i;
    return splits;
}

Automate* lire_fichier_init(char* nom_fichier_init) {

    strcpy(fichier_init, nom_fichier_init);

    char ligne[MAX_INT]; char* nom_automate; char* nom_alphabet;
    char** aig; char** alphabet; char** aig3; char** aig6;
    Alphabet* alph; // l'Alphabet
    int len=MAX_INT;
    int num_ligne=0, nombre_lettres=0, nombre_etats=0, nombre_instructions=0, i, nombre_etats_finaux=0;

    FILE* _fichier_init_ = ouvrir_fichier();
    if (_fichier_init_ == NULL) exit(-1);
    nom_alphabet = (char* )malloc(sizeof(char));

    // Lire ligne par ligne
    while (fgets(ligne, len, _fichier_init_) != NULL) {
        //puts(ligne);
        switch (++num_ligne) {
            case 2:
                nom_automate = separer_chaine(ligne, " \n", &i)[0];
                //printf("Nom de l'automate : %s\n", nom_automate);
                break;
            case 3:
                aig3 = separer_chaine(ligne, " \n", &i);
                strcpy(nom_alphabet, aig3[0]);
                nombre_lettres = converter_chaine_entier(aig3[1]);
                //printf("Nom de l'alphabet : %s, %d\n", nom_alphabet, nombre_lettres);
                break;
            case 4:
                aig = separer_chaine(ligne, " \n", &i);
                nombre_etats = converter_chaine_entier(aig[0]);
                //printf("Nombre d'états : %d\n", nombre_etats);
                break;
            case 5:
                aig = separer_chaine(ligne, " \n", &i);
                nombre_instructions = converter_chaine_entier(aig[0]);
                //printf("Nombre d'instruction : %d\n", nombre_instructions);
                break;
            case 6:
                aig6 = separer_chaine(ligne, " \n", &i);
                alphabet = aig6;
                /*for(int j=0; alphabet[j] != NULL; j++) {
                    //puts(alphabet[j]);
                }*/
                // Creation de l'alphabet.
                alph = creer_alphabet(nom_alphabet, nombre_lettres, alphabet);
                break;
            default:
                break;
        }
        if (num_ligne == 6) break;
    }

    // creation des états, des instructions, les ensembles d'état, les
    // ensemble d'états finauxn, l'état initial et l'ensemble des instruction.

    Etat** ensemble_etats; // ensemble des etats
    Etat** ensemble_etats_finaux; // ensemble des etats finaux
    Instruction** ensemble_instruction; // ensemble des instructions
    Etat* etat_init;

    ensemble_instruction = malloc(nombre_instructions * sizeof(Instruction)); // Allouer nombre_instruction Instruction dans la memoire
    ensemble_etats = malloc(nombre_etats * sizeof(Etat)); // Allouer nombre_etat Etat dans la memoire
    ensemble_etats_finaux = malloc(sizeof(Etat));

    char** aig_etat; char** aig_mot;

    for (int k=0; k<nombre_etats; k++) {
        Etat* etat_;
        char** etat;

        fgets(ligne, len, _fichier_init_);
        etat = separer_chaine(ligne, " \n", &i);

        if (etat[1] != NULL) {
            if (strcmp(etat[1], "FINAL") == 0) {
                ensemble_etats_finaux[nombre_etats_finaux] = malloc(sizeof(Etat));
                etat_ = creer_etat(++ID_ETAT_SYS, etat[0], FINAL);
                ensemble_etats_finaux[nombre_etats_finaux++] = etat_;
            } else if (strcmp(etat[1], "INIT") == 0) {
                etat_ = creer_etat(++ID_ETAT_SYS, etat[0], INITIAL);
                etat_init = etat_;
            }
        } else {
            etat_ = creer_etat(++ID_ETAT_SYS, etat[0], NORMAL);
        }
        ensemble_etats[k] = etat_;
    }

    for (int o=0; o<nombre_instructions; o++) {
        Instruction* instruction_;
        Mot* mot_;
        Etat* etat_src_; Etat* etat_dest_;
        int type_instruction; // 2 si instruction de type Si,,Sj transition stantané
                                // 3 sinon instruction de type (Si, mot, Sj) 

        fgets(ligne, len, _fichier_init_);
        aig_etat = separer_chaine(ligne, ",\n", &type_instruction);

        int nombre_lettre_mot_lecture=0;
        char* sauv=(char *)malloc(sizeof(char));
        
        // pour elimine les escpaces 
        char* sauv_src=(char *)malloc(sizeof(char));
        char* sauv_dest=(char *)malloc(sizeof(char));

        if (type_instruction == 3) {
            strcpy(sauv, aig_etat[1]);
            aig_mot = separer_chaine(sauv, " ", &nombre_lettre_mot_lecture);
        } else {
            strcpy(aig_mot[0], EPSILON);
            nombre_lettre_mot_lecture = 1;
        }
        
        mot_ = creer_mot(nombre_lettre_mot_lecture, aig_mot);

        strcpy(sauv_src, aig_etat[0]);
        strcpy(aig_etat[0], separer_chaine(sauv_src, " ", &i)[0]);
        etat_src_ = rechercher_etat_par_nom(ensemble_etats, aig_etat[0]);
        if (type_instruction == 3) {
            strcpy(sauv_dest, aig_etat[2]);
            strcpy(aig_etat[2], separer_chaine(sauv_dest, " ", &i)[0]);
            etat_dest_ = rechercher_etat_par_nom(ensemble_etats, aig_etat[2]);
        } else {
            strcpy(sauv_dest, aig_etat[1]);
            strcpy(aig_etat[1], separer_chaine(sauv_dest, " ", &i)[0]);
            etat_dest_ = rechercher_etat_par_nom(ensemble_etats, aig_etat[1]);
        }
        //afficher_etat(etat_src_);
        //afficher_etat(etat_dest_);
        //afficher_mot(mot_);
        instruction_ = creer_instruction(++ID_INSTRUCTION_SYS, mot_, etat_src_, etat_dest_);
        ensemble_instruction[o] = instruction_;
    }

    // Creation de l'automate
    Automate *automate;
    automate = creer_automate(nombre_etats, nombre_etats_finaux, nombre_instructions, nom_automate, alph, etat_init, ensemble_etats, ensemble_etats_finaux, ensemble_instruction);
    return automate;
}

/** API de creation des Automates **/
Etat* creer_etat(int id, char* nom, Status status) {
    Etat* etat=alloc_etat();
    set_id_etat(etat, id);
    set_status(etat, status);
    set_nom_etat(etat, nom);
    return etat;
}

Alphabet* creer_alphabet(char* nom, int nombre_lettres, char** ensemble_lettres) {
    Alphabet* a=alloc_alphabet();
    set_nom_alphabet(a, nom);
    set_ensemble_lettres(a, nombre_lettres, ensemble_lettres);
    return a;
}

Mot* creer_mot(int longeur, char** vecteur_mot) {
    Mot* mot=alloc_mot();
    set_vecteur_mot(mot, longeur, vecteur_mot);
    return mot;
}

Instruction* creer_instruction(int id, Mot* mot, Etat* etat_src, Etat* etat_dest) {
    Instruction* instruction=alloc_instruction();
    set_etat_src(instruction, etat_src);
    set_etat_dest(instruction, etat_dest);
    set_mot_instruction(instruction, mot);
    return instruction;
}

Automate* creer_automate(int n_e, int n_ef, int n_i, char* nom, Alphabet* alphabet, Etat* e_init, Etat** ensemble_etats, Etat** ensemble_etats_finaux, Instruction** ensemble_i) {
    Automate* a=alloc_automate();
    set_nom_automate(a, nom);
    set_nombre_etat(a, n_e);
    set_nombre_etat_finaux(a, n_ef);
    set_nombre_instruction(a, n_i);
    set_etat_init(a, e_init);
    set_alphabet(a, alphabet);
    set_ensemble_etat(a, ensemble_etats);
    set_ensemble_etat_finaux(a, ensemble_etats_finaux);
    set_ensemble_instruction(a, ensemble_i);
    return a;
}
/****/

/****/