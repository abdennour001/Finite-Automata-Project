
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

void aff_help(int i) {
    if (i == 1) {
        puts("");
        question printf("%s%sOperations Unaire sur l'Automates (%sset> %s@numero_operation%s%s) %s", KBLDON, KYEL, KRED, KNRM ,KBLDON, KYEL,KNRM);
        puts("");printf("\n\t");minus printf("%s%sAfficher l'automate %s (1)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sTester si l'automate est Simple %s (2)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sTester si l'automate est Complet %s (3)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sTester si l'automate est Deterministe %s (4)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sTester les états non accessible de l'automate %s (5)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sTester les états non Co-accessible de l'automate %s (6)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sRendez l'automate Simple %s (7)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sRendez l'automate Complet %s (8)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");minus printf("%s%sRendez l'automate Deterministe %s (9)", KBLDON, KYEL, KNRM);

        puts("");printf("\n\t");star printf("%s%sGenerer l'automate étoile %s (10)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");star printf("%s%sGenerer l'automate miroire %s (11)", KBLDON, KYEL, KNRM);
        puts("");printf("\n\t");star printf("%s%sGenerer l'automate complément %s (12)", KBLDON, KYEL, KNRM);


        puts("");puts("");alert printf("%s%sAfficher help (%sset> %shelp%s%s) %s", KBLDON, KYEL, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");minus printf("%s%sQuitter le programme (%sset> %sexit%s%s) %s", KBLDON, KYEL, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");  
    } else {
        aff_base_automate(); puts("");
        add printf("%s%sAjouter une Automate à la base (%sset> %s%sadd %s@chemin_vers_fichier.init%s%s) %s\n", KBLDON, KYEL, KRED, KNRM, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");minus printf("%s%sSupprimer une Automate de la base (%sset> %s%sremove %s@nom_automate%s%s) %s\n", KBLDON, KYEL, KRED, KNRM, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");question printf("%s%sSelectionner une Automate (%sset> %s%sselect %s@nom_automate%s%s) %s\n", KBLDON, KYEL, KRED, KNRM, KRED, KNRM,KBLDON, KYEL,KNRM);
        puts("");puts("");  
        question printf("%s%sOperations binaire sur les Automates (%sset> %s@nom_A1 @numero_operation @nom_A2%s%s) %s", KBLDON, KYEL, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");printf("\n\t");star printf("%s%sUnion %sA1 ∪ A2%s (1)", KBLDON, KYEL, KGRN, KNRM);
        printf("\n\t");star printf("%s%sConcaténation %sA1 ∘ A2%s (2)", KBLDON, KYEL, KGRN, KNRM);puts("");

        puts("");alert printf("%s%sAfficher help (%sset> %shelp%s%s) %s", KBLDON, KYEL, KRED, KNRM, KBLDON, KYEL,KNRM);
        puts("");minus printf("%s%sQuitter le programme (%sset> %sexit%s%s) %s", KBLDON, KYEL, KRED, KNRM, KBLDON, KYEL,KNRM);
    }
}

void aff_menu_automate(Automate *a) {
    aff_help(1);puts("");puts("");
    while (1) {
        char commande_msg[MAX_INT];
        printf("%s%sset> %s%s> %s", KBLDON, KRED, KGRN, a->nom, KNRM);
        char input[MAX_INT]; char **lex; int len;
        fgets(input, MAX_INT, stdin);
        lex = separer_chaine(input, " \n", &len);
        switch (len) {
            case 1:
                // exit
                if (!strcmp(lex[0], "exit")) {
                    star printf("L'automate %s%s%s%s a été dé-sélectionnée.", KBLDON, KGRN, a->nom, KNRM);
                    return;
                } else if (!strcmp(lex[0], "help")) {
                    aff_help(1);
                } else if (!strcmp(lex[0], "show")) {
                    aff_base_automate();
                } else if (!strcmp(lex[0], "1")) {
                    afficher_automate(a);
                } else if (!strcmp(lex[0], "2")) {
                    if (auto_est_simple(a)) {
                        star printf("L'automate %s%s%s%s est simple.", KBLDON, KGRN, a->nom, KNRM);
                    } else {
                        star printf("L'automate %s%s%s%s n'est pas simple.", KBLDON, KGRN, a->nom, KNRM);
                    }
                } else if (!strcmp(lex[0], "3")) {
                    if (auto_est_complet(a)) {
                        star printf("L'automate %s%s%s%s est complet.", KBLDON, KGRN, a->nom, KNRM);
                    } else {
                        star printf("L'automate %s%s%s%s n'est pas complet.", KBLDON, KGRN, a->nom, KNRM);
                    }
                } else if (!strcmp(lex[0], "4")) {
                    if (auto_est_deterministe(a)) {
                        star printf("L'automate %s%s%s%s est deterministe.", KBLDON, KGRN, a->nom, KNRM);
                    } else {
                        star printf("L'automate %s%s%s%s n'est pas deterministe.", KBLDON, KGRN, a->nom, KNRM);
                    }
                } else if (!strcmp(lex[0], "5")) {
                    int sauv=0;
                    for (int i=0; i<a->nombre_etat; i++) {
                        if (!etat_est_accessible(a, a->ensemble_etat[i])) {
                            star printf("L'état %s%s%s%s est un etat non accessible.\n", KBLDON, KGRN, a->ensemble_etat[i]->nom, KNRM); 
                            if (!sauv) sauv=1;
                        }
                    }
                    if (!sauv) {
                        alert printf("L'automate %s%s%s%s n'a pas des etats non accessible.", KBLDON, KGRN, a->nom, KNRM); 
                    }
                } else if (!strcmp(lex[0], "6")) {
                    int sauv=0;
                    for (int i=0; i<a->nombre_etat; i++) {
                        if (!etat_est_Co_accessible(a, a->ensemble_etat[i])) {
                            star printf("L'état %s%s%s%s est un etat non Co-accessible.\n", KBLDON, KGRN, a->ensemble_etat[i]->nom, KNRM); 
                            if (!sauv) sauv=1;
                        }
                    }
                    if (!sauv) {
                        alert printf("L'automate %s%s%s%s n'a pas des etats non Co-accessible.", KBLDON, KGRN, a->nom, KNRM);                         
                    }
                } else if (!strcmp(lex[0], "7")) {
                    alert printf("L'automate %s%s%s%s a été rendu simple.", KBLDON, KGRN, a->nom, KNRM);                    
                    rendez_simple(a);
                } else if (!strcmp(lex[0], "8")) {
                    alert printf("L'automate %s%s%s%s a été rendu complet.", KBLDON, KGRN, a->nom, KNRM);                    
                    rendez_simple(a);
                } else if (!strcmp(lex[0], "9")) {
                    puts("HI");
                    alert printf("L'automate %s%s%s%s a été rendu deterministe.", KBLDON, KGRN, a->nom, KNRM);                    
                    Automate *a2 = rendez_deterministe(a);
                    ajouter_automate_au_base(a2);
                } else if (!strcmp(lex[0], "10")) {
                    
                } else if (!strcmp(lex[0], "11")) {
                    
                } else if (!strcmp(lex[0], "12")) {
                    
                } else {
                    printf("%s : Command not found", lex[0]);
                }
                
                break;
            default:
                printf("%s : Command not found", lex[0]);
                break;
        }
        free(lex);puts("");
    }
}

void aff_menu_de_base__() {
    aff_msg_debut();
    puts("");aff_help(-222);puts("");puts("");
    while (1) {
        char commande_msg[MAX_INT];
        printf("%s%sset> %s", KBLDON, KRED, KNRM);
        char input[MAX_INT]; char **lex; int len;
        fgets(input, MAX_INT, stdin);
        lex = separer_chaine(input, " \n", &len);
        switch (len) {
            case 1:
                // exit
                if (!strcmp(lex[0], "exit")) {
                    exit(0);
                } else if (!strcmp(lex[0], "help")) {
                    aff_help(-222);
                } else if (!strcmp(lex[0], "show")) {
                    aff_base_automate();
                } else {
                    printf("%s : Command not found", lex[0]);
                }
                break;
            case 2:
                // operation unitaire
                if (!strcmp(lex[0], "add")) {
                    // ajouter automate
                    Automate *automate=nouvelle_automate(lex[1]);
                    ajouter_automate_au_base(automate);
                    add printf("L'automate %s%s%s%s à été ajoutée.", KBLDON, KGRN, automate->nom, KNRM);
                } else if(!strcmp(lex[0], "remove")) {
                    // supprimer automate
                    int sauv = nombre_automate;
                    for (int i=0; i<nombre_automate; i++) {
                        if (!strcmp(lex[1], base_automate[i]->nom)) {
                            minus printf("L'automate %s%s%s%s a été supprimée de la base.", KBLDON, KGRN, base_automate[i]->nom, KNRM);
                            for (int j=i; j<nombre_automate-1; j++) {
                                base_automate[j] = base_automate[j+1];
                            }
                            nombre_automate--;
                            break;
                        }
                    } 
                    if (sauv == nombre_automate) {
                        alert printf("L'automate %s%s%s%s n'existe pas dans la base.", KBLDON, KGRN, lex[1], KNRM);
                    }
                } else if (!strcmp(lex[0], "select")) {
                    // selectionner une automate
                    int sauv=0;
                    for (int i=0; i<nombre_automate; i++) {
                        if (!strcmp(lex[1], base_automate[i]->nom)) {
                            sauv = 1;
                            // HI
                            star printf("L'automate %s%s%s%s a été sélectionnée.\n", KBLDON, KGRN, lex[1], KNRM);
                            alert printf("Commande help pour afficher le menu.");
                            puts("");  
                            aff_menu_automate(base_automate[i]);
                            puts("");  
                        }
                    }
                    if (!sauv) {
                        alert printf("L'automate %s%s%s%s n'existe pas dans la base.", KBLDON, KGRN, lex[1], KNRM);
                    }
                } else {
                    printf("%s : Command not found", lex[0]);
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
                printf("%s : Command not found", lex[0]);
                break;
        }
        free(lex);puts("");
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