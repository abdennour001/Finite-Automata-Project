
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


void aff_msg_debut() {

}

void aff_menu() {
    
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