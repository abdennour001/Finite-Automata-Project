#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structure.h"
#include "structure.h"


/**
 * @author AMOKRANE Abdennour
 * 
 * "externe/structure.h"
 * 
 * Contient les  structures et les prototypes des fonctions qui manipule les structure 
 * 
 * externe dans le programme comme Les piles, les files, ...
 * 
 * **/

Pile *allouer()/** UNE FONCTION QUI ALLOUER UNE ADRESSE OU UNE PLACE DANS LA MEMOIRE POUR UNE MAILLON DANS LA LISTE **/
{
	return ((Pile *)malloc(sizeof(Pile)));
}

void aff_val(Pile *p,Etat* etat)/** UNE FONCTION QUI METTRE UNE VALEUR 'V' DANS LE CHAMPS VALEUR DE LA MAILLON POINTEE PAR P DANS LA MEMOIRE **/
{
	p->etat=etat;//e.i *p.val=v;
}

void aff_adr(Pile *p,Pile *q)/** UNE FONCTION QUI METTRE UNE ADRESSE 'PIONTEE PAR Q ' DANS LE CHAMPS VALEUR DE LA MAILLON POINTEE PAR P DANS LA MEMOIRE **/
{
	p->suiv=q;
}

Pile *suivant(Pile *p)/** AFFICHER LE CONTENUE DU CHAMPS ADRESSE DANS LA MAILLON POINTEE PAR P  **/
{
	return (p->suiv);
}

Etat* valeur(Pile *p)/** AFFICHER LE CONTENUE DU CHAMPS VALEUR DANS LA MAILLON POINTEE PAR P **/
{
	return (p->etat);
}

void empiler(Pile **p, Etat* etat)
{
    Pile *q ;
    //-----------------------
    q = allouer();
    aff_adr(q,*p);
    aff_val(q,etat);
    *p = q;
    return 0;
}

Etat *depiler(Pile **p)
{
    Pile *sauv; Etat *return_val;

    if(!pilevide(*p))
    {
        sauv = *p ;
        return_val = sauv->etat;
        *p = suivant(*p);
        sauv = NULL;
    }
    else
    {
        return NULL;
    }
    return return_val;
}

int pilevide(Pile *p)
{
    if(p == NULL) return(1);
        else return(0);
}

void afficher_pile(Pile *p) //Afficher une LLc, si la liste est vide donc rien va afficher a l'ecran ...
{
	Pile  *q;

	q = p;
	while(q != NULL )
	{
		afficher_etat(valeur(q));
        printf("\n");
		q=suivant(q);
	}
}