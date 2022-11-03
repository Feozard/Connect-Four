#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void historique(char noms_joueurs[2][10], int joueur, int nb_pion, int n, int m)
{
    // HISTORIQUE DES PARTIES

    FILE *historique;
    int nb_partie;

    int c;
    int nb_lignes = 0;

    historique = fopen("Historique.txt", "a+");      // On ouvre où on crée le document

    if (fgetc(historique) == EOF)       // Si le document est vide, on inscrit le titre, sinon il a déjà été inscrit
    {
        fputs("-> HISTORIQUE DES PARTIES\n", historique);
        fputs("--------------------------\n\n", historique);

        nb_partie = 1;
    }
    else        // Si le document n'est pas vide, au moins une partie a déjà été recensée
    {
        while((c = fgetc(historique)) != EOF)       // Pour savoir à la combientième partie on est, on va compter le nombre de ligne
        {
            if(c == '\n')
            {
                nb_lignes++;
            }
        }
        nb_partie = nb_lignes/8 + 1;        // Sachant que l'historique d'une partie se fait sur 8 lignes
    }

    fprintf(historique, "#PARTIE N\xB0%d \n\n", nb_partie);
    fprintf(historique, "Joueur 1 : %s       Joueur 2 : %s\n", noms_joueurs[0], noms_joueurs[1]);
    if (nb_pion == n*m)
    {
        fprintf(historique, "\x90galité");
    }
    else
    {
        fprintf(historique, "Vainqueur : %s", noms_joueurs[joueur-1]);
        fprintf(historique, "        Nombre de coups : %d \n\n", (nb_pion-n*m)/2 + (nb_pion-n*m)%2);
    }
    fprintf(historique, "    ~~~~~~~~~~~~~~~~~~~~~~ \n\n\n");
    fclose(historique);
}
