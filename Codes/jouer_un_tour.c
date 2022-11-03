#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "conio.h"

extern int tour(int nb_pion)
{
    // À QUI LE TOUR ?

    if (nb_pion % 2 == 1)       // On détermine quel joueur doit joué à partir du nombre de pion
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

extern int verif_pion(char p, int n, int **mat)
{
    // L'ACTION DU JOUEUR EST-ELLE POSSIBLE ?

    int j = p - 65;     // On convertie un char en integer à l'aide de la table ASCII

    for (int i = 0; i < n; i++)       // On vérifie que le caractère p est bien A, B, C, D, E, F ou G à l'aide de la table ASCII
    {
        if (j == i)
        {
            if (*(mat[0] + j) == 0)     // Si la case la plus haute de la colonne est libre, alors il reste au moins une place
            {
                gotoxy(6*n + 15, 18);
                printf("                                                                    ");     // Si l'action est possible, on va effacer le possible message d'erreur
                return 1;
            }
        }
    }
    gotoxy(6*n + 15, 18);
    printf("La colonne demand\x82\x65 est d\x82j\x85 compl\x8Ate ou indisponible.");        // On affiche un message d'erreur si la demande du joueur est impossible
    return 0;
}

extern int ajouter_pion(int **mat, int m, int p, int joueur)
{
    int i = m - 1;      // On commence par le bas d'une colonne pour pouvoir remonter petit à petit
    int libre = 0;
    while (libre == 0)      // Tant qu'on est pas tombé sur une case disponible, on va continuer à monter
    {
        if (*(mat[i] + p) == 0)     // Si la case est disponible, on va y ajouter la valeur correspondant au joueur
        {
            *(mat[i] + p) = joueur;
            libre = 1;
        }
        i--;
    }
    return (i+1);       // On retourne la ligne à laquelle le pion a été ajouté pour compléter les coordonnées
}
