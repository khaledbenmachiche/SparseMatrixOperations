/*-------------------------------------------------BIBLIOTHEQUE TP C LES MATRICES CREUSES---------------------------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------------LE FICHIER .C-------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "BIBLIO.h"
#include <string.h>
typedef int Typeelem_Li;
/*------------------------------------------------------LA 1ERE REPRESENTATION-----------------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------LA MACHINE ABSTRAITE------------------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Allouer_Li(Pointeur_Li *P) // allouer un espace et retourner son adresse
{
    *P = (struct Maillon_Li *)malloc(sizeof(struct Maillon_Li));
    (*P)->Suiv = NULL;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Liberer_Li(Pointeur_Li P) // libérer l'espace déja allouer
{
    free(P);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
Pointeur_Li Suivant_Li(Pointeur_Li P) // retourner l'adresse du prochain élément contenu dans le maillon P
{
    return (P->Suiv);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
Typeelem_Li Valeur_ligne(Pointeur_Li P) // retourner l'information contenue dans le maillon P
{
    return (P->ligne);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
Typeelem_Li Valeur_colonne(Pointeur_Li P) // retourner l'information contenue dans le maillon P
{
    return (P->colonne);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//
Typeelem_Li Valeur_val(Pointeur_Li P) // retourner l'information contenue dans le maillon P
{
    return (P->val_nonul);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_val_ligne(Pointeur_Li P, Typeelem_Li i) // affecter l'information au champ vam du maillon P
{
    P->ligne = i;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_val_colonne(Pointeur_Li P, Typeelem_Li j) // affecter l'information au champ vam du maillon P
{
    P->colonne = j;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_val(Pointeur_Li P, Typeelem_Li Val) // affecter l'information au champ vam du maillon P
{
    P->val_nonul = Val;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_adr_Li(Pointeur_Li P, Pointeur_Li Q) // lier P à une autre adresse
{
    P->Suiv = Q;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------FIN DE LA MACHINE ABSTRAITE--------------------------------------------------------------------------------*/

void creation_liste_rep1(Pointeur_Li *tete, int lig, int col)
{
    Pointeur_Li p, q;
    int i, j, cpti, cptj, val;
    i = 0;
    j = 0;
    val = 0;
    *tete = NULL;
    p = NULL;
    //-----------------------la creation de la tete------------------------//
    while (val == 0 && i <= lig - 1)
    {
        while (val == 0 && j <= col - 1)
        {
            printf("Entrer la valeur de :  Matrix[%d,%d]--> ", i, j);
            scanf("%d", &val);
            if (val != 0)
            {
                Allouer_Li(&p);
                *tete = p;
                Aff_val_ligne(p, i);
                Aff_val_colonne(p, j);
                Aff_val(p, val);
                cpti = i;
                cptj = j;
            }
            j++;
        }
        j = 0;
        i++;
    }
    /*-----------------------------l'incrémentation des indices---------------------------------*/
    if (*tete != NULL)
    {
        if (cpti != lig && cptj == col - 1)
        {
            cptj = 0;
            cpti++;
        }
        else
        {
            cptj++;
        }
        /*--------------------------------la creation des maillons--------------------------------------*/
        for (i = cpti; i <= lig - 1; i++)
        {
            for (j = cptj; j <= col - 1; j++)
            {
                printf("Entrer la valeur de :  Matrix[%d,%d]--> ", i, j);
                scanf("%d", &val);
                if (val != 0)
                {
                    Allouer_Li(&q);
                    Aff_val_ligne(q, i);
                    Aff_val_colonne(q, j);
                    Aff_val(q, val);
                    Aff_adr_Li(p, q);
                    p = Suivant_Li(p);
                }
            }
            cptj = 0;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Affichage_LLC_rep1(Pointeur_Li tete)
{
    Pointeur_Li p;
    p = tete;
    while (p != NULL)
    {
        printf("| [l:%d]-[c:%d]-[v:%d] |--", Valeur_ligne(p), Valeur_colonne(p), Valeur_val(p));
        p = Suivant_Li(p);
    }
    printf("[-\n");
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Affichage_matrice_rep1(Pointeur_Li tete, int nbr_l, int nbr_c)
{
    Pointeur_Li p = tete;
    int cpt = 0, i = 0, j = 0;
    for (i = 0; i < nbr_l; i++)
    {
        for (j = 0; j < nbr_c; j++)
        {
            if (p != NULL)
            {
                if (Valeur_ligne(p) == i && Valeur_colonne(p) == j) // On affiche La valeur si la case tab[i , j] existe dans la liste
                {
                    printf("  %3d  ", Valeur_val(p));
                    p = Suivant_Li(p);
                }
                else
                {
                    printf("  %3d  ", 0); // Si la case n'existe pas dans la liste alors on affiche un 0(dans la liste creer il n'ya pas de 0)
                }
            }
            else // Si p est a NULL
            {
                printf("  %3d  ", 0);
            }
        }
        printf("\n");
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------LES DIVISIONS(EXTRACTION,DIVISION SOUS MATRICE)--------------------------------------------------------------------------------------*/
void extraction_rep1(Pointeur_Li tete, int dep_l, int dep_c, int fin_l, int fin_c, Pointeur_Li *teterect)
{
    Pointeur_Li p = tete, sauv, tmp;
    int nbr_lsous = fin_l - dep_l, nbr_csous = fin_c - dep_c;
    *teterect = NULL;
    while (p != NULL)
    {
        if ((Valeur_ligne(p)) >= dep_l && (Valeur_colonne(p)) >= dep_c) // les indices de collone de la sous matrice sont entre dep_c et fin_c (dep_c <= i <= fin_c)
        {
            if ((Valeur_ligne(p)) <= fin_l && (Valeur_colonne(p)) <= fin_c) // les indices de ligne de la sous matrice sont entre dep_l et fin_l (dep_l <= j <= fin_l)
            {
                if (*teterect == NULL) // creation de la tete de la liste sous matrice
                {
                    Allouer_Li(&*teterect);
                    Aff_val(*teterect, Valeur_val(p));
                    Aff_val_colonne(*teterect, Valeur_colonne(p) - dep_c);
                    Aff_val_ligne(*teterect, Valeur_ligne(p) - dep_l);
                    sauv = *teterect;
                }
                else // creation des maillons de la liste sous matrice
                {
                    Allouer_Li(&tmp);
                    Aff_val(tmp, Valeur_val(p));
                    Aff_val_colonne(tmp, Valeur_colonne(p) - dep_c);
                    Aff_val_ligne(tmp, Valeur_ligne(p) - dep_l);
                    Aff_adr_Li(sauv, tmp);
                    sauv = Suivant_Li(sauv);
                }
            }
        }
        p = Suivant_Li(p);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void divsousmatrice_rep1(Pointeur_Li tete, int nbr_l, int nbr_c, int divrow, int divcol)
{

    Pointeur_Li tetediv;
    int lig, col, tmpi, tmpj, cpt = 1, error = 0;
    do
    {
        if (divrow != 0 && divcol != 0)
        {
            col = (nbr_c / divcol);                         // nombre de collonne des sous matrice
            lig = (nbr_l / divrow);                         // nombre de ligne des sous matrices
            if (nbr_l % divrow == 0 && nbr_c % divcol == 0) // on doit d'abord verifier si cet matrice est devisable par le nombre enter par l'utilisateur
            {
                printf("\n \n LE RESULTAT DE LA DIVISION : \n");
                for (int i = 0; i < nbr_l; i = i + lig)
                {
                    for (int j = 0; j < nbr_c; j = j + col)
                    {
                        tmpi = i + lig;
                        tmpj = j + col;
                        extraction_rep1(tete, i, j, tmpi - 1, tmpj - 1, &tetediv);
                        printf("\n\n");
                        printf("LA SOUS MATRICE %d : \n", cpt);
                        Affichage_matrice_rep1(tetediv, lig, col);
                        cpt++;
                    }
                }
            }
            else
            {
                error = 1;
            }
        }
        else
        {
            error = 1;
        }
        if (error == 1)
        {
            printf("Il faut que la matrice soit divisible , entrer autres valeurs SVP ");
        }
    } while (error == 1);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*---------------------------------------------------------FIN DES MODULES DIVISION---------------------------------------------------------------------------------------*/
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/* --------------------------------------------------------------L'ADDITION------------------------------------------------------------------------------------------------*/
void addition_rep1(Pointeur_Li tete1, Pointeur_Li tete2, Pointeur_Li *teteop)
{
    int val;
    Pointeur_Li p = tete1, q = tete2, w, tmp;
    *teteop = NULL;
    if (tete1 != NULL && tete2 != NULL)
    {
        while ((p != NULL || q != NULL) && *teteop == NULL)
        {
            if (Valeur_ligne(p) == Valeur_ligne(q))
            {
                if (Valeur_colonne(p) == Valeur_colonne(q))
                {
                    val = Valeur_val(p) + Valeur_val(q);
                    if (val != 0)
                    {
                        Allouer_Li(&*teteop);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(p));
                        Aff_val_colonne(*teteop, Valeur_colonne(p));
                    }
                    p = Suivant_Li(p);
                    q = Suivant_Li(q);
                }
                else
                {
                    if (Valeur_colonne(p) > Valeur_colonne(q))
                    {
                        Allouer_Li(&*teteop);
                        val = Valeur_val(q);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(q));
                        Aff_val_colonne(*teteop, Valeur_colonne(q));
                        q = Suivant_Li(q);
                    }
                    else
                    {
                        if (Valeur_colonne(p) < Valeur_colonne(q))
                        {
                            Allouer_Li(&*teteop);
                            val = Valeur_val(p);
                            Aff_val(*teteop, val);
                            Aff_val_ligne(*teteop, Valeur_ligne(p));
                            Aff_val_colonne(*teteop, Valeur_colonne(p));
                            p = Suivant_Li(p);
                        }
                    }
                }
            }
            else
            {
                if (Valeur_ligne(p) > Valeur_ligne(q))
                {
                    Allouer_Li(&*teteop);
                    val = Valeur_val(q);
                    Aff_val(*teteop, val);
                    Aff_val_ligne(*teteop, Valeur_ligne(q));
                    Aff_val_colonne(*teteop, Valeur_colonne(q));
                    q = Suivant_Li(q);
                }
                else
                {
                    if (Valeur_ligne(p) < Valeur_ligne(q))
                    {
                        Allouer_Li(&*teteop);
                        val = Valeur_val(p);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(p));
                        Aff_val_colonne(*teteop, Valeur_colonne(p));
                        p = Suivant_Li(p);
                    }
                }
            }
            if (*teteop == NULL)
            {
                if (p == NULL && q != NULL)
                {
                    Allouer_Li(&*teteop);
                    val = Valeur_val(q);
                    Aff_val(*teteop, val);
                    Aff_val_ligne(*teteop, Valeur_ligne(q));
                    Aff_val_colonne(*teteop, Valeur_colonne(q));
                    q = Suivant_Li(q);
                }
                else
                {
                    if (q == NULL && p != NULL)
                    {
                        Allouer_Li(&*teteop);
                        val = Valeur_val(p);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(p));
                        Aff_val_colonne(*teteop, Valeur_colonne(p));
                        p = Suivant_Li(p);
                    }
                }
            }
        }
        w = *teteop;
        while (p != NULL && q != NULL)
        {
            if (Valeur_ligne(p) == Valeur_ligne(q))
            {
                if (Valeur_colonne(p) < Valeur_colonne(q))
                {
                    val = Valeur_val(p);
                    Allouer_Li(&tmp);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(p));
                    Aff_val_colonne(tmp, Valeur_colonne(p));
                    Aff_adr_Li(w, tmp);
                    p = Suivant_Li(p);
                    w = Suivant_Li(w);
                }
                else
                {
                    if (Valeur_colonne(p) > Valeur_colonne(q))
                    {
                        Allouer_Li(&tmp);
                        val = Valeur_val(q);
                        Aff_val(tmp, val);
                        Aff_val_ligne(tmp, Valeur_ligne(q));
                        Aff_val_colonne(tmp, Valeur_colonne(q));
                        Aff_adr_Li(w, tmp);
                        q = Suivant_Li(q);
                        w = Suivant_Li(w);
                    }
                    else
                    {
                        if (Valeur_colonne(p) == Valeur_colonne(q))
                        {
                            val = Valeur_val(p) + Valeur_val(q);
                            if (val != 0)
                            {
                                Allouer_Li(&tmp);
                                Aff_val(tmp, val);
                                Aff_val_ligne(tmp, Valeur_ligne(p));
                                Aff_val_colonne(tmp, Valeur_colonne(p));
                                Aff_adr_Li(w, tmp);
                                w = Suivant_Li(w);
                            }
                            p = Suivant_Li(p);
                            q = Suivant_Li(q);
                        }
                    }
                }
            }
            else
            {
                if (Valeur_ligne(p) > Valeur_ligne(q))
                {
                    Allouer_Li(&tmp);
                    val = Valeur_val(q);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(q));
                    Aff_val_colonne(tmp, Valeur_colonne(q));
                    Aff_adr_Li(w, tmp);
                    q = Suivant_Li(q);
                    w = Suivant_Li(w);
                }
                else
                {
                    if (Valeur_ligne(p) < Valeur_ligne(q))
                    {
                        Allouer_Li(&tmp);
                        val = Valeur_val(p);
                        Aff_val(tmp, val);
                        Aff_val_ligne(tmp, Valeur_ligne(p));
                        Aff_val_colonne(tmp, Valeur_colonne(p));
                        Aff_adr_Li(w, tmp);
                        p = Suivant_Li(p);
                        w = Suivant_Li(w);
                    }
                }
            }
        }
        while (p != NULL || q != NULL)
        {
            if (p == NULL)
            {
                Allouer_Li(&tmp);
                val = Valeur_val(q);
                Aff_val(tmp, val);
                Aff_val_ligne(tmp, Valeur_ligne(q));
                Aff_val_colonne(tmp, Valeur_colonne(q));
                Aff_adr_Li(w, tmp);
                w = Suivant_Li(w);
                q = Suivant_Li(q);
            }
            else
            {
                if (q == NULL)
                {
                    Allouer_Li(&tmp);
                    val = Valeur_val(p);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(p));
                    Aff_val_colonne(tmp, Valeur_colonne(p));
                    Aff_adr_Li(w, tmp);
                    w = Suivant_Li(w);
                    p = Suivant_Li(p);
                }
            }
        }
    }
    else
    {
        if (tete1 == NULL) // Si la matrice1 contient que des 0
        {
            *teteop = tete2;
        }
        else
        {
            if (tete2 == NULL) // Si la matrice2 contient que des 0
            {
                *teteop = tete1;
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void addition_multiple_rep1(Pointeur_Li tete1, Pointeur_Li tete2, Pointeur_Li *teteadd, int nbr_l, int nbr_c)
{
    int choix, cpt = 3;
    Pointeur_Li tete3, p = tete1, q = tete2;
    do
    {
        addition_rep1(p, q, &*teteadd);
        p = *teteadd;
        printf("ES QUE VOUS VOULEZ FAIRE UNE AUTRE ADDITION ? \n");
        printf("SI OUI ENTRER 1 \n");
        printf("SI NON ENTRER 2 \n");
        printf("TON CHOIX : ");
        scanf("%d", &choix);
        if (choix == 1)
        {
            printf("\n\nLE REMPLISSAGE DE LA MATRICE %d : \n\n", cpt);
            creation_liste_rep1(&tete3, nbr_l, nbr_c);
            Affichage_matrice_rep1(tete3, nbr_l, nbr_c);
            q = tete3;
            cpt++;
        }
    } while (choix == 1);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*---------------------------------------------------------FIN DES MODULES ADDITION-------------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void tri_bulle_lig_rep1(Pointeur_Li *tete)
{
    int sauv, sauvlig, sauvcol, tri;
    Pointeur_Li p, Prochain;
    if (*tete != NULL)
    {
        tri = 0;
        while (tri == 0)
        {
            p = *tete;
            tri = 1;
            while (Suivant_Li(p) != NULL)
            {
                Prochain = Suivant_Li(p);
                if (Valeur_ligne(p) > Valeur_ligne(Prochain))
                {
                    sauv = Valeur_val(p);
                    sauvlig = Valeur_ligne(p);
                    sauvcol = Valeur_colonne(p);
                    Aff_val(p, Valeur_val(Prochain));
                    Aff_val_ligne(p, Valeur_ligne(Prochain));
                    Aff_val_colonne(p, Valeur_colonne(Prochain));
                    Aff_val(Prochain, sauv);
                    Aff_val_ligne(Prochain, sauvlig);
                    Aff_val_colonne(Prochain, sauvcol);
                    tri = 0;
                }
                p = Suivant_Li(p);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------------LA MULTIPLICATION-------------------------------------------------------------------------------------------*/
void multiplication_vect_rep1(Pointeur_Li tete, Pointeur_Li tetevect, Pointeur_Li *teteop, int nbr_l, int nbr_c, int nbr_lvect)
{
    Pointeur_Li p = tete, q, tmp, sauv;
    *teteop = NULL;
    int l = 0, c = 0, val = 0;
    if (nbr_c == nbr_lvect) // faut que le nombre de colonne de la matrice est egal a le nombre de ligne de vecteur (les conditions de la multiplication)
    {
        if (tete != NULL && tetevect != NULL) /*on verifier si tete et tetevect ne sont pas a null
     (si tete == NULL --> toute les valeurs de la matrice sont egal a 0 , si tetevet == NULL --> toute les valeurs de vecteur sont a 0)*/
        {
            while (p != NULL && l != nbr_l) // l control et compte les nombres de lignes
            {
                c = 0;
                val = 0;
                q = tetevect; // a chaque iteration q prend l'adresse de tetevect car on vas parcourir le vecteur a nouveau
                while (q != NULL && c != nbr_c)
                {
                    if (p != NULL)
                    {
                        if (Valeur_ligne(p) == l && Valeur_colonne(p) == Valeur_ligne(q)) // on verifier si la collonne de la matrice est egal a la ligne du vecteur
                        {
                            val = val + Valeur_val(p) * Valeur_val(q); // on consruit la valeur des case de la matrice_multi
                            q = Suivant_Li(q);
                            p = Suivant_Li(p);
                            // on avance dans la liste de vecteur et de la matrice
                        }
                        else
                        {
                            if (Valeur_ligne(p) == l && Valeur_colonne(p) == c)
                            {
                                p = Suivant_Li(p);
                            }
                            else
                            {
                                if (Suivant_Li(q) != NULL)
                                {
                                    q = Suivant_Li(q);
                                }
                            }
                        }
                    }
                    if (q == NULL && p != NULL)
                    {
                        while (Valeur_ligne(p) == l) // si le vecteur est a null alors on passe a la ligne suivante de la de la matrice
                        {
                            p = Suivant_Li(p);
                            if (p == NULL)
                            {
                                break;
                            }
                        }
                    }
                    c++;
                }
                if (val != 0)
                {
                    if (*teteop == NULL) // si la tete n'est pas a NULL on creer la tete de la liste resultats
                    {
                        Allouer_Li(&*teteop);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, l);
                        Aff_val_colonne(*teteop, 0);
                        sauv = *teteop;
                    }
                    else // on construit les maillons de la liste
                    {
                        Allouer_Li(&tmp);
                        Aff_val(tmp, val);
                        Aff_val_ligne(tmp, l);
                        Aff_val_colonne(tmp, 0);
                        Aff_adr_Li(sauv, tmp);
                        sauv = Suivant_Li(sauv);
                    }
                }
                l++;
            }
        }
    }
    else
    {
        printf("ERROR , The number of columns in the first matrix should be equal to the number of rows in the second.");
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void multiplication_rep1(Pointeur_Li tete1, Pointeur_Li tete2, Pointeur_Li *tetemulti, int nbr_l1, int nbr_c1, int nbr_l2, int nbr_c2)
{
    int cpt = 0, j = 0;
    Pointeur_Li tetediv, tetemulvect, p, sauv, tmp;
    *tetemulti = NULL;
    if (nbr_c1 = nbr_l2)
    {
        if (tete1 != NULL && tete2 != NULL)
        {
            while (cpt < nbr_c2)
            {
                j = 0;
                tetediv = NULL;
                extraction_rep1(tete2, 0, cpt, nbr_l2, cpt, &tetediv); // on fait l'extraction d'un vecteur
                if (tetediv != NULL)
                {
                    multiplication_vect_rep1(tete1, tetediv, &tetemulvect, nbr_l1, nbr_c1, nbr_l2); // on fait la multiplication de l matrice avec le vecteur
                    p = tetemulvect;
                    if (tetemulvect != NULL)
                    {
                        while (j <= nbr_c1) // dans chauqe iteration dans cet while on va creer la liste mul apartir des resultas de la multiplication vecteur matrice
                        {
                            if (p != NULL)
                            {
                                if (*tetemulti == NULL) // creation de la tete
                                {
                                    Allouer_Li(&*tetemulti);
                                    Aff_val_ligne(*tetemulti, Valeur_ligne(p));
                                    Aff_val_colonne(*tetemulti, cpt);
                                    Aff_val(*tetemulti, Valeur_val(p));
                                    sauv = *tetemulti;
                                }
                                else // creation des maillons de la liste mul
                                {
                                    Allouer_Li(&tmp);
                                    Aff_val_ligne(tmp, Valeur_ligne(p));
                                    Aff_val_colonne(tmp, cpt);
                                    Aff_val(tmp, Valeur_val(p));
                                    Aff_adr_Li(sauv, tmp);
                                    sauv = Suivant_Li(sauv);
                                }
                                p = Suivant_Li(p);
                            }
                            j++;
                        }
                    }
                }
                cpt++;
            }
        }
    }
    else
    {
        printf("ERROR , The number of columns in the first matrix should be equal to the number of rows in the second.");
    }
    /*le resultat obtenue les lignes ne sont pas trier d'un ordre croissant
    car c'est le reultat de plusiers vecteur , donc on doit trier la liste par raport au champ de ligne pour quand puisse l'afficher*/
    tri_bulle_lig_rep1(&*tetemulti);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------FIN DES MODULES MULTIPLICATION----------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------LA TRANSPOSEE----------------------------------------------------------------------------------------------*/
void matrice_transposee_rep1(Pointeur_Li tete, Pointeur_Li *tetetr)
{
    Pointeur_Li w, tmp, q, p;
    p = Suivant_Li(tete);
    if (tete != NULL)
    {
        Allouer_Li(&w);
        *tetetr = w;
        Aff_val(*tetetr, Valeur_val(tete));
        /*on permute entre la valeur des collone et la valeur des lignes de la tete*/
        Aff_val_colonne(*tetetr, Valeur_ligne(tete));
        Aff_val_ligne(*tetetr, Valeur_colonne(tete));
        while (p != NULL) // on parcours le reste de la liste est a chaque fois on permute
        {
            Allouer_Li(&tmp);
            Aff_val_ligne(tmp, Valeur_colonne(p));
            Aff_val_colonne(tmp, Valeur_ligne(p));
            Aff_val(tmp, Valeur_val(p));
            Aff_adr_Li(w, tmp);
            p = Suivant_Li(p);
            w = Suivant_Li(w);
        }
    }
    tri_bulle_lig_rep1(&*tetetr); // on tri la liste transposé creer par raport au champ de ligne
}
/*---------------------------------------------------------LES OPERATIONS LOGIQUE-----------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------NON LOGIQUE-------------------------------------------------------------------------------------*/
void operation_non_rep1(Pointeur_Li tete, Pointeur_Li *teteop, int nbr_l, int nbr_c)
{
    Pointeur_Li p, sauv, tmp = NULL;
    int cpt = 0, l = 0, c = 0;
    p = tete;
    *teteop = NULL;
    while (cpt != nbr_c * nbr_l)
    {
        if (p == NULL || Valeur_ligne(p) != l || Valeur_colonne(p) != c)
        {
            if (*teteop == NULL)
            {
                Allouer_Li(&*teteop);
                Aff_val(*teteop, 1);
                Aff_val_colonne(*teteop, c);
                Aff_val_ligne(*teteop, l);
                sauv = *teteop;
            }
            else
            {
                Allouer_Li(&tmp);
                Aff_val(tmp, 1);
                Aff_val_colonne(tmp, c);
                Aff_val_ligne(tmp, l);
                Aff_adr_Li(sauv, tmp);
                sauv = Suivant_Li(sauv);
            }
        }
        if (p != NULL)
        {
            if (l == Valeur_ligne(p) && c == Valeur_colonne(p))
            {
                p = Suivant_Li(p);
            }
        }
        if (c == nbr_c - 1)
        {
            l++;
            c = 0;
        }
        else
        {
            c++;
        }
        cpt++;
    }
}
/*------------------------------------------------------------FIN NON LOGIQUE-------------------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------LE ET LOGIQUE-------------------------------------------------------------------------------------*/
void operation_et_rep1(Pointeur_Li tete1, Pointeur_Li tete2, Pointeur_Li *teteop)
{
    int val, control = 0;
    int checker = 0;
    *teteop = NULL;
    if (tete1 != NULL && tete2 != NULL)
    {
        Pointeur_Li p = tete1, q = tete2;
        while (p != NULL && q != NULL && *teteop == NULL) // on va traiter le cas de la tete
        {
            if (Valeur_colonne(p) == Valeur_colonne(q) && Valeur_ligne(p) == Valeur_ligne(q))
            {
                val = (Valeur_val(p) & Valeur_val(q));
                if (val != 0)
                {
                    Allouer_Li(&*teteop);
                    Aff_val(*teteop, val);
                    Aff_val_colonne(*teteop, Valeur_colonne(p));
                    Aff_val_ligne(*teteop, Valeur_ligne(p));
                }
                p = Suivant_Li(p);
                q = Suivant_Li(q);
            }
            else
            {
                if (Valeur_ligne(p) > Valeur_ligne(q))
                {
                    q = Suivant_Li(q);
                }
                else
                {
                    if (Valeur_ligne(p) < Valeur_ligne(q))
                    {
                        p = Suivant_Li(p);
                    }
                    else
                    {
                        if ((Valeur_ligne(p) == Valeur_ligne(q)) && (Valeur_colonne(p) > Valeur_colonne(q)))
                        {
                            q = Suivant_Li(q);
                        }
                        else
                        {
                            if ((Valeur_ligne(p) == Valeur_ligne(q)) && (Valeur_colonne(p) < Valeur_colonne(q)))
                            {
                                p = Suivant_Li(p);
                            }
                        }
                    }
                }
            }
        }
        Pointeur_Li tmp, sauv = *teteop;
        while (p != NULL && q != NULL)
        {
            checker = 0;
            while (checker != 1)
            {
                if ((Valeur_colonne(p) == Valeur_colonne(q)) && (Valeur_ligne(p) == Valeur_ligne(q)))
                {
                    val = (Valeur_val(p) & Valeur_val(q));
                    if (val != 0)
                    {
                        Allouer_Li(&tmp);
                        Aff_val(tmp, val);
                        Aff_val_colonne(tmp, Valeur_colonne(p));
                        Aff_val_ligne(tmp, Valeur_ligne(p));
                        Aff_adr_Li(sauv, tmp);
                        sauv = Suivant_Li(sauv);
                        control++;
                        checker = 1;
                    }
                    p = Suivant_Li(p);
                    q = Suivant_Li(q);
                }
                else
                {
                    if (Valeur_ligne(p) > Valeur_ligne(q))
                    {
                        q = Suivant_Li(q);
                    }
                    else
                    {
                        if (Valeur_ligne(p) < Valeur_ligne(q))
                        {
                            p = Suivant_Li(p);
                        }
                        else
                        {
                            if ((Valeur_ligne(p) == Valeur_ligne(q)) && (Valeur_colonne(p) > Valeur_colonne(q)))
                            {
                                q = Suivant_Li(q);
                            }
                            else
                            {
                                if ((Valeur_ligne(p) == Valeur_ligne(q)) && (Valeur_colonne(p) < Valeur_colonne(q)))
                                {
                                    p = Suivant_Li(p);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------------FIN ET LOGIQUE--------------------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------LE OU LOGIQUE-------------------------------------------------------------------------------------*/
void operation_ou_rep1(Pointeur_Li tete1, Pointeur_Li tete2, Pointeur_Li *teteop)
{
    int val;
    Pointeur_Li p = NULL, q = NULL, w = NULL, tmp = NULL;
    if (tete1 != NULL && tete2 != NULL)
    {
        if (Valeur_ligne(tete1) == Valeur_ligne(tete2))
        {
            if (Valeur_colonne(tete1) == Valeur_colonne(tete2))
            {
                Allouer_Li(&*teteop);
                val = Valeur_val(tete1) | Valeur_val(tete2);
                Aff_val(*teteop, val);
                Aff_val_ligne(*teteop, Valeur_ligne(tete1));
                Aff_val_colonne(*teteop, Valeur_colonne(tete1));
                p = Suivant_Li(tete1);
                q = Suivant_Li(tete2);
            }
            else
            {
                if (Valeur_colonne(tete1) > Valeur_colonne(tete2))
                {
                    Allouer_Li(&*teteop);
                    val = Valeur_val(tete2);
                    Aff_val(*teteop, val);
                    Aff_val_ligne(*teteop, Valeur_ligne(tete2));
                    Aff_val_colonne(*teteop, Valeur_colonne(tete2));
                    p = tete1;
                    q = Suivant_Li(tete2);
                }
                else
                {
                    if (Valeur_colonne(tete1) < Valeur_colonne(tete2))
                    {
                        Allouer_Li(&*teteop);
                        val = Valeur_val(tete1);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(tete1));
                        Aff_val_colonne(*teteop, Valeur_colonne(tete1));
                        q = tete2;
                        p = Suivant_Li(tete1);
                    }
                }
            }
        }
        else
        {
            if (Valeur_ligne(tete1) > Valeur_ligne(tete2))
            {
                Allouer_Li(&*teteop);
                val = Valeur_val(tete2);
                Aff_val(*teteop, val);
                Aff_val_ligne(*teteop, Valeur_ligne(tete2));
                Aff_val_colonne(*teteop, Valeur_colonne(tete2));
                p = tete1;
                q = Suivant_Li(tete2);
            }
            else
            {
                if (Valeur_ligne(tete1) < Valeur_ligne(tete2))
                {
                    Allouer_Li(&*teteop);
                    val = Valeur_val(tete1);
                    Aff_val(*teteop, val);
                    Aff_val_ligne(*teteop, Valeur_ligne(tete1));
                    Aff_val_colonne(*teteop, Valeur_colonne(tete1));
                    p = tete2;
                    q = Suivant_Li(tete1);
                }
            }
        }
        w = *teteop;
        while (p != NULL && q != NULL)
        {
            if (Valeur_ligne(p) == Valeur_ligne(q))
            {
                if (Valeur_colonne(p) < Valeur_colonne(q))
                {
                    Allouer_Li(&tmp);
                    val = Valeur_val(p);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(p));
                    Aff_val_colonne(tmp, Valeur_colonne(p));
                    Aff_adr_Li(w, tmp);
                    p = Suivant_Li(p);
                    w = Suivant_Li(w);
                }
                else
                {
                    if (Valeur_colonne(p) > Valeur_colonne(q))
                    {
                        Allouer_Li(&tmp);
                        val = Valeur_val(q);
                        Aff_val(tmp, val);
                        Aff_val_ligne(tmp, Valeur_ligne(q));
                        Aff_val_colonne(tmp, Valeur_colonne(q));
                        Aff_adr_Li(w, tmp);
                        q = Suivant_Li(q);
                        w = Suivant_Li(w);
                    }
                    else
                    {
                        if (Valeur_colonne(p) == Valeur_colonne(q))
                        {
                            Allouer_Li(&tmp);
                            val = Valeur_val(p) | Valeur_val(q);
                            Aff_val(tmp, val);
                            Aff_val_ligne(tmp, Valeur_ligne(p));
                            Aff_val_colonne(tmp, Valeur_colonne(p));
                            Aff_adr_Li(w, tmp);
                            p = Suivant_Li(p);
                            q = Suivant_Li(q);
                            w = Suivant_Li(w);
                        }
                    }
                }
            }
            else
            {
                if (Valeur_ligne(p) > Valeur_ligne(q))
                {
                    Allouer_Li(&tmp);
                    val = Valeur_val(q);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(q));
                    Aff_val_colonne(tmp, Valeur_colonne(q));
                    Aff_adr_Li(w, tmp);
                    q = Suivant_Li(q);
                    w = Suivant_Li(w);
                }
                else
                {
                    if (Valeur_ligne(p) < Valeur_ligne(q))
                    {
                        Allouer_Li(&tmp);
                        val = Valeur_val(p);
                        Aff_val(tmp, val);
                        Aff_val_ligne(tmp, Valeur_ligne(p));
                        Aff_val_colonne(tmp, Valeur_colonne(p));
                        Aff_adr_Li(w, tmp);
                        p = Suivant_Li(p);
                        w = Suivant_Li(w);
                    }
                }
            }
        }
        while (p != NULL || q != NULL)
        {
            if (p == NULL)
            {
                Allouer_Li(&tmp);
                val = Valeur_val(q);
                Aff_val(tmp, val);
                Aff_val_ligne(tmp, Valeur_ligne(q));
                Aff_val_colonne(tmp, Valeur_colonne(q));
                Aff_adr_Li(w, tmp);
                w = Suivant_Li(w);
                q = Suivant_Li(q);
            }
            else
            {
                if (q == NULL)
                {
                    Allouer_Li(&tmp);
                    val = Valeur_val(p);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(p));
                    Aff_val_colonne(tmp, Valeur_colonne(p));
                    Aff_adr_Li(w, tmp);
                    w = Suivant_Li(w);
                    p = Suivant_Li(p);
                }
            }
        }
    }
    else
    {
        if (tete1 == NULL) // Si la matrice1 contient que des 0
        {
            *teteop = tete2;
        }
        else
        {
            if (tete2 == NULL) // Si la matrice2 contient que des 0
            {
                *teteop = tete1;
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------------FIN OU LOGIQUE--------------------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------------LE OU Exlusif LOGIQUE--------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void operation_oux_rep1(Pointeur_Li tete1, Pointeur_Li tete2, Pointeur_Li *teteop)
{
    int val;
    Pointeur_Li p = tete1, q = tete2, w, tmp;
    *teteop = NULL;
    if (tete1 != NULL && tete2 != NULL)
    {
        while ((p != NULL || q != NULL) && *teteop == NULL) // creation de maillon de la tete de la liste addition
        {
            if (Valeur_ligne(p) == Valeur_ligne(q))
            {
                if (Valeur_colonne(p) == Valeur_colonne(q))
                {
                    val = Valeur_val(p) ^ Valeur_val(q);
                    if (val != 0)
                    {
                        Allouer_Li(&*teteop);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(p));
                        Aff_val_colonne(*teteop, Valeur_colonne(p));
                    }
                    p = Suivant_Li(p);
                    q = Suivant_Li(q);
                }
                else
                {
                    if (Valeur_colonne(p) > Valeur_colonne(q))
                    {
                        Allouer_Li(&*teteop);
                        val = Valeur_val(q);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(q));
                        Aff_val_colonne(*teteop, Valeur_colonne(q));
                        q = Suivant_Li(q);
                    }
                    else
                    {
                        if (Valeur_colonne(p) < Valeur_colonne(q))
                        {
                            Allouer_Li(&*teteop);
                            val = Valeur_val(p);
                            Aff_val(*teteop, val);
                            Aff_val_ligne(*teteop, Valeur_ligne(p));
                            Aff_val_colonne(*teteop, Valeur_colonne(p));
                            p = Suivant_Li(p);
                        }
                    }
                }
            }
            else
            {
                if (Valeur_ligne(p) > Valeur_ligne(q))
                {
                    Allouer_Li(&*teteop);
                    val = Valeur_val(q);
                    Aff_val(*teteop, val);
                    Aff_val_ligne(*teteop, Valeur_ligne(q));
                    Aff_val_colonne(*teteop, Valeur_colonne(q));
                    q = Suivant_Li(q);
                }
                else
                {
                    if (Valeur_ligne(p) < Valeur_ligne(q))
                    {
                        Allouer_Li(&*teteop);
                        val = Valeur_val(p);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(p));
                        Aff_val_colonne(*teteop, Valeur_colonne(p));
                        p = Suivant_Li(p);
                    }
                }
            }
            if (*teteop == NULL)
            {
                if (p == NULL && q != NULL)
                {
                    Allouer_Li(&*teteop);
                    val = Valeur_val(q);
                    Aff_val(*teteop, val);
                    Aff_val_ligne(*teteop, Valeur_ligne(q));
                    Aff_val_colonne(*teteop, Valeur_colonne(q));
                    q = Suivant_Li(q);
                }
                else
                {
                    if (q == NULL && p != NULL)
                    {
                        Allouer_Li(&*teteop);
                        val = Valeur_val(p);
                        Aff_val(*teteop, val);
                        Aff_val_ligne(*teteop, Valeur_ligne(p));
                        Aff_val_colonne(*teteop, Valeur_colonne(p));
                        p = Suivant_Li(p);
                    }
                }
            }
        }
        w = *teteop;
        while (p != NULL && q != NULL)
        {
            if (Valeur_ligne(p) == Valeur_ligne(q))
            {
                if (Valeur_colonne(p) < Valeur_colonne(q))
                {
                    val = Valeur_val(p);
                    Allouer_Li(&tmp);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(p));
                    Aff_val_colonne(tmp, Valeur_colonne(p));
                    Aff_adr_Li(w, tmp);
                    p = Suivant_Li(p);
                    w = Suivant_Li(w);
                }
                else
                {
                    if (Valeur_colonne(p) > Valeur_colonne(q))
                    {
                        Allouer_Li(&tmp);
                        val = Valeur_val(q);
                        Aff_val(tmp, val);
                        Aff_val_ligne(tmp, Valeur_ligne(q));
                        Aff_val_colonne(tmp, Valeur_colonne(q));
                        Aff_adr_Li(w, tmp);
                        q = Suivant_Li(q);
                        w = Suivant_Li(w);
                    }
                    else
                    {
                        if (Valeur_colonne(p) == Valeur_colonne(q))
                        {
                            val = Valeur_val(p) ^ Valeur_val(q);
                            if (val != 0)
                            {
                                Allouer_Li(&tmp);
                                Aff_val(tmp, val);
                                Aff_val_ligne(tmp, Valeur_ligne(p));
                                Aff_val_colonne(tmp, Valeur_colonne(p));
                                Aff_adr_Li(w, tmp);
                                w = Suivant_Li(w);
                            }
                            p = Suivant_Li(p);
                            q = Suivant_Li(q);
                        }
                    }
                }
            }
            else
            {
                if (Valeur_ligne(p) > Valeur_ligne(q))
                {
                    Allouer_Li(&tmp);
                    val = Valeur_val(q);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(q));
                    Aff_val_colonne(tmp, Valeur_colonne(q));
                    Aff_adr_Li(w, tmp);
                    q = Suivant_Li(q);
                    w = Suivant_Li(w);
                }
                else
                {
                    if (Valeur_ligne(p) < Valeur_ligne(q))
                    {
                        Allouer_Li(&tmp);
                        val = Valeur_val(p);
                        Aff_val(tmp, val);
                        Aff_val_ligne(tmp, Valeur_ligne(p));
                        Aff_val_colonne(tmp, Valeur_colonne(p));
                        Aff_adr_Li(w, tmp);
                        p = Suivant_Li(p);
                        w = Suivant_Li(w);
                    }
                }
            }
        }
        while (p != NULL || q != NULL)
        {
            if (p == NULL)
            {
                Allouer_Li(&tmp);
                val = Valeur_val(q);
                Aff_val(tmp, val);
                Aff_val_ligne(tmp, Valeur_ligne(q));
                Aff_val_colonne(tmp, Valeur_colonne(q));
                Aff_adr_Li(w, tmp);
                w = Suivant_Li(w);
                q = Suivant_Li(q);
            }
            else
            {
                if (q == NULL)
                {
                    Allouer_Li(&tmp);
                    val = Valeur_val(p);
                    Aff_val(tmp, val);
                    Aff_val_ligne(tmp, Valeur_ligne(p));
                    Aff_val_colonne(tmp, Valeur_colonne(p));
                    Aff_adr_Li(w, tmp);
                    w = Suivant_Li(w);
                    p = Suivant_Li(p);
                }
            }
        }
    }
    else
    {
        if (tete1 == NULL) // Si la matrice1 contient que des 0
        {
            *teteop = tete2;
        }
        else
        {
            if (tete2 == NULL) // Si la matrice2 contient que des 0
            {
                *teteop = tete1;
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------------FIN OU Exlusif LOGIQUE--------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Recherche_rep_1(Pointeur_Li tete, int val_lig, int val_col, Pointeur_Li *p, Pointeur_Li *precedent)
{
    int trouve;
    if (tete != NULL)
    {
        trouve = 0;
        *p = tete;
        while (*p != NULL && trouve == 0)
        {
            if (Valeur_ligne(*p) == val_lig && Valeur_colonne(*p) == val_col)
            {
                trouve = 1;
            }
            else
            {
                *precedent = *p;
                *p = Suivant_Li(*p);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void supp_rep1(Pointeur_Li *tete, int val_lig, int val_col)
{
    Pointeur_Li p, precedent;
    if (*tete != NULL)
    {
        if (Valeur_ligne(*tete) == val_lig && Valeur_colonne(*tete) == val_col)
        {
            p = *tete;
            *tete = Suivant_Li(*tete);
            Liberer_Li(p);
        }
        else
        {
            Recherche_rep_1(*tete, val_lig, val_col, &p, &precedent);
            if (p != NULL)
            {
                Aff_adr_Li(precedent, Suivant_Li(p));
                Liberer_Li(p);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void inserer_rep1(Pointeur_Li *tete, int val, int val_lig, int val_col, int position)
{
    Pointeur_Li p, q;
    int i;
    if (position == 1)
    {
        p = *tete;
        Allouer_Li(&*tete);
        Aff_adr_Li(*tete, p);
        Aff_val(*tete, val);
        Aff_val_colonne(*tete, val_col);
        Aff_val_ligne(*tete, val_lig);
    }
    else
    {
        p = *tete;
        i = 1;
        while (i != position - 1)
        {
            i++;
            p = Suivant_Li(p);
        }
        Allouer_Li(&q);
        Aff_adr_Li(q, Suivant_Li(p));
        Aff_adr_Li(p, q);
        Aff_val(q, val);
        Aff_val_colonne(q, val_col);
        Aff_val_ligne(q, val_lig);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
void modification_champ_rep1(Pointeur_Li *tete, int val, int val_lig, int val_col)
{
    Pointeur_Li p;
    int position = 1, checker = 0;
    if (*tete != NULL)
    {
        p = *tete;
        while (p != NULL)
        {
            if (Valeur_ligne(p) == val_lig && Valeur_colonne(p) == val_col)
            {
                if (val != 0)
                {
                    Aff_val(p, val);
                }
                else
                {
                    supp_rep1(&*tete, val_lig, val_col);
                }
                checker = 1;
            }
            if (Valeur_ligne(p) == val_lig && Valeur_colonne(p) > val_col)
            {
                break;
            }
            if (Valeur_ligne(p) > val_lig)
            {
                break;
            }
            p = Suivant_Li(p);
            position++;
        }
        if (checker != 1)
        {
            inserer_rep1(&*tete, val, val_lig, val_col, position);
        }
    }
    else
    {
        if (val != 0)
        {
            Allouer_Li(&*tete);
            Aff_val(*tete, val);
            Aff_val_ligne(*tete, val_lig);
            Aff_val_colonne(*tete, val_col);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*---------------------------------------------------FIN DES MODULES MODIFICATION PAR CHAMP-------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-----------------------------------------------------LA FIN DE LA 1ER REPRESENTATION------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------------LA 2EM REPRESENTATION-------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------------LA MACHINE ABSTRAITE--------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Allouer_lign(Pointeur_lign *P) // allouer un espace et retourner son adresse
{
    *P = (struct Maillon_lign *)malloc(sizeof(struct Maillon_lign));
    (*P)->Suiv_lign = NULL;
    (*P)->Suiv_col = NULL;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Allouer_col(Pointeur_col *P) // allouer un espace et retourner son adresse
{
    *P = (struct Maillon_col *)malloc(sizeof(struct Maillon_col));
    (*P)->Suiv_col = NULL;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Liberer_lign(Pointeur_lign P) // libérer l'espace déja allouer
{
    free(P);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Liberer_col(Pointeur_col P) // libérer l'espace déja allouer
{
    free(P);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Pointeur_lign Suivant_lign_l(Pointeur_lign P) // retourner l'adresse du prochain élément contenu dans le maillon P
{
    return (P->Suiv_lign);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Pointeur_col Suivant_col_l(Pointeur_lign P) // retourner l'adresse du prochain élément contenu dans le maillon P
{
    return (P->Suiv_col);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Pointeur_col Suivant_col_c(Pointeur_col P) // retourner l'adresse du prochain élément contenu dans le maillon P
{
    return (P->Suiv_col);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Typeelem_Li Valeur_ligne_rep2(Pointeur_lign P) // retourner l'information contenue dans le maillon P
{
    return (P->ligne);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Typeelem_Li Valeur_colonne_rep2(Pointeur_col P) // retourner l'information contenue dans le maillon P
{
    return (P->colonne);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Typeelem_Li Valeur_val_rep2(Pointeur_col P) // retourner l'information contenue dans le maillon P
{
    return (P->val_nonul);
}
void Aff_val_ligne_rep2(Pointeur_lign P, Typeelem_Li i) // affecter l'information au champ vam du maillon P
{
    P->ligne = i;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_val_colonne_rep2(Pointeur_col P, Typeelem_Li j) // affecter l'information au champ vam du maillon P
{
    P->colonne = j;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_val_rep2(Pointeur_col P, Typeelem_Li Val) // affecter l'information au champ vam du maillon P
{
    P->val_nonul = Val;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_adr_ligne(Pointeur_lign P, Pointeur_lign Q) // lier P à une autre adresse
{
    P->Suiv_lign = Q;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_adr_ligne_col(Pointeur_lign P, Pointeur_col Q) // lier P à une autre adresse
{
    P->Suiv_col = Q;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Aff_adr_col(Pointeur_col P, Pointeur_col Q) // lier P à une autre adresse
{
    P->Suiv_col = Q;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------LA FIN DE LA MACHINE ABSTRAITE-----------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------ LES MODULES DE LA 2EME REPRESENTATION-------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------LES MODULES CREATION-----------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void create_maillon_colonne(int val, int j, Pointeur_lign *z)
{
    Pointeur_col ptrcol, q;

    // creation d'un maillon de colonnes
    Allouer_col(&ptrcol);
    Aff_val_colonne_rep2(ptrcol, j);
    Aff_val_rep2(ptrcol, val);

    // Connecter avec la liste ds lignes
    if (Suivant_col_l(*z) == NULL)
        Aff_adr_ligne_col(*z, ptrcol);
    else
    {
        // d points sur la listes des colonnes
        q = Suivant_col_l(*z);
        while (Suivant_col_c(q) != NULL)
        {
            q = Suivant_col_c(q);
        }
        Aff_adr_col(q, ptrcol);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void creation_liste_ligne(Pointeur_lign *tete, int ligne) // fonction pour creer seulement la liste qui contient les nums de lignes
{
    for (int i = 0; i < ligne; i++)
    {
        Pointeur_lign p, q;
        Allouer_lign(&p);
        Aff_val_ligne_rep2(p, i);
        if (i == 0)
            *tete = p;
        else
        {
            q = *tete;
            while (Suivant_lign_l(q) != NULL)
            {
                q = Suivant_lign_l(q);
            }
            Aff_adr_ligne(q, p);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void create_liste_rep_2(Pointeur_lign *tete, int ligne, int colonne)
{
    int val;

    for (int i = 0; i < ligne; i++)
    {
        Pointeur_lign p, q;
        // creation d'un maillon de ligne
        Allouer_lign(&p);
        Aff_val_ligne_rep2(p, i);
        if (i == 0)
            *tete = p;
        else
        {
            q = *tete;
            while (Suivant_lign_l(q) != NULL)
            {
                q = Suivant_lign_l(q);
            }
            Aff_adr_ligne(q, p);
        }

        for (int j = 0; j < colonne; j++)
        {
            printf("Entrer la valeur de :  Matrix[%d,%d]--> ", i, j);
            scanf("%d", &val);
            if (val != 0)
            {
                create_maillon_colonne(val, j, &p);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------FIN DES MODULES CREATION-----------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*---------------------------------------------------------LES MODULES AFFICHAGE-----------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void affichage_liste_rep_2(Pointeur_lign tete)
{
    Pointeur_lign p;
    Pointeur_col q;
    p = tete;

    while (p != NULL)
    {
        if (Suivant_col_l(p) != NULL)
        {
            q = Suivant_col_l(p);

            while (q != NULL)
            {
                printf("==|[l=%d]-[c=%d]-[v=%d]|=", Valeur_ligne_rep2(p), Valeur_colonne_rep2(q), Valeur_val_rep2(q));

                q = Suivant_col_c(q);
            }
        }
        p = Suivant_lign_l(p);
    }
    printf("\n\n");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void affichage_matrice_rep2(Pointeur_lign tete, int nbr_l, int nbr_c)
{
    int cpt = 0;
    Pointeur_lign p1 = tete;
    Pointeur_col plig;
    while (p1 != NULL && Valeur_ligne_rep2(p1) < nbr_l)
    {
        plig = Suivant_col_l(p1);
        while (cpt < nbr_c)
        {
            if (plig != NULL)
            {
                if (cpt == Valeur_colonne_rep2(plig))
                {
                    printf("  %3d  ", Valeur_val_rep2(plig));
                    plig = Suivant_col_c(plig);
                }
                else
                {
                    printf("  %3d  ", 0);
                }
            }
            else
            {
                printf("  %3d  ", 0);
            }
            cpt++;
        }
        if (p1 != NULL)
        {
            cpt = 0;
            p1 = Suivant_lign_l(p1);
            printf("\n\n");
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------FIN DES MODULES AFFICHAGE-----------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------LES DIVISION(EXTRACTION,DIVISION SOUS MATRICE)-----------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void extraction_rep2(Pointeur_lign tete, int dep_l, int dep_c, int fin_l, int fin_c, Pointeur_lign *teteract)
{
    Pointeur_lign plig, q; // parcours les lignes
    Pointeur_col pcol /*parcours les colonnes*/, tetecol, sauv, tmp;
    int c, l, nbr_lsous = fin_l - dep_l, nbr_csous = fin_c - dep_c, cpti = 0, cptj = 0, cpt; // control les indices de la sous matrice
    plig = tete;
    *teteract = NULL;
    //---------------------------------------------------------//
    for (int i = 0; i <= nbr_lsous; i++)
    {
        Pointeur_lign tmp, sauv;
        Allouer_lign(&tmp);
        Aff_val_ligne_rep2(tmp, i);
        if (i == 0)
            *teteract = tmp;
        else
        {
            sauv = *teteract;
            while (Suivant_lign_l(sauv) != NULL)
            {
                sauv = Suivant_lign_l(sauv);
            }
            Aff_adr_ligne(sauv, tmp);
        }
    }
    //---------------------------------------------------------//
    q = *teteract;
    if (tete != NULL)
    {
        while (Valeur_ligne_rep2(plig) < dep_l) // plig deplace dans la liste des lignes jusqu'il trouve la valeur de debut de la sous matricess
        {
            plig = Suivant_lign_l(plig);
        }
        do
        {
            cptj = 0;
            tetecol = NULL;
            tmp = NULL;
            sauv = NULL;
            pcol = Suivant_col_l(plig);
            while (pcol != NULL)
            {
                if (Valeur_colonne_rep2(pcol) >= dep_c && Valeur_colonne_rep2(pcol) <= fin_c) // on verifier si la valeur des lignes de poiteurs pcol est entre dep_c et fin_c
                {
                    if (tetecol == NULL)
                    {
                        Allouer_col(&tetecol);
                        Aff_val_rep2(tetecol, Valeur_val_rep2(pcol));
                        Aff_val_colonne_rep2(tetecol, Valeur_colonne_rep2(pcol) - dep_c);
                        Aff_adr_ligne_col(q, tetecol);
                        sauv = tetecol;
                    }
                    else
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(pcol));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(pcol) - dep_c);
                        Aff_adr_col(sauv, tmp);
                        sauv = Suivant_col_c(sauv);
                    }
                }
                pcol = Suivant_col_c(pcol);
            }
            q = Suivant_lign_l(q);
            plig = Suivant_lign_l(plig);
        } while (plig != NULL && Valeur_ligne_rep2(plig) <= fin_l);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void divsousmatrice_rep2(Pointeur_lign tete, int nbr_l, int nbr_c, int divrow, int divcol)
{
    Pointeur_lign tetediv;
    int lig, col, tmpi, tmpj, cpt = 1, error = 0;
    do
    {
        if (divrow != 0 && divcol != 0) // on doit d'abord verifier si cet matrice est devisable par le nombre enter par l'utilisateur
        {
            col = (nbr_c / divcol);
            lig = (nbr_l / divrow);
            if (nbr_l % divrow == 0 && nbr_c % divcol == 0)
            {
                printf("\n \n LE RESULTAT DE LA DIVISION : \n");
                for (int i = 0; i < nbr_l; i = i + lig)
                {
                    for (int j = 0; j < nbr_c; j = j + col)
                    {
                        tmpi = i + lig;
                        tmpj = j + col;
                        extraction_rep2(tete, i, j, tmpi - 1, tmpj - 1, &tetediv);
                        printf("\n\n");
                        printf("LA SOUS MATRICE %d : \n", cpt);
                        affichage_matrice_rep2(tetediv, lig, col);
                        cpt++;
                    }
                }
            }
            else
            {
                error = 1;
            }
        }
        else
        {
            error = 1;
        }
        if (error == 1)
        {
            printf("Il faut que la matrice soit divisible , entrer autres valeurs SVP ");
        }
    } while (error == 1);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*---------------------------------------------------------FIN DES MODULES DIVISION------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/* -------------------------------------------------------------L'ADDITION---------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void addligne(Pointeur_lign plig1, Pointeur_lign plig2, Pointeur_lign *teteoplig)
{
    *teteoplig = NULL;
    Pointeur_col p1, p2, tmp = NULL, sauv = NULL;
    p1 = Suivant_col_l(plig1);
    p2 = Suivant_col_l(plig2);
    int val;
    if (p1 != NULL || p2 != NULL)
    {
        Allouer_lign(&*teteoplig);
        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
        Pointeur_col teteopcol = NULL;
        while (p1 != NULL && p2 != NULL)
        {
            if (teteopcol == NULL)
            {
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    val = Valeur_val_rep2(p1) + Valeur_val_rep2(p2);
                    if (val != 0)
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, val);
                        Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p1));
                        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                        Aff_adr_ligne_col(*teteoplig, teteopcol);
                    }
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, Valeur_val_rep2(p2));
                        Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p2));
                        Aff_adr_ligne_col(*teteoplig, teteopcol);
                        p2 = Suivant_col_c(p2);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            Allouer_col(&teteopcol);
                            Aff_val_rep2(teteopcol, Valeur_val_rep2(p1));
                            Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p1));
                            Aff_adr_ligne_col(*teteoplig, teteopcol);
                            p1 = Suivant_col_c(p1);
                        }
                    }
                }
                sauv = teteopcol;
            }
            else
            {
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    val = Valeur_val_rep2(p1) + Valeur_val_rep2(p2);
                    if (val != 0)
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, val);
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                        Aff_adr_col(sauv, tmp);
                        sauv = Suivant_col_c(sauv);
                    }
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                        Aff_adr_col(sauv, tmp);
                        p2 = Suivant_col_c(p2);
                        sauv = Suivant_col_c(sauv);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            Allouer_col(&tmp);
                            Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                            Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                            Aff_adr_col(sauv, tmp);
                            p1 = Suivant_col_c(p1);
                            sauv = Suivant_col_c(sauv);
                        }
                    }
                }
            }
        }
        while (p1 != NULL || p2 != NULL)
        {
            if (p1 == NULL)
            {
                if (teteopcol == NULL)
                {
                    Allouer_col(&teteopcol);
                    Aff_val_rep2(teteopcol, Valeur_val_rep2(p2));
                    Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p2));
                    Aff_adr_ligne_col(*teteoplig, teteopcol);
                    p2 = Suivant_col_c(p2);
                    sauv = teteopcol;
                }
                else
                {
                    Allouer_col(&tmp);
                    Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                    Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                    Aff_adr_col(sauv, tmp);
                    p2 = Suivant_col_c(p2);
                    sauv = Suivant_col_c(sauv);
                }
            }
            else
            {
                if (p2 == NULL)
                {
                    if (teteopcol == NULL)
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, Valeur_val_rep2(p1));
                        Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p1));
                        Aff_adr_ligne_col(*teteoplig, teteopcol);
                        p1 = Suivant_col_c(p1);
                        sauv = teteopcol;
                    }
                    else
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                        Aff_adr_col(sauv, tmp);
                        p1 = Suivant_col_c(p1);
                        sauv = Suivant_col_c(sauv);
                    }
                }
            }
        }
    }
    else
    {
        Allouer_lign(&*teteoplig);
        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
        Aff_adr_ligne_col(*teteoplig, NULL);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void addition_rep2(Pointeur_lign tete1, Pointeur_lign tete2, Pointeur_lign *teteop)
{
    Pointeur_lign p, q, sauv, tmp;
    *teteop = NULL;
    q = tete1;
    p = tete2;
    while (q != NULL || p != NULL)
    {
        if (*teteop == NULL)
        {
            addligne(p, q, &*teteop);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
            sauv = *teteop;
        }
        else
        {
            addligne(p, q, &tmp);
            Aff_adr_ligne(sauv, tmp);
            sauv = Suivant_lign_l(sauv);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void addition_multiple_rep2(Pointeur_lign tete1, Pointeur_lign tete2, Pointeur_lign *teteadd, int nbr_l, int nbr_c)
{
    int choix, cpt = 3;
    Pointeur_lign tete3, p = tete1, q = tete2;
    do
    {
        addition_rep2(p, q, &*teteadd);
        p = *teteadd;
        printf("ES QUE VOUS VOULEZ FAIRE UNE AUTRE ADDITION ? \n");
        printf("SI OUI ENTRER 1 \n");
        printf("SI NON ENTRER 2 \n");
        printf("TON CHOIX : ");
        scanf("%d", &choix);
        if (choix == 1)
        {
            printf("\n\nLE REMPLISSAGE DE LA MATRICE %d : \n\n", cpt);
            create_liste_rep_2(&tete3, nbr_l, nbr_c);
            affichage_liste_rep_2(tete3);
            affichage_matrice_rep2(tete3, nbr_l, nbr_c);
            q = tete3;
            cpt++;
        }
    } while (choix == 1);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*---------------------------------------------------------FIN DES MODULES ADDITION------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------------LA MULTIPLICATION----------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void multiplication_vect_rep2(Pointeur_lign tete, Pointeur_lign tetevect, Pointeur_lign *teteop, int nbr_l, int nbr_c, int nbr_lvect, int nbr_cvect)
{
    Pointeur_lign p, pvect, q = NULL;
    Pointeur_col tmp, sauv = NULL, teteopcol = NULL, r = NULL, rvect = NULL;
    int l = 0, c = 0, val = 0;
    //------------------------------------------------//
    for (int i = 0; i <= nbr_c; i++)
    {
        Pointeur_lign tmp, sauv;
        Allouer_lign(&tmp);
        Aff_val_ligne_rep2(tmp, i);
        if (i == 0)
            *teteop = tmp;
        else
        {
            sauv = *teteop;
            while (Suivant_lign_l(sauv) != NULL)
            {
                sauv = Suivant_lign_l(sauv);
            }
            Aff_adr_ligne(sauv, tmp);
        }
    }
    //-----------------------------------------------//
    q = *teteop;
    if (nbr_c == nbr_lvect)
    {
        if (tete != NULL && tetevect != NULL)
        {
            p = tete;
            while (p != NULL)
            {
                teteopcol = NULL;
                r = Suivant_col_l(p);
                pvect = tetevect;
                val = 0;
                while (pvect != NULL && r != NULL)
                {
                    rvect = Suivant_col_l(pvect);
                    if (rvect != NULL)
                    {
                        if (Valeur_colonne_rep2(r) == Valeur_ligne_rep2(pvect))
                        {
                            val = val + Valeur_val_rep2(rvect) * Valeur_val_rep2(r);
                            r = Suivant_col_c(r);
                            pvect = Suivant_lign_l(pvect);
                        }
                        else
                        {
                            if (Valeur_colonne_rep2(r) > Valeur_ligne_rep2(pvect))
                            {
                                pvect = Suivant_lign_l(pvect);
                            }
                            else
                            {
                                if (Valeur_colonne_rep2(r) < Valeur_ligne_rep2(pvect))
                                {
                                    r = Suivant_col_c(r);
                                }
                            }
                        }
                    }
                    else
                    {
                        pvect = Suivant_lign_l(pvect);
                    }
                }
                if (val != 0)
                {
                    if (teteopcol == NULL)
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, val);
                        Aff_val_colonne_rep2(teteopcol, 0);
                        Aff_adr_ligne_col(q, teteopcol);
                        q = Suivant_lign_l(q);
                        sauv = teteopcol;
                    }
                    else
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, val);
                        Aff_val_colonne_rep2(tmp, 0);
                        Aff_adr_col(sauv, tmp);
                        sauv = Suivant_col_c(sauv);
                    }
                }
                else
                {
                    q = Suivant_lign_l(q);
                }

                p = Suivant_lign_l(p);
            }
        }
    }
    else
    {
        printf("ERROR , The number of columns in the first matrix should be equal to the number of rows in the second.");
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void multiplication_rep2(Pointeur_lign tete1, Pointeur_lign tete2, int nbr_l1, int nbr_c1, int nbr_l2, int nbr_c2)
{
    int cpt = 0, j = 0;
    Pointeur_lign tetediv = NULL, tetemul = NULL, p;
    Pointeur_col q;
    int tab[nbr_l1][nbr_c2];
    if (nbr_c1 == nbr_l2)
    {
        if (tete1 != NULL && tete2 != NULL)
        {
            while (cpt < nbr_c2)
            {
                j = 0;
                extraction_rep2(tete2, 0, cpt, nbr_l2, cpt, &tetediv);
                if (tetediv != NULL)
                {
                    multiplication_vect_rep2(tete1, tetediv, &tetemul, nbr_l1, nbr_c1, nbr_l2, 1);
                    p = tetemul;
                    q = Suivant_col_l(p);
                    while (j <= nbr_c1)
                    {
                        q = Suivant_col_l(p);
                        if (q == NULL)
                        {
                            tab[Valeur_ligne_rep2(p)][cpt] = 0;
                            p = Suivant_lign_l(p);
                        }
                        else
                        {
                            if (q != NULL)
                            {
                                tab[Valeur_ligne_rep2(p)][cpt] = Valeur_val_rep2(q);
                                if (p != NULL)
                                {
                                    p = Suivant_lign_l(p);
                                }
                            }
                        }
                        j++;
                    }
                }
                cpt++;
            }
            for (int i = 0; i < nbr_l1; i++)
            {
                for (int j = 0; j < nbr_c2; j++)
                {
                    printf(" %3d ", tab[i][j]);
                }
                printf("\n\n");
            }
        }
    }
    else
    {
        printf("ERROR , The number of columns in the first matrix should be equal to the number of rows in the second.");
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------FIN DES MODULES MULTIPLICATION---------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------LA TRANSPOSEE-------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void transposee_rep2(Pointeur_lign tete, Pointeur_lign *tetetrans, int ligne, int colonne)
{
    //--------------------------------------------------------//
    creation_liste_ligne(&*tetetrans, colonne);
    //---------------------------------------------------------//
    Pointeur_lign p, q;
    Pointeur_col m;
    p = tete;
    int i = 0;
    while (i < ligne)
    {
        if (Suivant_col_l(p) != NULL)
        {
            m = Suivant_col_l(p);
            q = *tetetrans;
            int j = 0;
            while (j < colonne)
            {
                while (Valeur_colonne_rep2(m) != j && Suivant_lign_l(q) != NULL)
                {
                    q = Suivant_lign_l(q);
                    j++;
                }
                create_maillon_colonne(Valeur_val_rep2(m), i, &q);
                q = Suivant_lign_l(q);
                if (Suivant_col_c(m) != NULL)
                {
                    m = Suivant_col_c(m);
                }
                else
                {
                    break;
                }
                j++;
            }
        }
        i++;
        p = Suivant_lign_l(p);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------------FIN DE LA TRANSPOSEE----------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*---------------------------------------------------------LES OPERATIONS LOGIQUE--------------------------------------------------------------------------......*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------NON LOGIQUE-------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void operation_non_rep2(Pointeur_lign tete, Pointeur_lign *tete_non, int ligne, int colonne)
{
    // LA-CREATION-DE-LA-LISTE-QUI-CONTIENT-SEULEMENT-LES-NUMEROS-DES-LIGNES-POUR-"NON LISTE"//
    creation_liste_ligne(&*tete_non, ligne);
    //-------------------------------------------------------------------------------------//
    Pointeur_lign p, q;
    Pointeur_col m; //"m" le maillon qui va parcourir la liste des clonnes pour la premiere liste
    p = tete;       //"p" le maillon qui va parcourir la liste des lignes pour la premiere liste
    q = *tete_non;  //"q" le maillon qui va parcourir la liste des lignes pour la "NON liste"
    int i = 0;
    while (i < ligne)
    {
        if (Suivant_col_l(p) == NULL)
        {
            for (int j = 0; j < colonne; j++)
            {
                create_maillon_colonne(1, j, &q);
            }
        }
        if (Suivant_col_l(p) != NULL)
        {
            m = Suivant_col_l(p);
            int j = 0;
            while (j < colonne)
            {
                if (Valeur_colonne_rep2(m) != j)
                {
                    create_maillon_colonne(1, j, &q);
                }
                else
                {
                    if (Suivant_col_c(m) != NULL)
                    {
                        m = Suivant_col_c(m);
                    }
                }
                while (m == NULL && j < colonne)
                {
                    create_maillon_colonne(1, j, &q);
                    j++;
                }
                j++;
            }
        }
        i++;
        p = Suivant_lign_l(p);
        q = Suivant_lign_l(q);
    } // while
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------FIN NON LOGIQUE------------------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------LE ET LOGIQUE-------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void et_ligne(Pointeur_lign plig1, Pointeur_lign plig2, Pointeur_lign *teteoplig)
{
    *teteoplig = NULL;
    Pointeur_col p1, p2, tmp, sauv;
    p1 = Suivant_col_l(plig1);
    p2 = Suivant_col_l(plig2);
    int val;
    if (p1 != NULL || p2 != NULL)
    {
        Allouer_lign(&*teteoplig);
        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
        Pointeur_col teteopcol = NULL;
        while (p1 != NULL && p2 != NULL)
        {
            if (teteopcol == NULL)
            {
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    val = Valeur_val_rep2(p1) & Valeur_val_rep2(p2);
                    if (val != 0)
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, val);
                        Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p1));
                        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                        Aff_adr_ligne_col(*teteoplig, teteopcol);
                    }
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        p2 = Suivant_col_c(p2);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            p1 = Suivant_col_c(p1);
                        }
                    }
                }
                sauv = teteopcol;
            }
            else
            {
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    val = Valeur_val_rep2(p1) & Valeur_val_rep2(p2);
                    if (val != 0)
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, val);
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                        Aff_adr_col(sauv, tmp);
                        sauv = Suivant_col_c(sauv);
                    }
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        p2 = Suivant_col_c(p2);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            p1 = Suivant_col_c(p1);
                        }
                    }
                }
            }
        }
    }
    else
    {
        Allouer_lign(&*teteoplig);
        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
        Aff_adr_ligne_col(*teteoplig, NULL);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void operation_et_rep2(Pointeur_lign tete1, Pointeur_lign tete2, Pointeur_lign *teteop)
{
    Pointeur_lign p, q, sauv, tmp;
    *teteop = NULL;
    q = tete1;
    p = tete2;
    while (q != NULL || p != NULL)
    {
        if (*teteop == NULL)
        {
            et_ligne(p, q, &*teteop);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
            sauv = *teteop;
        }
        else
        {
            et_ligne(p, q, &tmp);
            Aff_adr_ligne(sauv, tmp);
            sauv = Suivant_lign_l(sauv);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-------------------------------------------------------------LE OU LOGIQUE-------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void ou_ligne(Pointeur_lign plig1, Pointeur_lign plig2, Pointeur_lign *teteoplig)
{
    *teteoplig = NULL;
    Pointeur_col p1, p2, tmp, sauv;
    p1 = Suivant_col_l(plig1);
    p2 = Suivant_col_l(plig2);
    int val;
    if (p1 != NULL || p2 != NULL)
    {
        while (p1 != NULL && p2 != NULL)
        {
            if (*teteoplig == NULL)
            {
                Allouer_lign(&*teteoplig);
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    Allouer_col(&tmp);
                    val = Valeur_val_rep2(p1) | Valeur_val_rep2(p2);
                    Aff_val_rep2(tmp, val);
                    Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                    Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                    Aff_adr_ligne_col(*teteoplig, tmp);
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                        Aff_adr_ligne_col(*teteoplig, tmp);
                        p2 = Suivant_col_c(p2);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            Allouer_col(&tmp);
                            Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                            Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                            Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                            Aff_adr_ligne_col(*teteoplig, tmp);
                            p1 = Suivant_col_c(p1);
                        }
                    }
                }
                sauv = tmp;
            }
            else
            {
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    Allouer_col(&tmp);
                    val = Valeur_val_rep2(p1) | Valeur_val_rep2(p2);
                    Aff_val_rep2(tmp, val);
                    Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                    Aff_adr_col(sauv, tmp);
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                    sauv = Suivant_col_c(sauv);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                        Aff_adr_col(sauv, tmp);
                        p2 = Suivant_col_c(p2);
                        sauv = Suivant_col_c(sauv);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            Allouer_col(&tmp);
                            Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                            Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                            Aff_adr_col(sauv, tmp);
                            p1 = Suivant_col_c(p1);
                            sauv = Suivant_col_c(sauv);
                        }
                    }
                }
            }
        }
        while (p1 != NULL || p2 != NULL)
        {
            if (p1 == NULL)
            {
                if (*teteoplig == NULL)
                {
                    Allouer_lign(&*teteoplig);
                    Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                    Allouer_col(&tmp);
                    Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                    Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                    Aff_adr_ligne_col(*teteoplig, tmp);
                    p2 = Suivant_col_c(p2);
                    sauv = tmp;
                }
                else
                {
                    Allouer_col(&tmp);
                    Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                    Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                    Aff_adr_col(sauv, tmp);
                    p2 = Suivant_col_c(p2);
                    sauv = Suivant_col_c(sauv);
                }
            }
            else
            {
                if (p2 == NULL)
                {
                    if (*teteoplig == NULL)
                    {
                        Allouer_lign(&*teteoplig);
                        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                        Aff_adr_ligne_col(*teteoplig, tmp);
                        p1 = Suivant_col_c(p1);
                        sauv = tmp;
                    }
                    else
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                        Aff_adr_col(sauv, tmp);
                        p1 = Suivant_col_c(p1);
                        sauv = Suivant_col_c(sauv);
                    }
                }
            }
        }
    }
    else
    {
        Allouer_lign(&*teteoplig);
        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
        Aff_adr_ligne_col(*teteoplig, NULL);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void operation_ou_rep2(Pointeur_lign tete1, Pointeur_lign tete2, Pointeur_lign *teteop)
{
    Pointeur_lign p, q, sauv, tmp;
    *teteop = NULL;
    q = tete1;
    p = tete2;
    while (q != NULL || p != NULL)
    {
        if (*teteop == NULL)
        {
            ou_ligne(p, q, &*teteop);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
            sauv = *teteop;
        }
        else
        {
            ou_ligne(p, q, &tmp);
            Aff_adr_ligne(sauv, tmp);
            sauv = Suivant_lign_l(sauv);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void oux_ligne(Pointeur_lign plig1, Pointeur_lign plig2, Pointeur_lign *teteoplig)
{
    *teteoplig = NULL;
    Pointeur_col p1, p2, tmp = NULL, sauv = NULL;
    p1 = Suivant_col_l(plig1);
    p2 = Suivant_col_l(plig2);
    int val;
    if (p1 != NULL || p2 != NULL)
    {
        Allouer_lign(&*teteoplig);
        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
        Pointeur_col teteopcol = NULL;
        while (p1 != NULL && p2 != NULL)
        {
            if (teteopcol == NULL)
            {
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    val = Valeur_val_rep2(p1) ^ Valeur_val_rep2(p2);
                    if (val != 0)
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, val);
                        Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p1));
                        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
                        Aff_adr_ligne_col(*teteoplig, teteopcol);
                    }
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, Valeur_val_rep2(p2));
                        Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p2));
                        Aff_adr_ligne_col(*teteoplig, teteopcol);
                        p2 = Suivant_col_c(p2);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            Allouer_col(&teteopcol);
                            Aff_val_rep2(teteopcol, Valeur_val_rep2(p1));
                            Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p1));
                            Aff_adr_ligne_col(*teteoplig, teteopcol);
                            p1 = Suivant_col_c(p1);
                        }
                    }
                }
                sauv = teteopcol;
            }
            else
            {
                if (Valeur_colonne_rep2(p1) == Valeur_colonne_rep2(p2))
                {
                    val = Valeur_val_rep2(p1) ^ Valeur_val_rep2(p2);
                    if (val != 0)
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, val);
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                        Aff_adr_col(sauv, tmp);
                        sauv = Suivant_col_c(sauv);
                    }
                    p1 = Suivant_col_c(p1);
                    p2 = Suivant_col_c(p2);
                }
                else
                {
                    if (Valeur_colonne_rep2(p1) > Valeur_colonne_rep2(p2))
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                        Aff_adr_col(sauv, tmp);
                        p2 = Suivant_col_c(p2);
                        sauv = Suivant_col_c(sauv);
                    }
                    else
                    {
                        if (Valeur_colonne_rep2(p1) < Valeur_colonne_rep2(p2))
                        {
                            Allouer_col(&tmp);
                            Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                            Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                            Aff_adr_col(sauv, tmp);
                            p1 = Suivant_col_c(p1);
                            sauv = Suivant_col_c(sauv);
                        }
                    }
                }
            }
        }
        while (p1 != NULL || p2 != NULL)
        {
            if (p1 == NULL)
            {
                if (teteopcol == NULL)
                {
                    Allouer_col(&teteopcol);
                    Aff_val_rep2(teteopcol, Valeur_val_rep2(p2));
                    Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p2));
                    Aff_adr_ligne_col(*teteoplig, teteopcol);
                    p2 = Suivant_col_c(p2);
                    sauv = teteopcol;
                }
                else
                {
                    Allouer_col(&tmp);
                    Aff_val_rep2(tmp, Valeur_val_rep2(p2));
                    Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p2));
                    Aff_adr_col(sauv, tmp);
                    p2 = Suivant_col_c(p2);
                    sauv = Suivant_col_c(sauv);
                }
            }
            else
            {
                if (p2 == NULL)
                {
                    if (teteopcol == NULL)
                    {
                        Allouer_col(&teteopcol);
                        Aff_val_rep2(teteopcol, Valeur_val_rep2(p1));
                        Aff_val_colonne_rep2(teteopcol, Valeur_colonne_rep2(p1));
                        Aff_adr_ligne_col(*teteoplig, teteopcol);
                        p1 = Suivant_col_c(p1);
                        sauv = teteopcol;
                    }
                    else
                    {
                        Allouer_col(&tmp);
                        Aff_val_rep2(tmp, Valeur_val_rep2(p1));
                        Aff_val_colonne_rep2(tmp, Valeur_colonne_rep2(p1));
                        Aff_adr_col(sauv, tmp);
                        p1 = Suivant_col_c(p1);
                        sauv = Suivant_col_c(sauv);
                    }
                }
            }
        }
    }
    else
    {
        Allouer_lign(&*teteoplig);
        Aff_val_ligne_rep2(*teteoplig, Valeur_ligne_rep2(plig1));
        Aff_adr_ligne_col(*teteoplig, NULL);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void operation_oux_rep2(Pointeur_lign tete1, Pointeur_lign tete2, Pointeur_lign *teteop)
{
    Pointeur_lign p, q, sauv, tmp;
    *teteop = NULL;
    q = tete1;
    p = tete2;
    while (q != NULL && p != NULL)
    {
        if (*teteop == NULL)
        {
            oux_ligne(p, q, &*teteop);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
            sauv = *teteop;
        }
        else
        {
            oux_ligne(p, q, &tmp);
            Aff_adr_ligne(sauv, tmp);
            sauv = Suivant_lign_l(sauv);
            p = Suivant_lign_l(p);
            q = Suivant_lign_l(q);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------------FIN OU Exlusif LOGIQUE--------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*--------------------------------------------------------FIN DES OPERATIONS LOGIQUE------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*----------------------------------------------------------MODIFICATION PAR CHAMP--------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void Recherche_rep2(Pointeur_lign tete, int val_lig, int val_col, Pointeur_lign *plig, Pointeur_col *p, Pointeur_col *precedent)
{
    int trouvel = 0, trouvec = 0;
    *p = NULL;
    *precedent = NULL;
    if (tete != NULL)
    {
        *plig = tete;
        while (*plig != NULL && trouvel != 1)
        {
            if (Valeur_ligne_rep2(*plig) == val_lig)
            {
                trouvel = 1;
            }
            else
            {
                *plig = Suivant_lign_l(*plig);
            }
        }
        *p = Suivant_col_l(*plig);
        while (*p != NULL && trouvec != 1)
        {
            if (Valeur_colonne_rep2(*p) == val_col)
            {
                trouvec = 1;
            }
            else
            {
                *precedent = *p;
                *p = Suivant_col_c(*p);
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void supp_rep2(Pointeur_lign tete, int val_lig, int val_col)
{
    Pointeur_col p, precedent, sauv;
    Pointeur_lign plig;
    if (tete != NULL)
    {
        Recherche_rep2(tete, val_lig, val_col, &plig, &p, &precedent);
        if (p != NULL || precedent != NULL)
        {
            if (precedent == NULL)
            {
                sauv = p;
                p = Suivant_col_c(sauv);
                Liberer_col(sauv);
                Aff_adr_ligne_col(plig, p);
            }
            else
            {
                if (p != NULL)
                {
                    Aff_adr_col(precedent, Suivant_col_c(p));
                    Liberer_col(p);
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void inserer_rep2(Pointeur_lign tete, int val, int val_lig, int val_col)
{
    Pointeur_lign p;
    Pointeur_col q, qnew, sauv, qprec; // qprec c'est le precedent de q
    int trouve = 0, cpt = 0;
    p = tete;
    if (tete != NULL)
    {
        while (Valeur_ligne_rep2(p) != val_lig)
        {
            p = Suivant_lign_l(p);
            if (p == NULL)
            {
                break;
            }
        }
    }
    q = Suivant_col_l(p);
    if (q == NULL)
    {
        Allouer_col(&qnew);
        Aff_val_rep2(qnew, val);
        Aff_val_colonne_rep2(qnew, val_col);
        Aff_adr_ligne_col(p, qnew);
    }
    else
    {
        while (q != NULL && trouve != 1)
        {
            if (Valeur_colonne_rep2(q) == val_col)
            {
                Aff_val_rep2(q, val);
                trouve = 1;
            }
            else
            {
                if (Valeur_colonne_rep2(q) > val_col)
                {
                    Allouer_col(&qnew);
                    Aff_val_rep2(qnew, val);
                    Aff_val_colonne_rep2(qnew, val_col);
                    sauv = q;
                    Aff_adr_ligne_col(p, qnew);
                    Aff_adr_col(qnew, q);
                    trouve = 1;
                }
                else
                {
                    if (Suivant_col_c(q) != NULL)
                    {
                        if (Valeur_colonne_rep2(Suivant_col_c(q)) > val_col)
                        {
                            if (Valeur_colonne_rep2(q) < val_col)
                            {
                                qprec = q;
                                q = Suivant_col_c(q);
                                Allouer_col(&qnew);
                                Aff_val_rep2(qnew, val);
                                Aff_val_colonne_rep2(qnew, val_col);
                                Aff_adr_col(qnew, q);
                                Aff_adr_col(qprec, qnew);
                                trouve = 1;
                            }
                        }
                    }
                }
            }
            qprec = q;
            q = Suivant_col_c(q);
        }
        if (trouve != 1)
        {
            Allouer_col(&qnew);
            Aff_val_rep2(qnew, val);
            Aff_val_colonne_rep2(qnew, val_col);
            Aff_adr_col(qprec, qnew);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void modification_champ_rep2(Pointeur_lign *tete, int val, int val_lig, int val_col)
{
    Pointeur_lign p;
    int checker = 0;
    if (*tete != NULL)
    {
        p = *tete;
        if (val == 0)
        {
            supp_rep2(*tete, val_lig, val_col);
        }
        else
        {
            inserer_rep2(*tete, val, val_lig, val_col);
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
/*-----------------------------------------------------FIN DES MODULES MODIFICATION PAR CHAMP----------------------------------------------------------------------------------------*/
/*--------------------------------------------------------LA FIN DE LA 2ER REPRESENTATION-------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------FIN----------------------------------------------------------------------------------------------------------*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
