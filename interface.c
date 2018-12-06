
/**
 * @author AMOKRANE Abdennour
 * 
 * "interface.c"
 * 
 * Pour controler l'interface principale de notre programme.
 * 
 * Contient les implementations des fonctions dans le fichier "interface.h"
 * 
 * **/

#include <stdio.h>

#include "interface.h"
#include "structure.h"
#include "biblio.h"

Automate **base_automate;
int nombre_automate=0;
void init_base_automate() {
    base_automate=(Automate **)malloc(MAX_BASE * sizeof(Automate *));
}

char fichier_decoration[30] = "start.dec";
FILE* ouvrir_fichier_deco() {
    FILE* fichier = fopen(fichier_decoration, "r");
    if (fichier == NULL) {
        perror("Erreur : ");
        return -1;
    }
    return fichier;
}

void aff_msg_debut() {
    FILE *fichier_debut = ouvrir_fichier_deco();
    char ligne[MAX_INT];
    char by_name[MAX_INT]; char title[MAX_INT];
    char github[MAX_INT];

    sprintf(by_name, "%s%s[*] By %s%sAMOKRANE %s%sAbdennour %s%s{ch@wi_ic0d3r};\n", KBLDON, KYEL, KNRM, 
                                    KBLDON, KCYN, KBLDON, KGRN, KBLDON, KYEL, KNRM);

    sprintf(title, "%s%s== [%s Finite Automaton API Project %s(FA-API) %s%s] -- [ %sDesigned and Implemented by %sAMOKRANE Abdennour %s%s] ==\n%s", 
    KBLDON, KYEL, KNRM, KGRN,KBLDON, KYEL, KNRM, KGRN, KBLDON, KYEL, KNRM);

    sprintf(github, "%s%s== [%s Check it on Github : %s%shttps://www.github.com/abdennour001/Finite-Automata-Project %s] ==\n%s", 
    KBLDON, KYEL, KNRM, KBLDON, KGRN, KYEL, KNRM);
    int count=0;
    while (fgets(ligne, MAX_INT,fichier_debut) != NULL) {
        char aig[MAX_INT];
        sprintf(aig , "%s%s%s", KBLDON, KYEL, ligne);
        if (count++ == 13) {
            aig[strlen(aig)-1] = '\0';
            sprintf(aig, "%s%s", aig, by_name);
        } else if (count == 18) {
            // author
            aig[strlen(aig)-1] = '\0';
            sprintf(aig, "%s%s", aig, title); 
        } else if (count == 19) {
            // github
            aig[strlen(aig)-1] = '\0';
            sprintf(aig, "%s%s",aig, github);
        }
        printf(aig);
    }
}

void aff_base_automate() {
    puts("");
    char database[MAX_INT];

    add
    sprintf(database, "%s%sBase des Automate\t--%s", KBLDON, KYEL, KNRM);
    for (int i=0; i<nombre_automate; i++) {
        if (i == 0) {
            sprintf(database, "%s%s%s|-[%s%s%s%s]%s\n", database, KBLDON, KYEL, KNRM, base_automate[i]->nom, KBLDON, KYEL, KNRM);
        } else {
            sprintf(database, "%s                          %s%s|-[%s%s%s%s]%s\n", database, KBLDON, KYEL, KNRM, base_automate[i]->nom, KBLDON, KYEL, KNRM);
        }	
    }
    printf(database);
}

void ajouter_automate_au_base(Automate *a) {
    base_automate[nombre_automate] = (Automate *) malloc(sizeof(Automate));
    base_automate[nombre_automate] = a;
    nombre_automate++;
}

void aff_menu_de_base__() {
    while (1) {
        char commande_msg[MAX_INT];
        aff_msg_debut();
        aff_base_automate(); puts("");
        add printf("%s%sAjouter une Automate à la base (%sset> %s%sadd %s@chemin_vers_fichier.init%s%s) %s\n", KBLDON, KYEL, KRED, KNRM, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");minus printf("%s%sSupprimer une Automate de la base (%sset> %s%sremove %s@nom_automate%s%s) %s\n", KBLDON, KYEL, KRED, KNRM, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");question printf("%s%sSelectionner une Automate (%sset> %s%sselect %s@nom_automate%s%s) %s\n", KBLDON, KYEL, KRED, KNRM, KRED, KNRM,KBLDON, KYEL,KNRM);
        puts("");puts("");  
        question printf("%s%sOperations binaire sur les Automates (%sset> %s@nom_A1 @numero_operation @nom_A2%s%s) %s", KBLDON, KYEL, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");printf("\n\t");star printf("%s%sUnion %sA1 ∪ A2%s (1)", KBLDON, KYEL, KGRN, KNRM);
        printf("\n\t");star printf("%s%sConcaténation %sA1 ∘ A2%s (2)", KBLDON, KYEL, KGRN, KNRM);puts("");

        puts("");minus printf("%s%sQuitter le programme (%sset> %sexit%s%s) %s", KBLDON, KYEL, KRED, KNRM, KBLDON, KYEL,KNRM);

        puts("");puts("");printf("%s%sset> %s", KBLDON, KRED, KNRM);
        char input[MAX_INT]; char **lex; int len;
        fgets(input, MAX_INT, stdin);
        lex = separer_chaine(input, " \n", &len);
        switch (len) {
            case 1:
                // exit
                if (!strcmp(lex[0], "exit")) {
                    exit(0);
                }
                break;
            case 2:
                // operation unitaire
                if (!strcmp(lex[0], "add")) {
                    // ajouter automate
                    puts("add");
                    Automate *automate=nouvelle_automate(lex[1]);
                    ajouter_automate_au_base(automate);
                    
                } else if(!strcmp(lex[0], "remove")) {
                    // supprimer automate 
                    puts("remove");
                } else if (!strcmp(lex[0], "select")) {
                    // selectionner une automate
                    puts("select");
                }
                break;
            case 3:
                // operation binaire
                if (!strcmp(lex[1], "1")) {
                    // Union
                    puts("1");
                } else if(!strcmp(lex[1], "2")) {
                    // Concatenation
                    puts("1");  
                }
                break;
            default:
                break;
        }
        free(lex);
    }
}

char *lire_nom_automate() {
    char mot__[MAX_INT]; char **__mot__; int l;
    printf("%s%s[?]%s Faire entrée le nom de fichier .init qui contien l'automate : %s%s[regex : letter_1.lettre_2.(...)]\n\n%s>>> %s", KGRN, KBLDON, KNRM ,KGRN, KBLDON, KRED, KNRM);
    scanf("%s", mot__);printf("\n");
    __mot__ = separer_chaine(mot__, ".\n", &l);
    Mot *mot_retour = creer_mot(l, __mot__);     
    return mot_retour;
}

void aff_chemin_reussi(Automate *automate, Mot *mot) {

    Instruction** ensemble_path;
    int vect[MAX_INT]; int i;
    ensemble_path = rechercher_chemins_reussi(automate, mot, vect, &i);

    if (!i) {
        printf("%s%s[!]%s Le mot n'est pas reconnue par l'automate %s%s%s%s.\n", KBLDON, KRED ,KNRM ,KBLDON, KGRN,automate->nom, KNRM);
        return;
    } else if (i != 1) {
        printf("%s%s[*] %sIl exist %s%s%d %schemins réussi.\n", KBLDON, KGRN, KNRM, KBLDON, KGRN, i, KNRM);
        printf("%s%s[?] %sAfficher ces chemins ? %s%s[Y/n] %s", KBLDON, KGRN, KNRM, KBLDON, KRED, KNRM);
        char c;
        scanf(" %c", &c);
        switch (c) {
            case 'Y':
                break;
            case 'y':
                break;
            case 'n':
                return;
                break;
            case 'N':
                return;
                break;
            default:
                return;
                break;
        }
    } else if (i == 1) {
        printf("%s%s[*] %sIl exist %s%s1 %schemin réussi.\n", KBLDON, KGRN, KNRM, KBLDON, KGRN, KNRM);
        printf("%s%s[?] %sAfficher ce chemin ? %s%s[Y/n] %s", KBLDON, KGRN, KNRM, KBLDON, KRED, KNRM);
        char c;
        scanf(" %c", &c);
        switch (c) {
            case 'Y':
                break;
            case 'y':
                break;
            case 'n':
                return;
                break;
            case 'N':
                return;
                break;
            default:
                return;
                break;
        }
    }

    puts("");
    printf("%s%s[!] %s%s=>( Si ) %sest un état initiale.\n",KBLDON, KYEL, KBLDON, KWHT, KNRM);
    printf("%s%s[!] %s%s( Sf )* %sest un état finale.\n",KBLDON, KYEL, KBLDON, KRED, KNRM);
    puts("");


    int s=0;
    for (int o=0; o<i;o++) {
        printf("%s%s[-] %s%sChemin %s%s#%d%s\n", KBLDON, KYEL, KBLDON, KYEL, KBLDON, KYEL, o+1, KNRM);
        if (vect[o]-1 == -1 && !strcmp(mot->vecteur_mot[0], EPSILON)) {
            printf("%s%s=>", KBLDON, KWHT);printf("( %s ) %s", automate->etat_init->nom, KNRM);
            printf("%s%s-[%s ", KBLDON,KYEL, KNRM);printf("~");printf(" %s%s]->%s", KBLDON,KYEL, KNRM);
            printf(" %s%s( %s )*%s", KBLDON, KRED,automate->etat_init->nom, KNRM);
        }
        for (int u=vect[o]-1; u>=0; u--) {
            if (u == vect[o] - 1) {        
                printf("%s%s=>", KBLDON, KWHT);printf("( %s ) %s", ensemble_path[u+s]->etat_src->nom, KNRM);
                printf("%s%s-[%s ", KBLDON,KYEL, KNRM);afficher_mot(ensemble_path[u+s]->mot);printf(" %s%s]->%s", KBLDON,KYEL, KNRM);
                printf(" %s%s( %s%s %s%s)%s ",KBLDON, KYEL, KBLDON, ensemble_path[u+s]->etat_dest->nom, KBLDON, KYEL, KNRM);
            } else if (u > 0) {
                printf("%s%s-[%s ", KBLDON,KYEL, KNRM);afficher_mot(ensemble_path[u+s]->mot);printf(" %s%s]->%s", KBLDON,KYEL, KNRM);
                printf(" %s%s( %s%s %s%s)%s ",KBLDON, KYEL, KBLDON, ensemble_path[u+s]->etat_dest->nom, KBLDON, KYEL, KNRM);
            } else if (u == 0) {
                printf("%s%s-[%s ", KBLDON,KYEL, KNRM);afficher_mot(ensemble_path[u+s]->mot);printf(" %s%s]->%s", KBLDON,KYEL, KNRM);
                printf(" %s%s( %s )*%s\n", KBLDON, KRED,ensemble_path[u+s]->etat_dest->nom, KNRM);
            }
            //afficher_instruction_sans_detail(ensemble_path[u+s]);
        }
        puts("");
        s += vect[o];
    }
}

Mot *lire_mot() {
    char mot__[MAX_INT]; char **__mot__; int l;
    printf("%s%s[?]%s Faire entrée un mot : %s%s[regex : letter_1.lettre_2.(...)]\n\n%s>>> %s", KGRN, KBLDON, KNRM ,KGRN, KBLDON, KRED, KNRM);
    scanf("%s", mot__);printf("\n");
    __mot__ = separer_chaine(mot__, ".\n", &l);
    Mot *mot_retour = creer_mot(l, __mot__);
    return mot_retour;
}