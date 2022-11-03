#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conio.h"

extern void joueurs(int n, char noms_joueurs[2][10], int *c1, int *c2)
{
    // AFFICHAGE DU NOM DES JOUEURS ET DE LEUR COULEUR

    gotoxy(6*n + 15 , 4);
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-");

    gotoxy(6*n + 23 + strlen(noms_joueurs[0]), 6);
    textbackground(*c1);
    printf("     ");
    textbackground(0);

    gotoxy(6*n + 20, 7);
    printf("%s : ", noms_joueurs[0]);
    textbackground(*c1);
    printf("     ");
    textbackground(0);

    gotoxy(6*n + 23 + strlen(noms_joueurs[1]), 9);
    textbackground(*c2);
    printf("     ");
    textbackground(0);

    gotoxy(6*n + 20, 10);
    printf("%s : ", noms_joueurs[1]);
    textbackground(*c2);
    printf("     ");
    textbackground(0);

    gotoxy(6*n + 15, 12);
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-");
}

extern void grille(int **mat, int n, int m, int *c1, int *c2)
{
    // AFFICHAGE DE LA GRILLE DE JEU

    gotoxy(1, 3);
    for (int i = 0; i < m; i++)     // On a m lignes à afficher
    {
        textbackground(0);
        printf("    |");
        for (int i = 0; i < n; i++)     // Et n colonnes
        {
            printf("+     ");
        }
        printf("+| \n");
        for (int k = 0; k < 2; k++)     // Chaque case est haute de deux lignes
        {
            printf("    |");
            for (int j = 0; j < n; j++)
            {
                printf(" ");
                if (*(mat[i] + j) == 1)     // Si le pion d'un joueur est placé, on va remplir la case avec sa couleur
                {
                    textbackground(*c1);
                }
                else if (*(mat[i] + j) == 2)
                {
                    textbackground(*c2);
                }
                printf("     ");
                textbackground(0);
            }
            printf(" | \n");
        }
    }
    printf("    |");
    for (int i = 0; i < n; i++)
    {
        printf("+     ");
    }
    printf("+| \n    =");
    for (int i = 0; i < n; i++)
    {
        printf("======");
    }
    printf("= \n        ");
    for (int i = 65; i < n+65; i++)     // On affiche le nom des colonnes pour le joueur
    {
        printf("%c     ", i);
    }
}

extern void affich_tour(int n, int joueur, char noms_joueurs[2][10])
{
   // AFFICHAGE DU NOM DU JOUEUR QUI DOIT JOUER

    gotoxy(6*n + 15, 15);
    printf("                                               ");
    gotoxy(6*n + 15, 15);
    printf("Au tour de %s :", noms_joueurs[joueur-1]);
}

extern int pion(int n, char p, int mat)
{
    // QUE JOUE LE JOUEUR ?

    int verif_pion();

    gotoxy(6*n + 15, 17);
    printf("Colonne [A-%c] ? : ", 64+n);       // On demande une valeur à l'utilisateur
    do
    {
        gotoxy(6*n + 33, 17);
        printf("            ");
        gotoxy(6*n + 33, 17);
        scanf("%s", &p);
        p = toupper(p);
    } while (verif_pion(p, n, mat) == 0);       // Tant que la valeur ne correspond pas un coup possible, on va redemander une valeur au joueur
    return p;
}

extern void verdict(int n, int m, int joueur, char noms_joueurs[2][10], int nb_pion)
{
    // AFFICHAGE DU RÉSULTAT FINAL

    gotoxy(6*n + 15, 15);
    if (nb_pion == n*m)     // Si le nombre de pion joués est égal au nombre de pion maximal, la grille a été remplit sans victoire
    {
        printf("\x90GALIT\x90");
        gotoxy(6*n + 15, 16);
        printf("Le nombre maximal de pions plac\x82s a été atteint.");
    }
    else        // Sinon, l'un des joueurs a gagné
    {
        printf("VICTOIRE");
        gotoxy(6*n + 15, 16);
        printf("%s a gagn\x82 la partie.", noms_joueurs[joueur-1]);
    }
}

extern int rejouer(int n)
{
    // REFAIRE UNE PARTIE ?

    char rejouer;

    gotoxy(6*n + 15, 18);
    printf("Voulez-vous refaire une partie ? (O/N) : ");
    while (1)       // Quand l'une des deux possibilités de réponse sera rentré, return permettra de directement sortir de la fonction
    {
        gotoxy(6*n + 56, 18);
        printf("      ");
        gotoxy(6*n + 56, 18);
        scanf("%s", &rejouer);
        if (toupper(rejouer) == 'O')
        {
            return 1;
        }
        else if (toupper(rejouer) == 'N')
        {
            return 0;
        }
    }
}
