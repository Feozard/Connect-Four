extern int victoire(int **mat, int joueur, int pl, int pc, int n, int m, int nb_pion)
{
    // LE JOUEUT A-T-IL GAGN� ?

    int count;

    int vl;     // Variables contenant les coordonn�es d'un possible pion voisin et du m�me joueur � celui qui a �t� mit en dernier
    int vc;

    int a;      // Indices permettant d'explorer les pions en ligne, colonne ou diagonales
    int b;
    int signe_a;        // Variables qui d�termine dans quel sens on va explorer la matrice
    int signe_b;

    int count_inverse;      // On compte le nombre de fois o� l'on va faire demi-tour dans la recherche de 4 pions voisins pour ne pas tourner en rond

    int mat_analyse[m][n];      // On initialise une matrice permettant de savoir ce qu'on a d�j� test�
    for (int i = 0; i < m; i++)     // Initialisation de toutes ses valeurs � 0, signifiant qu'on ne connait pas l'�tat des pions � ces endroits
    {
        for (int j = 0; j < n; j++)
        {
            mat_analyse[i][j] = 0;
        }
    }

    mat_analyse[pl][pc] = 1;        // Aux coordonn�es du dernier pion jou�, on indique 1, voulant dire que cette case contient un pion du joueur

    for (int i = -1; i <= 1; i++)       // On va analyser chaque pion autour du dernier pion jou� en formant un U
    {
        for (int j = -1; j <= 1; j++)
        {
            if ((pl + j >= 0) && (pl + j < m) && (pc + i >= 0) && (pc + i < n))        // On v�rifie que la case � tester est dans la matrice
            {
                if (i != 0 || j != 0)       // On v�rifie que la case � tester n'est pas la case de d�part
                {
                    if (*(mat[pl + j] + (pc + i)) == joueur)        // On regarde si la case a tester contient un pion du joueur
                    {
                        mat_analyse[pl + j][pc + i] = 1;        // Si oui, cette case va avoir la valeur 1
                        count = 2;        // Il y a donc deux pions align�s dans la grille
                        vl = pl + j;        // On r�cup�re les coordonn�es de ce pion voisin
                        vc = pc + i;

                        count_inverse = 0;

                        if (pl == vl)       // Si les deux pions voisins sont situ�s sur la m�me ligne, on va se d�caler en colonne
                        {
                            a = i;
                            signe_a = i;
                            b = 0;
                            signe_b = 0;
                        }
                        else if (pc == vc)       // Si les deux pions voisins sont situ�s sur la m�me colonne, on va se d�caler en ligne
                        {
                            a = 0;
                            signe_a = 0;
                            b = j;
                            signe_b = j;
                        }
                        else        // Si les deux voisins ne sont ni sur la m�me ligne, ni sur la m�me colonne, ils sont en diagonales et on va jouer avec deux indices pour voyager dans la matrice
                        {
                            a = i;
                            signe_a = i;
                            b = j;
                            signe_b = j;
                        }
                        while ((count < 4) && (count_inverse < 2))      // Tant qu'on a pas trouv� 4 pions align�s ou qu'on a pas atteint deux demis-tour, on va continuer � chercher
                        {
                            if ((vl + b >= 0) && (vl + b < m) && (vc + a >= 0) && (vc + a < n) && (mat_analyse[vl + b][vc + a] != 2))       // On regarde si la case � test� est dans la matrice et si elle n'a pas d�j� �t� test� n�gativement
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
                            else        // Si on tombe en dehors de la grille o� sur une case ne contenant pas un pion du joueur, on va chercher dans l'autre sens
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
                            return (nb_pion+n*m);     // Si le joueur a align� 4 pions, on sort de la fonction
                        }
                    }
                    else
                    {
                        mat_analyse[pl+j][pc+i] = 2;        // Si la case test� ne contient pas un pion du joueur, on lui donne la valeur de 2
                    }
                }
            }
        }
    }
    return (nb_pion);
}
