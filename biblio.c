
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
#include <math.h>
#include "externe/structure.h"


char fichier_init[30];
int marquer_vecteur[MAX_INT];
int __INIT__=1;

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

int deux_chaines_egale(char **ch1, char **cha2, int l1, int l2) {
    
    if (l1 != l2) return 0;
    
    int vct1[MAX_INT];
    for (int l=0; l<l1; l++) {
        vct1[l] = 0;
    }
    for (int i=0; i<l1; i++) {
        for (int j=0; j<l2; j++) {
            if (!strcmp(ch1[i], cha2[j])) {
                vct1[i] = 1;
                break;
            }
        }
        if (!vct1[i]) return 0;
    }
    return 1;
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

    char** aig_etat; char** aig_mot = malloc(MAX_INT * sizeof(char*));

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
        char* sauv=(char *)malloc(MAX_INT * sizeof(char));
        
        // pour elimine les escpaces 
        char* sauv_src=(char *)malloc(MAX_INT * sizeof(char));
        char* sauv_dest=(char *)malloc(MAX_INT * sizeof(char));

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
        etat_src_ = rechercher_etat_par_nom(ensemble_etats, nombre_etats,aig_etat[0]);
        if (type_instruction == 3) {
            strcpy(sauv_dest, aig_etat[2]);
            strcpy(aig_etat[2], separer_chaine(sauv_dest, " ", &i)[0]);
            etat_dest_ = rechercher_etat_par_nom(ensemble_etats, nombre_etats,aig_etat[2]);
        } else {
            strcpy(sauv_dest, aig_etat[1]);
            strcpy(aig_etat[1], separer_chaine(sauv_dest, " ", &i)[0]);
            etat_dest_ = rechercher_etat_par_nom(ensemble_etats, nombre_etats,aig_etat[1]);
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
                    /*mise_a_jour_etat(automate, automate->ensemble_instruction[w]->etat_src,
                        automate->ensemble_instruction[w]->etat_src->id,
                        automate->ensemble_instruction[w]->etat_src->nom, 
                        FINAL);*/
                    // a nouveau
                    switch (automate->ensemble_instruction[w]->etat_src->status) {
                        case INITIAL:
                            mise_a_jour_etat(automate, automate->ensemble_instruction[w]->etat_src,
                            automate->ensemble_instruction[w]->etat_src->id,
                            automate->ensemble_instruction[w]->etat_src->nom, 
                            INITIAL_FINAL);
                            break;
                        case NORMAL:
                            mise_a_jour_etat(automate, automate->ensemble_instruction[w]->etat_src,
                            automate->ensemble_instruction[w]->etat_src->id,
                            automate->ensemble_instruction[w]->etat_src->nom, 
                            FINAL);
                            break;
                        case FINAL:
                            // pass
                            break;
                        case INITIAL_FINAL:
                            // pass
                            /*mise_a_jour_etat(automate, automate->ensemble_instruction[w]->etat_src,
                            automate->ensemble_instruction[w]->etat_src->id,
                            automate->ensemble_instruction[w]->etat_src->nom, 
                            INITIAL_FINAL);*/
                            break;
                    } 

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
    Etat* nouveau_etat_init;
    Etat *ensemble_nouveau_etat[MAX_INT]; int nombre_etats=0;
    Instruction *ensemble_nouveau_instruction[MAX_INT]; int nombre_instructions=0;
    Etat *ensemble_nouveau_etat_finaux[MAX_INT]; int nombre_etats_finaux=0;
    Alphabet *nouvelle_alphabet;
    Automate *nouvelle_auto;
    char nom_etat[MAX_INT];
    Etat *etat_dest;

    nouveau_etat_init = automate->etat_init;
    ensemble_nouveau_etat[nombre_etats++] = nouveau_etat_init;

    empiler(&pile_sys, automate->etat_init);

    while ((etat_aig = depiler(&pile_sys)) != NULL) {
        for (int i=0; i < automate->alphabet->nombre_lettres; i++) {
            Etat* ensemble_interne_etat[MAX_INT]; int j=-1; Status s=NORMAL;
            for (int l=0; l<automate->nombre_instructions; l++) {
                // a commenter ida thardet XD
                char **les_etats_prec;
                char nom[MAX_INT];
                strcpy(nom, etat_aig->nom); int long_;
                les_etats_prec = separer_chaine(nom, " ;\n", &long_);
                for (int k=0; k<long_; k++) {
                    //printf("%s - %d _ ", les_etats_prec[k], long_);
                    Etat *e=rechercher_etat_par_nom(automate->ensemble_etat, automate->nombre_etat, les_etats_prec[k]);
                    if (!strcmp(automate->ensemble_instruction[l]->etat_src->nom, e->nom) && !strcmp(automate->ensemble_instruction[l]->mot->vecteur_mot[0], automate->alphabet->ensemble_lettres[i])) {
                        // ajouter l'état si'il n'existe pas
                        if (rechercher_etat_par_nom(ensemble_interne_etat, j+1, automate->ensemble_instruction[l]->etat_dest->nom) == NULL) {
                            ensemble_interne_etat[++j] = automate->ensemble_instruction[l]->etat_dest;
                        }
                        //afficher_etat(ensemble_interne_etat[j]);
                        if (automate->ensemble_instruction[l]->etat_dest->status == FINAL) {
                            s = FINAL;
                        }
                    }
                }
                //
            }
            if (j != -1) {
                int exist=0;
                strcpy(nom_etat, "");
                sprintf(nom_etat, "%s", ensemble_interne_etat[0]->nom);
                for (int o=1; o <= j; o++) {
                    sprintf(nom_etat, "%s;%s", nom_etat, ensemble_interne_etat[o]->nom);
                }

                for (int t=0; t<nombre_etats; t++) {
                    // ensemble ch1
                    char **cha1; int l1;
                    char sauv_nom_etat[MAX_INT];
                    strcpy(sauv_nom_etat, nom_etat);
                    cha1 = separer_chaine(sauv_nom_etat, " ;\n", &l1);
                    // ensemble ch2
                    char **cha2; int l2;
                    char nom_etat_2[MAX_INT];
                    strcpy(nom_etat_2, ensemble_nouveau_etat[t]->nom);
                    cha2 = separer_chaine(nom_etat_2, " ;\n", &l2);

                    //printf("*%s*%s*", nom_etat, ensemble_nouveau_etat[t]->nom);

                    /*printf("cha1 %d:", l1);
                    for (int b0=0; b0<l1; b0++) {
                        printf("+%s+", cha1[b0]);
                    }

                    printf("cha2 %d:", l2);
                    for (int b0=0; b0<l2; b0++) {
                        printf("+%s+", cha2[b0]);
                    }*/

                    //printf("/%d/", deux_chaines_egale(cha1, cha2, l1, l2));
                    //int g;scanf("%d", &g);

                    if (deux_chaines_egale(cha1, cha2, l1, l2)) {
                        exist = 1;
                        etat_dest = ensemble_nouveau_etat[t];
                        break;
                    }
                }

                if (!exist) {
                    Etat *nouveau_etat=creer_etat(++ID_ETAT_SYS, nom_etat, s);
                    ensemble_nouveau_etat[nombre_etats++] = nouveau_etat;
                    if (s == FINAL) {
                        ensemble_nouveau_etat_finaux[nombre_etats_finaux++] = nouveau_etat;
                    }
                    empiler(&pile_sys, nouveau_etat);           
                    etat_dest = nouveau_etat;
                }
                char *nouveau_vect_mot[MAX_INT];
                nouveau_vect_mot[0] = (char *) malloc(MAX_INT * sizeof(char));
                strcpy(nouveau_vect_mot[0], automate->alphabet->ensemble_lettres[i]);
                Mot *nouvelle_mot=creer_mot(1, nouveau_vect_mot);
                //afficher_etat(etat_dest);
                Instruction *inst=creer_instruction(++ID_INSTRUCTION_SYS, nouvelle_mot, etat_aig, etat_dest);
                // banch-mark test
                //afficher_instruction(inst);puts("\n");//int m;scanf("%d", &m);
                ensemble_nouveau_instruction[nombre_instructions++] = inst;
                //puts("");
            }
        }
        // banch-mark test
        //afficher_etat(etat_aig);puts("\n");
    }

    nouvelle_alphabet = automate->alphabet;
    char nom_automate[MAX_INT];
    sprintf(nom_automate, "%s_Version_deterministe", automate->nom);
    nouvelle_auto = creer_automate(nombre_etats, nombre_etats_finaux, nombre_instructions, nom_automate, nouvelle_alphabet, nouveau_etat_init, ensemble_nouveau_etat, ensemble_nouveau_etat_finaux, ensemble_nouveau_instruction);
    return nouvelle_auto;

}

int index_dans_ensemble(Etat **ensemble_etats, int nombre_etats, Etat *etat) {
    for (int i=0; i<nombre_etats; i++) {
        if (strcmp(ensemble_etats[i]->nom, etat->nom) == 0) {
            return i;
        }
    }
    return -1;   
}

void init_marquer_vecteur(Automate *automate) {
    for (int i=0; i<automate->nombre_etat; i++) {
        marquer_vecteur[i] = 0;
    }
}

void depth_first_search(Automate *automate, Etat *etat_initial_de_parcoure) {
    afficher_etat(etat_initial_de_parcoure);
    puts("");
    if (__INIT__) {
        init_marquer_vecteur(automate);
        __INIT__ = 0;
    }
    for (int i=0; i<automate->nombre_instructions; i++) {
        if (!strcmp(automate->ensemble_instruction[i]->etat_src->nom, etat_initial_de_parcoure->nom)) {
            int index = index_dans_ensemble(automate->ensemble_etat, automate->nombre_etat, automate->ensemble_instruction[i]->etat_dest);
            if (!marquer_vecteur[index]) {
                marquer_vecteur[index] = 1;
                depth_first_search(automate, automate->ensemble_instruction[i]->etat_dest);
            }
        }
    }
}


void chemin_entre_etats(Automate *automate, Etat *etat_depart, Etat *etat_arrive, int *return_value) {
    if (!strcmp(etat_depart->nom, etat_arrive->nom)) {
        *return_value=1;
    }
    if (__INIT__) {
        init_marquer_vecteur(automate);
        __INIT__ = 0;
    }
    for (int i=0; i<automate->nombre_instructions; i++) {
        if (!strcmp(automate->ensemble_instruction[i]->etat_src->nom, etat_depart->nom)) {
            int index = index_dans_ensemble(automate->ensemble_etat, automate->nombre_etat, automate->ensemble_instruction[i]->etat_dest);
            if (!marquer_vecteur[index]) {
                marquer_vecteur[index] = 1;
                chemin_entre_etats(automate, automate->ensemble_instruction[i]->etat_dest, etat_arrive, return_value);
            }
        }
    }
}

int etat_est_accessible(Automate* a, Etat* etat) {
    int return_value=0;
    chemin_entre_etats(a, a->etat_init, etat, &return_value);
    __INIT__ = 1;
    return return_value;
}

int etat_est_Co_accessible(Automate* a, Etat* etat) {
    int return_value=0;
    for(int i=0; i<a->nombre_etats_finaux; i++) {
        chemin_entre_etats(a, etat, a->ensemble_etat_finaux[i], &return_value);
        __INIT__ = 1;
        if (return_value) {
            return 1;
        }
    }
    return 0;
}

int verifier_facteur_gauche(Mot *mot1, Mot *mot2) {
    if (mot1->longeur < mot2->longeur) return 0;
    for (int i=0; i<mot2->longeur; i++) {
        if (strcmp(mot1->vecteur_mot[i], mot2->vecteur_mot[i])) return 0;
    }
    return 1;
} 

Mot *eclater_mot(Mot *mot, int l) {
    if (mot->longeur < l) return NULL;
    Mot *mot__=creer_mot(mot->longeur, mot->vecteur_mot);
    for (int i=l; i<mot__->longeur; i++) {
        mot__->vecteur_mot[i-l] = mot__->vecteur_mot[i];
    }
    mot__->longeur = mot__->longeur - l;
    if (!mot__->longeur) {
        mot__->longeur = 1;
        mot__->vecteur_mot[0] = "~";
    }
    return mot__;
}

 /** Retourne tous les chemins réussi à la lecture du mot "mot_input" dans un vecteur

    chaque taille d'un chemin réussi "i" est dans "vect_taille[i]", nombre_chemin_reussi contien le nobmbre des chemins trouvés  
**/

Instruction **rechercher_chemins_reussi(Automate *automate, Mot *mot, int vect_taille[], int *nombre_chemin_reussi) {
    Instruction **ensemble_chemin_reussi=malloc(MAX_INT * sizeof(Instruction));
    Pile_etat_mot *pile_sys=NULL;
    *nombre_chemin_reussi=0;

    /****/
    Mot *marqueur_instruction[automate->nombre_instructions];

    for (int i=0; i<automate->nombre_instructions; i++) {
        char **vect__ = malloc(sizeof(char *));
        vect__[0] = malloc(30 * sizeof(char));
        strcpy(vect__[0], "XXXXXXX");
        Mot *mot_vide=creer_mot(1, vect__);
        marqueur_instruction[i] = mot_vide;
    }
    /****/
    
    // empiler l'état initial
    PEtat_mot *etat_mot_aig = creer_etat_mot(automate->etat_init, mot);
    empiler_etat_mot(&pile_sys, etat_mot_aig);


    while (!pilevide_etat_mot(pile_sys)) {

        PEtat_mot *sauv=creer_etat_mot(pile_sys->etat_mot->etat, pile_sys->etat_mot->mot);

        //afficher_pile_etat_mot(pile_sys);puts("");


        for (int i=0; i<automate->nombre_instructions; i++) {

            if (!strcmp(automate->ensemble_instruction[i]->etat_src->nom, pile_sys->etat_mot->etat->nom)) {
                // nous somme dans l'instruction
                //afficher_mot(marqueur_instruction[i]);printf("--");afficher_mot(pile_sys->etat_mot->mot);
                //printf("%d**", mot_compare(marqueur_instruction[i], pile_sys->etat_mot->mot));
                //printf("%d==", verifier_facteur_gauche(pile_sys->etat_mot->mot, automate->ensemble_instruction[i]->mot));
                if ( (!mot_compare(marqueur_instruction[i], pile_sys->etat_mot->mot)) && verifier_facteur_gauche(pile_sys->etat_mot->mot, automate->ensemble_instruction[i]->mot)) {
                    PEtat_mot *etat_mot_aig = creer_etat_mot(automate->ensemble_instruction[i]->etat_dest, eclater_mot(pile_sys->etat_mot->mot, automate->ensemble_instruction[i]->mot->longeur));
                    //afficher_mot(marqueur_instruction[i]);printf("--");afficher_mot(pile_sys->etat_mot->mot);puts("");
                    if (!instr_est_boucle(automate->ensemble_instruction[i])) {
                        marqueur_instruction[i] = pile_sys->etat_mot->mot;
                    }
                    //printf("Empiler : ");afficher_etat(etat_mot_aig->etat);printf(" <> ");afficher_mot(etat_mot_aig->mot);puts("");
                    empiler_etat_mot(&pile_sys, etat_mot_aig);
                }
            }
            // tester si le mot restant est EPSILON et l'etat est final
        }

        //afficher_pile_etat_mot(pile_sys);puts("");


        //int k;scanf("%d", &k);

        if (((pile_sys->etat_mot->etat->status == FINAL || pile_sys->etat_mot->etat->status == INITIAL_FINAL) &&
            (!strcmp(pile_sys->etat_mot->mot->vecteur_mot[0], EPSILON))) || ((!strcmp(pile_sys->etat_mot->etat->nom, sauv->etat->nom)) && (pile_sys->etat_mot->mot->longeur == sauv->mot->longeur))
         ) {
                if (((pile_sys->etat_mot->etat->status == FINAL || pile_sys->etat_mot->etat->status == INITIAL_FINAL) &&
                    (!strcmp(pile_sys->etat_mot->mot->vecteur_mot[0], EPSILON)))) {
                        printf("DONE === \n");
                        afficher_pile_etat_mot(pile_sys);
                        printf("DONE === \n");
                }
                PEtat_mot *p=NULL;
                //puts("BEGIN");
                p = depiler_etat_mot(&pile_sys);
                //printf("Depiler : ");afficher_etat(p->etat);printf(" <> ");afficher_mot(p->mot);puts(sauv->etat->nom);puts("");

                while (1) {
                    //afficher_pile_etat_mot(pile_sys);puts("");
                    if (pile_sys != NULL && !strcmp(pile_sys->etat_mot->etat->nom, p->etat->nom)) {
                        //afficher_pile_etat_mot(pile_sys);
                        p = depiler_etat_mot(&pile_sys);
                        //printf("%d ---- ", p != NULL && !strcmp(p->etat->nom, sauv->etat->nom));
                        //printf("Depiler : ");afficher_etat(p->etat);printf(" <> ");afficher_mot(p->mot);puts("");
                    } else {
                        break;
                    }
                }
        }
    }
    return ensemble_chemin_reussi;
}

/****/

/****/