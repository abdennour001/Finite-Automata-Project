# Finite-Automata-Project

## By AMOKRANE Abdennour (abdennour001)

A finite automaton (FA) is a simple idealized machine used to recognize patterns within input taken from some character set (or alphabet) C. The job of an FA is to accept or reject an input depending on whether the pattern defined by the FA occurs in the input.

# General form of .init file to create an Automata

***!!!*** *@X@* == X est sans espaces ***!!!*** <br/>
***!!!*** *@X@* *@Y@* ... @Z@ == X, Y et Z sont séparés par un espace ***!!!** <br/>
***!!!*** *@status@* == status dans {INIT, FINAL, INIT&FINAL} ***!!!*** <br/>
***!!!*** *@mot_lu@* == vide si est une transition stantané EPSILON ***!!!*** <br/>
***!!!*** *@mot_lu@* == *@lettre_1@* *@lettre_2@* ... *@lettre_3@* == des lettres séparés par espaces ***!!!*** <br/>
```
**DEBUT;** <br/>
*@nom_automate@* **< X, S0, F, S, II >** <br/>
*@nom_alphabet@* *@nombre_des_lettres_dans_l'alphabet@* <br/>
*@nombre_d'états@* <br/>
*@nombre_instructions@* <br/>
*@lettre_1@* *@lettre_2@* ... *@lettre_n@* <br/>
*@etat_1@* *@status_1@* <br/>
*@etat_2@* *@sataus_2@* <br/>
.<br/>
.<br/>
.<br/>
*@etat_m@* *@sataus_m@*<br/>
*@etat_src_1@***,** *@mot_lu_1@***,** *@etat_dest_1@*<br/>
*@etat_src_2@***,** *@mot_lu_2@***,** *@etat_dest_2@*<br/>
*@etat_src_3@***,** *@mot_lu_3@***,** *@etat_dest_3@*<br/>
.
.
.
@etat_src_k@, @mot_lu_k@, @etat_dest_k@  
FIN;
```