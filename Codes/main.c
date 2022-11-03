#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // INFORMATIONS DES JOUEURS

    char noms_joueurs[2][10];       // Tableau de chaine de caractère contenant les noms des joueurs

    int couleur_j1;     // Ces variables corresponderont au nombre qu'il faut mettre dans la fonction textBackground(n) pour afficher la couleur souhaiter
    int couleur_j2;
    int *c1 = &couleur_j1;      // On utilise des pointeurs, car la fonction menu() ne peut pas renvoyer plusieurs variables
    int *c2 = &couleur_j2;

    char menu();
    menu(noms_joueurs, c1, c2);        // On va afficher l'écran de début et récupérer les infos des joueurs
    system("cls");       // On nettoie l'écran pour afficher la nouvelle page


    // INITIALISATION DE LA MATRICE

    int n = 7;      // Nombre de colonnes
    int m = 6;      // Nombre de lignes
    int **mat;
    mat = (int**)malloc(sizeof(int*)*m);        // Création de la matrice dans l'espace de stockage mémoire
    for (int i = 0; i < m; i++)
    {
        mat[i] = (int*)malloc(sizeof(int)*n);
    }


    // INITIALISATION DES VARIABLES

    int fin;        // Variable déterminant la fin de la boucle et donc la fin du jeu
    int nb_pion;      // Variable servant à compter le nombre de pions qui ont été joués au total
    int pl;     // Variables contenant la ligne et la colonne du dernier pion joué
    int pc;
    int joueur;     // Variable permettant de savoir quel joueur est en train de jouer
    char p;         // Variable permettant de stocker la colonne où le joueur veut ajouter un pion
    int jouer;        // Variable servant à relancer une partie si demandé


    // INITIALISATION DES FONCTIONS

    void joueurs();
    void grille();
    void affich_tour();
    int pion();
    void verdict();
    int rejouer();
    int tour();
    int ajouter_pion();
    int victoire();
    void historique();


    // DÉBUT DU JEU

    joueurs(n, noms_joueurs, c1, c2);       // Cette partie de l'affichage sera toujours présente et identique, inutile de la re-afficher à chaque fois

    do
    {
        for (int i = 0; i < m; i++)     // Initialisation de toutes les valeurs de la matrice à 0, correspondant à une grille vide
        {
            for (int j = 0; j < n; j++)
            {
                *(mat[i] + j) = 0;
            }
        }

        fin = 0;
        nb_pion = 0;

        while (fin == 0)
        {

            // À QUI LE TOUR ?

            joueur = tour(nb_pion);
            affich_tour(n, joueur, noms_joueurs);


            // ON JOUE UN TOUR

            grille(mat, n, m, c1, c2);      // À chaque fois qu'un pion va être jouer, on va actualiser cette grille de jeu

            p = pion(n, p, mat);

            pl = ajouter_pion(mat, m, p-65, joueur);     // On ajoute un pion et on stocke ces coordonnées
            pc = p-65;

            nb_pion++;      // On incrémente le nombre de pion placé


            // FIN DU JEU

            if (nb_pion >= 7)       // Le jeu ne peut se terminer que si au moins 7 pions ont été placés
            {
                nb_pion = victoire(mat, joueur, pl, pc, n, m, nb_pion);     // Si l'un des joueurs a gagné, on affectera nb_pion la valeur nb_pion+n*m pour pouvoir sortir de la boucle
                if (nb_pion >= n*m)     // On regarde si le nombre de pion joués est supérieur ou égale à la limite
                {
                    fin = 1;
                }
            }
        }

        // APRÉS LE JEU

        system("cls");       // On nettoie l'écran pour afficher la page de fin

        grille(mat, n, m, c1, c2);      // Même si la partie est terminé, on affichage la grille de jeu
        joueurs(n, noms_joueurs, c1, c2);       // On affiche également les informations des joueurs
        verdict(n, m, joueur, noms_joueurs, nb_pion);      // On affichage le résultat final
        jouer = rejouer(n);        // On demande aux joueurs s'ils veulent rejouer

        system("cls");       // On nettoie l'écran pour éventuellement recommencer une partie

        historique(noms_joueurs, joueur, nb_pion, n, m);      // Création ou mise à jour du fichier txt contenant l'historique des parties joués
    } while (jouer == 1);
    return 0;
}
