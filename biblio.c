
/**
 * @author AMOKRANE Abdennour
 * 
 * "biblio.c"
 * 
 * Implementation des fonctions de "biblio.h"
 * 
 * **/

#include "biblio.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "externe/structure.h"


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

    splits = (char** )malloc(MAX_INT * sizeof(char));
    token = strtok(chaine, separateur);
    while (token != NULL) {
        splits[i] = (char* ) malloc(MAX_INT * sizeof(char));
		strcpy(splits[i], token);
        i++;
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
    nom_alphabet = (char* )malloc(30 * sizeof(char));
    nom_automate = (char* )malloc(30 * sizeof(char));

    // Lire ligne par ligne
    while (fgets(ligne, len, _fichier_init_) != NULL) {
        //puts(ligne);
        switch (++num_ligne) {
            case 2:
                strcpy(nom_automate, separer_chaine(ligne, " \n", &i)[0]);
                //printf("Nom de l'automate : %s\n", nom_automate);
                break;
            case 3:
                aig3 = separer_chaine(ligne, " \n", &i);
                strcpy(nom_alphabet, aig3[0]);
                nombre_lettres = converter_chaine_entier(aig3[1]);
                //printf("Nom de l'alphabet : %s, %d\n", nom_alphabet, nombre_lettres);
                free(aig3);
                break;
            case 4:
                aig = separer_chaine(ligne, " \n", &i);
                nombre_etats = converter_chaine_entier(aig[0]);
                //printf("Nombre d'états : %d\n", nombre_etats);
                free(aig);
                break;
            case 5:
                aig = separer_chaine(ligne, " \n", &i);
                nombre_instructions = converter_chaine_entier(aig[0]);
                //printf("Nombre d'instruction : %d\n", nombre_instructions);
                free(aig);
                break;
            case 6:
                aig6 = separer_chaine(ligne, " \n", &i);
                alphabet = aig6;
                /*for(int j=0; alphabet[j] != NULL; j++) {
                    //puts(aig6[j]);
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

    Etat** ensemble_etats_init; int nombre_etats_init=0; // ensemble des etats initiaux
    Etat** ensemble_etats; // ensemble des etats
    Etat** ensemble_etats_finaux; // ensemble des etats finaux
    Instruction** ensemble_instruction; // ensemble des instructions
    Etat* etat_init;

    ensemble_etats_init = (Etat** ) malloc(MAX_INT * sizeof(Etat)); // Allouer nombre_etats au max pour les etats initiaux
    ensemble_instruction = malloc(MAX_INT * sizeof(Instruction)); // Allouer nombre_instruction Instruction dans la memoire
    ensemble_etats = malloc(MAX_INT * sizeof(Etat)); // Allouer nombre_etat Etat dans la memoire
    ensemble_etats_finaux = malloc(MAX_INT * sizeof(Etat));

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
                ensemble_etats_init[nombre_etats_init] = malloc(sizeof(Etat));
                etat_ = creer_etat(++ID_ETAT_SYS, etat[0], INITIAL);
                ensemble_etats_init[nombre_etats_init++] = etat_;
            } else if (strcmp(etat[1], "INIT&FINAL") == 0) {
                etat_ = creer_etat(++ID_ETAT_SYS, etat[0], INITIAL_FINAL);
                // ajouter final
                ensemble_etats_finaux[nombre_etats_finaux] = malloc(sizeof(Etat));
                ensemble_etats_finaux[nombre_etats_finaux++] = etat_;
                // ajouter initial 
                ensemble_etats_init[nombre_etats_init] = malloc(sizeof(Etat));
                ensemble_etats_init[nombre_etats_init++] = etat_;
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
            aig_mot[0] = (char *)malloc(sizeof(char));
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
        instruction_ = creer_instruction(++ID_INSTRUCTION_SYS, mot_, etat_src_, etat_dest_);
        ensemble_instruction[o] = instruction_;
    }

    /* Faire la transition EPSILON des états initiaux */

    if (nombre_etats_init == 1) { // un seul état initiale
        etat_init = ensemble_etats_init[0];
    } else { // plusieur états initaux
        char nom_init[30]; char** mot_epsilon=(char**) malloc(sizeof(char));
        mot_epsilon[0] = malloc(sizeof(char));
        strcpy(mot_epsilon[0], EPSILON);
        Mot* mot=creer_mot(1, mot_epsilon);
        sprintf(nom_init, "Si_%d", ++ID_ETAT_SYS);
        Etat* _etat_init_ = creer_etat(ID_ETAT_SYS, nom_init, INITIAL);
        ensemble_etats[nombre_etats++] = _etat_init_;
        etat_init = _etat_init_;
        for (int x=0; x<nombre_etats_init; x++) {
            if (ensemble_etats_init[x]->status == INITIAL_FINAL) {
                ensemble_etats_init[x]->status = FINAL;
            } else {
                ensemble_etats_init[x]->status = NORMAL;
            }
            Instruction* i_epsilon=creer_instruction(++ID_INSTRUCTION_SYS, mot, etat_init, ensemble_etats_init[x]);
            ensemble_instruction[nombre_instructions] = (Instruction*) malloc(sizeof(Instruction));
            ensemble_instruction[nombre_instructions++] = i_epsilon; 
        }
    }

    /**/

    // Creation de l'automate
    Automate *automate;
    automate = creer_automate(nombre_etats, nombre_etats_finaux, nombre_instructions, nom_automate, alph, etat_init, ensemble_etats, ensemble_etats_finaux, ensemble_instruction);
    return automate;
}

void concat_chaine(char *a, char *b) {  // Concatener a et b, le resultat dans a.
    strcat(a, b);
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

Automate* nouvelle_automate(char* nom_fichier_init) {
    Automate* automate=lire_fichier_init(nom_fichier_init);
    return automate;
}

/****/

/** API de manupilation des Automates **/

int auto_est_simple(Automate* automate) {
    for (int i=0; i<automate->nombre_instructions; i++) {
        if (automate->ensemble_instruction[i]->mot->longeur > 1 || !strcmp(automate->ensemble_instruction[i]->mot->vecteur_mot[0], EPSILON)) {
            return 0;
        }
    }
    return 1;
}

int auto_est_deterministe(Automate* automate) {
    if (!auto_est_simple(automate)) return 0;
    int cpt_vec[automate->alphabet->nombre_lettres];

    for (int i=0; i<automate->nombre_etat; i++) {
        // initialisé le vecteur des compteurs à 0 pour chaque état.
        for (int b=0; b<automate->alphabet->nombre_lettres; b++) {
            cpt_vec[b] = 0;
        }
        for (int j=0; j<automate->nombre_instructions; j++) {
            if (!strcmp(automate->ensemble_instruction[j]->etat_src->nom, automate->ensemble_etat[i]->nom)) {
                for (int k=0; k<automate->alphabet->nombre_lettres; k++) {
                    if (!strcmp(automate->ensemble_instruction[j]->mot->vecteur_mot[0], automate->alphabet->ensemble_lettres[k])) {
                        if (++cpt_vec[k] > 1) goto non_det;
                        break;
                    }
                }
            }
        }
    }
    return 1;
    non_det:
    return 0;
}

int auto_est_complet(Automate* automate) {
    if (!auto_est_simple(automate)) return 0;
    int cpt_vec[automate->alphabet->nombre_lettres];

    for (int i=0; i<automate->nombre_etat; i++) {
        // initialisé le vecteur des compteurs à 0 pour chaque état.
        for (int b=0; b<automate->alphabet->nombre_lettres; b++) {
            cpt_vec[b] = 0;
        }
        for (int j=0; j<automate->nombre_instructions; j++) {
            if (!strcmp(automate->ensemble_instruction[j]->etat_src->nom, automate->ensemble_etat[i]->nom)) {
                for (int k=0; k<automate->alphabet->nombre_lettres; k++) {
                    if (!strcmp(automate->ensemble_instruction[j]->mot->vecteur_mot[0], automate->alphabet->ensemble_lettres[k])) {
                        cpt_vec[k]++;
                    }
                }
            }
        }
        for (int l=0; l<automate->alphabet->nombre_lettres; l++) {
            if (cpt_vec[l] < 1) {
                return 0;
            }
        }
    }
    return 1;
}

int rendez_simple(Automate* automate) {
    // élimination des transitions par mots

    // ensemble des instructions à éliminer
    Instruction **ensemble_a_eliminer = (Instruction **) malloc(automate->nombre_instructions * sizeof(Instruction)); // au max
    int elm_ = 0;
    int etat_=0;
    // ensemble des instructions à ajouter
    Instruction **ensemble_a_ajouter = (Instruction **) malloc(automate->nombre_instructions * sizeof(Instruction)); // au max
    int ajouter_ = 0;

    for (int i=0; i<automate->nombre_instructions; i++) {
        etat_ = 0;
        if (automate->ensemble_instruction[i]->mot->longeur > 1) {
            ensemble_a_eliminer[elm_++] = automate->ensemble_instruction[i];
            for (int o=0; o<automate->ensemble_instruction[i]->mot->longeur; o++) {
                char** vecteur_mot=(char** ) malloc(sizeof(char*));
                vecteur_mot[0] = malloc(MAX_INT * sizeof(char));
                strcpy(vecteur_mot[0], automate->ensemble_instruction[i]->mot->vecteur_mot[o]);
                Mot* nouveau_mot = creer_mot(1, vecteur_mot);
                Instruction *nouvelle_inst=NULL;
                if (o==0) {
                    char *nom=(char *) malloc(MAX_INT * sizeof(char));
                    char *nom_src = (char *) malloc(MAX_INT * sizeof(char)), *nom_dest = (char *) malloc(MAX_INT * sizeof(char));
                    strcpy(nom_src, automate->ensemble_instruction[i]->etat_src->nom);
                    strcpy(nom_dest, automate->ensemble_instruction[i]->etat_dest->nom);
                    concat_chaine(nom_src, nom_dest);
                    strcpy(nom, nom_src);
                    sprintf(nom, "%s_%d", nom, etat_++);            
                    Etat* nouveau_etat=creer_etat(++ID_ETAT_SYS, nom, NORMAL);
                    ajouter_etat(automate,nouveau_etat);

                    nouvelle_inst = creer_instruction(++ID_INSTRUCTION_SYS, nouveau_mot, automate->ensemble_instruction[i]->etat_src, nouveau_etat);
                } else if(o==automate->ensemble_instruction[i]->mot->longeur - 1) {
                    nouvelle_inst = creer_instruction(++ID_INSTRUCTION_SYS, nouveau_mot, ensemble_a_ajouter[ajouter_-1]->etat_dest, automate->ensemble_instruction[i]->etat_dest);
                } else {
                    char *nom=(char *) malloc(MAX_INT * sizeof(char));
                    char *nom_src = (char *) malloc(MAX_INT * sizeof(char)), *nom_dest = (char *) malloc(MAX_INT * sizeof(char));
                    strcpy(nom_src, automate->ensemble_instruction[i]->etat_src->nom);
                    strcpy(nom_dest, automate->ensemble_instruction[i]->etat_dest->nom);
                    concat_chaine(nom_src, nom_dest);
                    strcpy(nom, nom_src);
                    sprintf(nom, "%s_%d", nom, etat_++);            
                    Etat* nouveau_etat=creer_etat(++ID_ETAT_SYS, nom, NORMAL);
                    ajouter_etat(automate,nouveau_etat);

                    nouvelle_inst = creer_instruction(++ID_INSTRUCTION_SYS, nouveau_mot, ensemble_a_ajouter[ajouter_-1]->etat_dest , nouveau_etat);
                }
                ensemble_a_ajouter[ajouter_++] = nouvelle_inst;
            }
        }
    }

    for (int p=0; p<elm_; p++) {
        supprimer_instruction(automate, ensemble_a_eliminer[p]);
    }

    for (int m=0; m<ajouter_; m++) {
        ajouter_instruction(automate, ensemble_a_ajouter[m]);
    }

    while (1) {
        ajouter_ = 0;
        elm_ = 0;

        // élimination des transitions stantanées EPSILON

        for (int w=0; w < automate->nombre_instructions; w++) {
            if (!strcmp(automate->ensemble_instruction[w]->mot->vecteur_mot[0], EPSILON)) {
                ensemble_a_eliminer[elm_++] = automate->ensemble_instruction[w];
                if (automate->ensemble_instruction[w]->etat_dest->status == FINAL || automate->ensemble_instruction[w]->etat_dest->status == INITIAL_FINAL) {
                //automate->ensemble_instruction[w]->etat_src->status = FINAL; 
                    mise_a_jour_etat(automate, automate->ensemble_instruction[w]->etat_src,
                        automate->ensemble_instruction[w]->etat_src->id,
                        automate->ensemble_instruction[w]->etat_src->nom, 
                        FINAL);
                }
                for (int y=0; y < automate->nombre_instructions; y++) {
                    if (automate->ensemble_instruction[y]->etat_src == automate->ensemble_instruction[w]->etat_dest) {
                        Instruction *i=automate->ensemble_instruction[y];
                        Mot* mot=creer_mot(i->mot->longeur, i->mot->vecteur_mot);
                        Instruction* inst=creer_instruction(++ID_INSTRUCTION_SYS, mot, automate->ensemble_instruction[w]->etat_src, i->etat_dest);       
                        ensemble_a_ajouter[ajouter_++] = inst;
                    }
                }
            }
        }

        for (int p=0; p<elm_; p++) {
            supprimer_instruction(automate, ensemble_a_eliminer[p]);
        }

        for (int m=0; m<ajouter_; m++) {
            ajouter_instruction(automate, ensemble_a_ajouter[m]);
        }
        if (!elm_) break;
    }

    return auto_est_simple(automate);
}

void rendez_complet(Automate* automate) {

    int cpt_vec[automate->alphabet->nombre_lettres];
    Instruction **ensemble_instr_a_ajouter=(Instruction **) malloc(MAX_INT * sizeof(Instruction));
    Etat *etat_puis=creer_etat(++ID_ETAT_SYS, "E_puit", NORMAL);
    int aig=1, ajouter_=0;

    for (int i=0; i<automate->nombre_etat; i++) {
        // initialisé le vecteur des compteurs à 0 pour chaque état.
        for (int i=0; i<automate->alphabet->nombre_lettres; i++) {
            cpt_vec[i] = 0;
        }
        for (int j=0; j<automate->nombre_instructions; j++) {
            if (!strcmp(automate->ensemble_instruction[j]->etat_src->nom, automate->ensemble_etat[i]->nom)) {
                for (int k=0; k<automate->alphabet->nombre_lettres; k++) {
                    if (!strcmp(automate->ensemble_instruction[j]->mot->vecteur_mot[0], automate->alphabet->ensemble_lettres[k])) {
                        cpt_vec[k]++;
                    }
                }
            }
        }
        for (int l=0; l<automate->alphabet->nombre_lettres; l++) {
            if (cpt_vec[l] < 1) {
                if (aig) { // ajouter les instructions manquante
                    aig = 0;
                    // ajouter l'etat a l'ensemble des etat
                    ajouter_etat(automate, etat_puis);
                }
                char **mot_vect=(char **) malloc(sizeof(char*));
                mot_vect[0] = (char *)malloc(MAX_INT * sizeof(char));
                strcpy(mot_vect[0], automate->alphabet->ensemble_lettres[l]);
                Mot *lettre=creer_mot(1, mot_vect);
                Instruction *instr=creer_instruction(++ID_INSTRUCTION_SYS, lettre, automate->ensemble_etat[i], etat_puis);
                ensemble_instr_a_ajouter[ajouter_++] = instr;
            }
        }
    }

    for (int i=0; i<ajouter_; i++) {
        ajouter_instruction(automate, ensemble_instr_a_ajouter[i]);
    }
}

Automate *rendez_deterministe(Automate* automate) {
    Pile *pile_sys=NULL; Etat* etat_aig;
    char file_immitation[MAX_INT];
    Etat *ensemble_nouveau_etat[MAX_INT]; int nouveau_etat_;

    sprintf(file_immitation, "DEBUT;\n");
    sprintf(file_immitation, "%s%s _deterministe_version < X, S0, F, S, II >\n", file_immitation, automate->nom);
    sprintf(file_immitation, "%s%s %d\n", file_immitation, automate->alphabet->nom, automate->alphabet->nombre_lettres);
    
    char etat_chaine[MAX_INT]; int nombre_etat=0;
    char instruction_chaine[MAX_INT]; int nombre_instruction=0;

    empiler(&pile_sys, automate->ensemble_etat[0]);

    while ((etat_aig = depiler(&pile_sys)) != NULL) {
        for (int i=0; i < automate->alphabet->nombre_lettres; i++) {
            Etat* ensemble_interne_etat[MAX_INT]; int j=-1;
            for (int l=0; l<automate->nombre_instructions; l++) {
                if (!strcmp(automate->ensemble_instruction[l]->etat_src->nom, etat_aig->nom)) {
                    ensemble_interne_etat[++j] = automate->ensemble_instruction[l]->etat_dest; 
                }
            }
            if (j != -1) {
                char nom_etat[MAX_INT];
                sprintf(nom_etat, "%s", ensemble_interne_etat[0]->nom);
                for (int o=1; o < j; o++) {
                    sprintf(nom_etat, "%s %s", nom_etat, ensemble_interne_etat[o]->nom);
                }
                Etat *nouveau_etat=creer_etat();
            }
        }
        afficher_etat(etat_aig);
    }

    // copying the alphabet
    sprintf(file_immitation, "%s%s", file_immitation, automate->alphabet->ensemble_lettres[0]);    
    for (int i=1; i<automate->alphabet->nombre_lettres; i++) {
        sprintf(file_immitation, "%s %s", file_immitation, automate->alphabet->ensemble_lettres[i]);
    }
    sprintf(file_immitation, "%s\n", file_immitation);

}

/****/

/****/