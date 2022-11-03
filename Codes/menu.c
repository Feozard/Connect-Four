#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conio.h"

void maj(char *str)
{
    int j;
    for (int i = 0; i < strlen(str); i++)
    {
        j = str[i];
        str[i] = toupper(j);
    }
}

extern char menu(char noms_joueurs[2][10], int *c1, int *c2)
{
    // INITIALISATION DES VARIABLES

    char couleur_joueur1[4];
    char couleur_joueur2[4];
    int couleur_j1;
    int couleur_j2;

    char couleurs[16][7] = {"BLE", "V", "C", "R", "MAG", "MAR", "GC", "GF", "BLEC", "VC", "CC", "RC", "MAGC", "J", "BLA"};  // L'indice de chaque couleur correspond à n-1 dans textBackground(n) pour afficher sa couleur

    int couleur_ok = 0;
    int nom_ok = 0;


    // AFFICHAGE DU TITRE

    printf("\n     /#######            /##                                                                  /##   /## \n");
    printf("    | ##__  ##          |__/                                                                 | ##  | ## \n");
    printf("    | ##  \\ ## /##   /## /##  /####### /#######  /######  /#######   /#######  /######       | ##  | ## \n");
    printf("    | #######/| ##  | ##| ## /##_____//##_____/ |____  ##| ##__  ## /##_____/ /##__  ##      | ######## \n");
    printf("    | ##____/ | ##  | ##| ##|  ######|  ######   /#######| ##  \\ ##| ##      | ########      |_____  ## \n");
    printf("    | ##      | ##  | ##| ## \\____  ##\\____  ## /##__  ##| ##  | ##| ##      | ##_____/            | ## \n");
    printf("    | ##      |  ######/| ## /#######//#######/|  #######| ##  | ##|  #######|  #######            | ## \n");
    printf("    |__/       \\______/ |__/|_______/|_______/  \\_______/|__/  |__/ \\_______/ \\_______/            |__/");


    // AFFICHAGE DES INFORMATIONS QU'ON VA DEMANDER AUX JOUEURS

    gotoxy(15, 13);
    printf("-> NOM DU JOUEUR 1 : ");

    gotoxy(50, 13);
    printf("-> COULEUR DU JOUEUR 1 : ");

    gotoxy(12, 16);
    printf("-_-_-_-_-_-_-_-_-_-_-");

    gotoxy(15, 19);
    printf("-> NOM DU JOUEUR 2 : ");

    gotoxy(50, 19);
    printf("-> COULEUR DU JOUEUR 2 : ");


    // AFFICHAGE DES COULEURS DISPONIBLES EN BAS DE L'ÉCRAN

    gotoxy(12, 24);
    printf("Couleurs disponibles : ");
    textcolor(0);
    for (int i = 0; i < 15; i++)
    {
        gotoxy(12 + i*7, 26);
        textbackground(i+1);
        switch (strlen(couleurs[i]))        // Suivant la longueur de la chaine de caractère contenant le nom de la couleur, on affichera différemment pour centrer
        {
            case 4 : printf(" %s ", couleurs[i]); break;
            case 3 : printf(" %s  ", couleurs[i]); break;
            case 2 : printf("  %s  ", couleurs[i]); break;
            case 1 : printf("  %s   ", couleurs[i]); break;
        }
    }
    textbackground(0);
    printf(".");
    textcolor(7);


    // ON VA DEMANDER LES INFORMATIONS AUX JOUEURS

    gotoxy(36, 13);     // On demande le nom du joueur 1
    scanf("%s", noms_joueurs[0]);

    gotoxy(75, 13);     // On demande la couleur du joueur 1
    scanf("%s", couleur_joueur1);

    do
    {
        maj(couleur_joueur1);
        for (int i = 0; i < 16; i++)        // On va regarder si la couleur demandé par l'utilisateur correspond à une des couleurs disponible
        {
            if (strcmp(couleur_joueur1, couleurs[i]) == 0)
            {
                couleur_ok = 1;
                *c1 = i + 1;
                gotoxy(50, 14);
                printf("                       ");      // On efface un possible message d'erreur si l'entrée est correct
            }
        }
        if (couleur_ok == 0)        // Si la couleur n'existe pas dans notre tableau, on va afficher un message d'erreur et demander une nouvelle couleur
        {
            gotoxy(50, 14);
            printf("Entr\x82\x65 non valide.");
            gotoxy(75, 13);
            printf("                       ");
            gotoxy(75, 13);
            scanf("%s", couleur_joueur1);
        }
    } while (couleur_ok == 0);      // Tant que la couleur ne sera pas correct, on tournera en boucle

    couleur_ok = 0;     // On remet l'indicateur à faux (0) pour a couleur du joueur 2

    gotoxy(36, 19);     // On demande le nom du joueur 2
    scanf("%s", noms_joueurs[1]);

    do      // Les noms des deux joueurs doivent être différents
    {
        if (strcmp(noms_joueurs[0], noms_joueurs[1]) != 0)
        {
            nom_ok = 1;
            gotoxy(15, 20);
            printf("                                                      ");
        }
        else
        {
            gotoxy(36, 19);
            printf("              ");
            gotoxy(15, 20);
            printf("Les noms des deux joueurs doivent \x88tre diff\x82rents.");
            gotoxy(36, 19);
            scanf("%s", noms_joueurs[1]);
        }
    } while (nom_ok == 0);

    gotoxy(75, 19);     // On demande la couleur du joueur 2
    scanf("%s", couleur_joueur2);

    do
    {
        maj(couleur_joueur2);
        for (int i = 0; i < 16; i++)
        {
            if ((strcmp(couleur_joueur2, couleurs[i]) == 0) && (strcmp(couleur_joueur2, couleur_joueur1) != 0))      // La couleur doit être présente dans le tableau mais aussi être différente de la couleur du joueur 1
            {
                couleur_ok = 1;
                *c2 = i + 1;
            }
        }
        if (couleur_ok == 0)
        {
            gotoxy(50, 20);
            printf("Entr\x82\x65 non valide. Les deux couleurs doivent \x88tre diff\x82rentes.");
            gotoxy(75, 19);
            printf("                                ");
            gotoxy(75, 19);
            scanf("%s", couleur_joueur2);
        }
    } while (couleur_ok == 0);

    return noms_joueurs;
}
