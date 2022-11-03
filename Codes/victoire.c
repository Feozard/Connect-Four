extern int victoire(int **mat, int joueur, int pl, int pc, int n, int m, int nb_pion)
{
    // LE JOUEUT A-T-IL GAGNÉ ?

    int count;

    int vl;     // Variables contenant les coordonnées d'un possible pion voisin et du même joueur à celui qui a été mit en dernier
    int vc;

    int a;      // Indices permettant d'explorer les pions en ligne, colonne ou diagonales
    int b;
    int signe_a;        // Variables qui détermine dans quel sens on va explorer la matrice
    int signe_b;

    int count_inverse;      // On compte le nombre de fois où l'on va faire demi-tour dans la recherche de 4 pions voisins pour ne pas tourner en rond

    int mat_analyse[m][n];      // On initialise une matrice permettant de savoir ce qu'on a déjà testé
    for (int i = 0; i < m; i++)     // Initialisation de toutes ses valeurs à 0, signifiant qu'on ne connait pas l'état des pions à ces endroits
    {
        for (int j = 0; j < n; j++)
        {
            mat_analyse[i][j] = 0;
        }
    }

    mat_analyse[pl][pc] = 1;        // Aux coordonnées du dernier pion joué, on indique 1, voulant dire que cette case contient un pion du joueur

    for (int i = -1; i <= 1; i++)       // On va analyser chaque pion autour du dernier pion joué en formant un U
    {
        for (int j = -1; j <= 1; j++)
        {
            if ((pl + j >= 0) && (pl + j < m) && (pc + i >= 0) && (pc + i < n))        // On vérifie que la case à tester est dans la matrice
            {
                if (i != 0 || j != 0)       // On vérifie que la case à tester n'est pas la case de départ
                {
                    if (*(mat[pl + j] + (pc + i)) == joueur)        // On regarde si la case a tester contient un pion du joueur
                    {
                        mat_analyse[pl + j][pc + i] = 1;        // Si oui, cette case va avoir la valeur 1
                        count = 2;        // Il y a donc deux pions alignés dans la grille
                        vl = pl + j;        // On récupère les coordonnées de ce pion voisin
                        vc = pc + i;

                        count_inverse = 0;

                        if (pl == vl)       // Si les deux pions voisins sont situés sur la même ligne, on va se décaler en colonne
                        {
                            a = i;
                            signe_a = i;
                            b = 0;
                            signe_b = 0;
                        }
                        else if (pc == vc)       // Si les deux pions voisins sont situés sur la même colonne, on va se décaler en ligne
                        {
                            a = 0;
                            signe_a = 0;
                            b = j;
                            signe_b = j;
                        }
                        else        // Si les deux voisins ne sont ni sur la même ligne, ni sur la même colonne, ils sont en diagonales et on va jouer avec deux indices pour voyager dans la matrice
                        {
                            a = i;
                            signe_a = i;
                            b = j;
                            signe_b = j;
                        }
                        while ((count < 4) && (count_inverse < 2))      // Tant qu'on a pas trouvé 4 pions alignés ou qu'on a pas atteint deux demis-tour, on va continuer à chercher
                        {
                            if ((vl + b >= 0) && (vl + b < m) && (vc + a >= 0) && (vc + a < n) && (mat_analyse[vl + b][vc + a] != 2))       // On regarde si la case à testé est dans la matrice et si elle n'a pas déjà été testé négativement
                            {
                                if (*(mat[vl + b] + (vc + a)) == joueur)        // On regarde si la case contient un pion du joueur
                                {
                                    mat_analyse[vl + b][vc + a] = 1;
                                    count++;
                                    b += signe_b;
                                    a += signe_a;
                                }
                                else
                                {
                                    mat_analyse[vl + b][vc + a] = 2;
                                }
                            }
                            else        // Si on tombe en dehors de la grille où sur une case ne contenant pas un pion du joueur, on va chercher dans l'autre sens
                            {
                                count_inverse++;
                                b = -signe_b;
                                signe_b = -signe_b;
                                b += signe_b;
                                a = -signe_a;
                                signe_a = -signe_a;
                                a += signe_a;
                            }
                        }
                        if (count == 4)
                        {
                            return (nb_pion+n*m);     // Si le joueur a aligné 4 pions, on sort de la fonction
                        }
                    }
                    else
                    {
                        mat_analyse[pl+j][pc+i] = 2;        // Si la case testé ne contient pas un pion du joueur, on lui donne la valeur de 2
                    }
                }
            }
        }
    }
    return (nb_pion);
}
