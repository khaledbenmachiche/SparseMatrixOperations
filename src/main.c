#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BIBLIO.h"
void menu_intro()
{
  system("cls");
  system("Color 2");
  printf("------------------------------------------------------------------------- \n");
  printf("|       -ESI-          ECOLE SUPERIEUR D'INFORMATIQUE          -ESI-      |\n");
  printf("|                                                                         |\n");
  printf("|             TP N*1 ~MANIPULATION DE MATRICES CREUSES~ TP N*1            |\n");
  printf("|                                                                         |\n");
  printf("|  BINOME N*11:                                                           |\n");
  printf("|  BENMACHICHE KHALED.                                                    |\n");
  printf("|  BAZOULA CERINE.                                            -ALSDD-     |\n");
  printf("|                                                           SEMESTRE -2-  |\n");
  printf("---------------------------------------------------------------------------\n");
}
int menu_1()
{
  system("cls");
  system("Color 2");
  printf("----------------------------------------------------------------------- \n");
  printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
  printf("----------------------------------------------------------------------- \n");
  printf("|                                                                      |\n");
  printf("|   CHOISISSEZ LA REPRESENTATION DE MATRICE CREUSE QUE VOUS VOULEZ:    |\n");
  printf("|         >>[1] Representation -1-                                     |\n");
  printf("|         >>[2] Representation -2-                                     |\n");
  printf("|                                                                      |\n");
  printf("----------------------------------------------------------------------- \n");
  printf("\n");
  int rep;
  printf("-->>Entrez la representation choisit ici : ");
  scanf("%d", &rep);
  return rep;
}

int menu_operation()
{
  system("cls");
  system("Color 2");
  printf("----------------------------------------------------------------------- \n");
  printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
  printf("----------------------------------------------------------------------- \n");
  printf("|                                                                      |\n");
  printf("|   CHOISISSEZ L'OPERATIONS QUE VOULER FAIRE SUR VOTRE MATRICE   :     |\n");
  printf("|         >>[1] Extraction d'une sous matrice.                         |\n");
  printf("|         >>[2] Division d'une matrice en sous-blocs de taille egale.  |\n");
  printf("|         >>[3] Addition de deux ou plusieurs matrices.                |\n");
  printf("|         >>[4] Multiplication par vecteur.                            |\n");
  printf("|         >>[5] Multiplication de deux matrices.                       |\n");
  printf("|         >>[6] Transposee d'une matrice.                              |\n");
  printf("|         >>[7] Operations logiques : NON, ET, OU, OU exclusif.        |\n");
  printf("|         >>[8] Modification par champ                                 |\n");
  printf("|                                                                      |\n");
  printf("----------------------------------------------------------------------- \n");
  printf("\n");
  int ope;
  printf("-->>Entrez l'operation que vous avez choisit : ");
  scanf("%d", &ope);
  return ope;
}
int menu_operation_logique()
{
  system("cls");
  system("Color 2");
  printf("----------------------------------------------------------------------- \n");
  printf("|                MENU PRINCIPALE, CHOISISSEZ UNE OPTION                |\n");
  printf("----------------------------------------------------------------------- \n");
  printf("|                                                                      |\n");
  printf("|   CHOISISSEZ L'OPERATIONS LOGIQUE QUE VOULER FAIRE LA MATRICE :      |\n");
  printf("|         >>[1] L'operation logique 'NON'                              |\n");
  printf("|         >>[2] L'operation logique 'ET'                               |\n");
  printf("|         >>[3] L'operation logique 'OU'                               |\n");
  printf("|         >>[4] L'operation logique 'OU exclusif'                      |\n");
  printf("|                                                                      |\n");
  printf("----------------------------------------------------------------------- \n");
  printf("\n");
  int oplg;
  printf("-->>Entrezl'operation que vous avez choisit : ");
  scanf("%d", &oplg);
  return oplg;
}
void menu_quitter()
{
  printf("-------------------------------------------------------------------------- \n");
  printf("|                                                                        |\n");
  printf("|              MERCI                         MERCI                       |\n");
  printf("|           MERCI MERCI                   MERCI MERCI                    |\n");
  printf("|         MERCI MERCI MERCI             MERCI MERCI MERCI                |\n");
  printf("|       MERCI MERCI MERCI MERCI      MERCI MERCI MERCI MERCI             |\n");
  printf("|    MERCI MERCI MERCI MERCI MERCI MERCI MERCI MERCI MERCI MERCI         |\n");
  printf("|       MERCI MERCI MERCI MERCI      MERCI MERCI MERCI MERCI             |\n");
  printf("|         MERCI MERCI MERCI             MERCI MERCI MERCI                |\n");
  printf("|             MERCI MERCI                   MERCI MERCI                  |\n");
  printf("|              MERCI                         MERCI                       |\n");
  printf("|                                                                        |\n");
  printf("-------------------------------------------------------------------------- \n");
}

void main()
{
  int divrow, divcol, nbr_c, nbr_l, nbr_lvect, nbr_l2, nbr_c2;
  Pointeur_Li tete1, tete2, teteop, teteract1;
  Pointeur_lign teterep1, teteoprep2, teterep2, teteract2;
  int representation, operation1, oper_logique1, operation2, oper_logique2;
  char ch;
  menu_intro();
  printf("\n");
  printf("\n");
  printf("press charactere key to continue......");
  scanf("%s", &ch);
  char reponce = 'y';
  while (reponce == 'y')
  {
    tete1 = NULL;
    tete2 = NULL;
    teteop = NULL;
    representation = menu_1();
    switch (representation) // choisire la representation
    {
    case 1: // representation 1
      operation1 = menu_operation();
      //----------------------------------------------------------------//
      switch (operation1) // operation sur la representation -1-
      {
      case 1:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                EXTRACTION D'UNE MATRICE REPRESENTATION -1-            |\n");
        printf("----------------------------------------------------------------------- \n");
        int dep_l, dep_c, fin_c, fin_l;
        printf("Entrer le nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer le nombre de colonne : ");
        scanf("%d", &nbr_c);
        creation_liste_rep1(&tete1, nbr_l, nbr_c);
        Affichage_LLC_rep1(tete1);
        Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        printf("ligne.Initial --> ");
        scanf("%d", &dep_l);
        printf("colonne.Initial --> ");
        scanf("%d", &dep_c);
        printf("ligne.final --> ");
        scanf("%d", &fin_l);
        printf("colonne.final --> ");
        scanf("%d", &fin_c);
        while (fin_c > nbr_c && fin_c <= 0 && fin_c < dep_c)
        {
          printf("   - Votre matrice contient %d colonnes vous ne devez pas le depasser : ", nbr_c);
          scanf("%d", &fin_c);
        }
        extraction_rep1(tete1, dep_l, dep_c, fin_l, fin_c, &teteract1);
        Affichage_LLC_rep1(teteract1);
        int nbr_lsous = fin_l - dep_l + 1, nbr_csous = fin_c - dep_c + 1;
        Affichage_matrice_rep1(teteract1, nbr_lsous, nbr_csous);
        break;
      case 2:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                DIVISION D'UNE MATRICE REPRESENTATION -1-              |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\n LE REMPLISSAGE DE LA MATRICE : \n\n");
        creation_liste_rep1(&tete1, nbr_l, nbr_c);
        printf("\n");
        printf("LA MATRICE : \n");
        Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        printf("Entrer le numero de lig de division ");
        scanf("%d", &divrow);
        printf("Entrer le numero de collonne de division ");
        scanf("%d", &divcol);
        printf("\n \n les matrices divise sont : \n");
        divsousmatrice_rep1(tete1, nbr_l, nbr_c, divrow, divcol);
        break;
      case 3:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                ADDITION D'UNE MATRICE REPRESENTATION -1-              |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne des deux matrice : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne des deux matrice : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE 1 : \n\n");
        creation_liste_rep1(&tete1, nbr_l, nbr_c);
        Affichage_LLC_rep1(tete1);
        Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE 2 : \n\n");
        creation_liste_rep1(&tete2, nbr_l, nbr_c);
        Affichage_LLC_rep1(tete2);
        Affichage_matrice_rep1(tete2, nbr_l, nbr_c);
        addition_multiple_rep1(tete1, tete2, &teteop, nbr_l, nbr_c);
        printf("le resultat de l'addition : \n");
        Affichage_LLC_rep1(teteop);
        Affichage_matrice_rep1(teteop, nbr_l, nbr_c);
        break;
      case 4:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                 MULTIPLICATION PAR VECTEUR REPRESENTATION -1-         |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
        creation_liste_rep1(&tete1, nbr_l, nbr_c);
        Affichage_LLC_rep1(tete1);
        Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        printf("Entrer nombre de ligne du vecteur : ");
        scanf("%d", &nbr_lvect);
        printf("LE REMPLISSAGE DE VECTEUR : ");
        creation_liste_rep1(&tete2, nbr_lvect, 1);
        Affichage_LLC_rep1(tete2);
        Affichage_matrice_rep1(tete2, nbr_lvect, 1);
        printf("le resultats de la multiplication est : \n");
        multiplication_vect_rep1(tete1, tete2, &teteop, nbr_l, nbr_c, nbr_lvect /*, 1*/);
        Affichage_LLC_rep1(teteop);
        Affichage_matrice_rep1(teteop, nbr_l, 1);
        break;
      case 5:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|               MULTIPLICATION DE DEUX MATRICE REPRESENTATION -1-       |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA 1ERE MATRICE : \n\n");
        creation_liste_rep1(&tete1, nbr_l, nbr_c);
        Affichage_LLC_rep1(tete1);
        Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l2);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c2);
        printf("\n\nLE REMPLISSAGE DE LA 2EM MATRICE : \n\n");
        creation_liste_rep1(&tete2, nbr_l2, nbr_c2);
        Affichage_LLC_rep1(tete2);
        Affichage_matrice_rep1(tete2, nbr_l2, nbr_c2);
        printf("le resultats de la multiplication est : \n");
        multiplication_rep1(tete1, tete2, &teteop, nbr_l, nbr_c, nbr_l2, nbr_c2);
        Affichage_LLC_rep1(teteop);
        Affichage_matrice_rep1(teteop, nbr_l, nbr_c2);
        break;
      case 6:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|               TRANSPOSEE D'UNE MATRICE REPRESENTATION -1-            |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
        creation_liste_rep1(&tete1, nbr_l, nbr_c);
        Affichage_LLC_rep1(tete1);
        Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        matrice_transposee_rep1(tete1, &teteop);
        printf("LE MATRICE TRANSPOSE : \n\n ");
        Affichage_LLC_rep1(teteop);
        Affichage_matrice_rep1(teteop, nbr_c, nbr_l);
        break;
      case 7:
        //--------------------------------------------------------//
        oper_logique1 = menu_operation_logique();
        switch (oper_logique1) // operation logique sur representation -1-
        {
        case 1:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'NON' REPRESENTATION -1-              |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
          creation_liste_rep1(&tete1, nbr_l, nbr_c);
          Affichage_LLC_rep1(tete1);
          Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
          operation_non_rep1(tete1, &teteop, nbr_l, nbr_c);
          printf("LE NON DE LA MATRICE  : \n ");
          Affichage_LLC_rep1(teteop);
          Affichage_matrice_rep1(teteop, nbr_l, nbr_c);
          break;
        case 2:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'ET' REPRESENTATION -1-               |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne des deux matrices : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne des deux matrices : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA 1ERE MATRICE : \n\n");
          creation_liste_rep1(&tete1, nbr_l, nbr_c);
          Affichage_LLC_rep1(tete1);
          Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA 2EM MATRICE : \n\n");
          creation_liste_rep1(&tete2, nbr_l, nbr_c);
          Affichage_LLC_rep1(tete2);
          Affichage_matrice_rep1(tete2, nbr_l, nbr_c);
          operation_et_rep1(tete1, tete2, &teteop);
          printf("le resultat d'operations logique et : \n");
          Affichage_LLC_rep1(teteop);
          Affichage_matrice_rep1(teteop, nbr_l, nbr_c);
          break;
        case 3:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'OU' REPRESENTATION -1-               |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne des deux matrices : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne des deux matrices : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA 1ERE MATRICE : \n\n");
          creation_liste_rep1(&tete1, nbr_l, nbr_c);
          Affichage_LLC_rep1(tete1);
          Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA 2EM MATRICE : \n\n");
          creation_liste_rep1(&tete2, nbr_l, nbr_c);
          Affichage_LLC_rep1(tete2);
          Affichage_matrice_rep1(tete2, nbr_l, nbr_c);
          operation_ou_rep1(tete1, tete2, &teteop);
          printf("le resultat d'operations logique ou : \n");
          Affichage_LLC_rep1(teteop);
          Affichage_matrice_rep1(teteop, nbr_l, nbr_c);
          break;
        case 4:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'OU exclusif' REPRESENTATION -1-      |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne des deux matrices : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne des deux matrices : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA 1ERE MATRICE : \n\n");
          creation_liste_rep1(&tete1, nbr_l, nbr_c);
          Affichage_LLC_rep1(tete1);
          Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA 2EM MATRICE : \n\n");
          creation_liste_rep1(&tete2, nbr_l, nbr_c);
          Affichage_LLC_rep1(tete2);
          Affichage_matrice_rep1(tete2, nbr_l, nbr_c);
          operation_oux_rep1(tete1, tete2, &teteop);
          printf("le resultat d'operations logique oux : \n");
          Affichage_LLC_rep1(teteop);
          Affichage_matrice_rep1(teteop, nbr_l, nbr_c);
          break;
        } // switch
        //--------------------------------------------------------//
        break;
      case 8:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                MODIFICATION PAR CHAMP REPRESENTATION -1-             |\n");
        printf("----------------------------------------------------------------------- \n");
        int cpt, val, vallig, valcol;
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
        creation_liste_rep1(&tete1, nbr_l, nbr_c);
        Affichage_LLC_rep1(tete1);
        Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        printf("Enter la ligne du champ que vous voulez modifier : ");
        scanf("%d", &vallig);
        printf("Enter la colonne du champ que vous voulez modifier : ");
        scanf("%d", &valcol);
        printf("Enter la nouvelle valeur : ");
        scanf("%d", &val);
        if (vallig < nbr_l && valcol < nbr_c && valcol >= 0 && vallig >= 0)
        {
          modification_champ_rep1(&tete1, val, vallig, valcol);
          Affichage_LLC_rep1(tete1);
          Affichage_matrice_rep1(tete1, nbr_l, nbr_c);
        }
        else
        {
          printf("LE CHAMP N'EXISTE PAS");
        }
        break;
      } // switch
      break;

    case 2: // representation 2

      operation2 = menu_operation();
      switch (operation2) // operation sur la representation -2-
      {
      case 1:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                EXTRACTION D'UNE MATRICE REPRESENTATION -2-            |\n");
        printf("----------------------------------------------------------------------- \n");
        int dep_l, dep_c, fin_c, fin_l;
        teteract2 = NULL;
        printf("Entrer le nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer le nombre de colonne : ");
        scanf("%d", &nbr_c);
        create_liste_rep_2(&teterep1, nbr_l, nbr_c);
        affichage_liste_rep_2(teterep1);
        affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        printf("ligne.Ini --> ");
        scanf("%d", &dep_l);
        printf("colonne.Ini --> ");
        scanf("%d", &dep_c);
        printf("ligne.final --> ");
        scanf("%d", &fin_l);
        printf("colonne.final --> ");
        scanf("%d", &fin_c);
        extraction_rep2(teterep1, dep_l, dep_c, fin_l, fin_c, &teteract2);
        affichage_liste_rep_2(teteract2);
        int nbr_lsous = fin_l - dep_l + 1, nbr_csous = fin_c - dep_c + 1;
        affichage_matrice_rep2(teteract2, nbr_lsous, nbr_csous);
        break;
      case 2:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                DIVISION D'UNE MATRICE REPRESENTATION -2-              |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\n LE REMPLISSAGE DE LA MATRICE : \n\n");
        create_liste_rep_2(&teterep1, nbr_l, nbr_c);
        printf("\n");
        printf("LA MATRICE : \n");
        affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        printf("Entrer le numero de lig de division ");
        scanf("%d", &divrow);
        printf("Entrer le numero de collonne de division ");
        scanf("%d", &divcol);
        printf("\n \n les matrices divise sont : \n");
        divsousmatrice_rep2(teterep1, nbr_l, nbr_c, divrow, divcol);
        break;
      case 3:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                ADDITION D'UNE MATRICE REPRESENTATION -2-              |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne des deux matrice : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne des deux matrice : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE 1 : \n\n");
        create_liste_rep_2(&teterep1, nbr_l, nbr_c);
        affichage_liste_rep_2(teterep1);
        affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE 2 : \n\n");
        create_liste_rep_2(&teterep2, nbr_l, nbr_c);
        affichage_liste_rep_2(teterep2);
        affichage_matrice_rep2(teterep2, nbr_l, nbr_c);
        addition_multiple_rep2(teterep1, teterep2, &teteoprep2, nbr_l, nbr_c);
        printf("l'affichage de la liste obtenue : \n");
        affichage_liste_rep_2(teteoprep2);
        printf("le resultat de l'addition : \n");
        affichage_matrice_rep2(teteoprep2, nbr_l, nbr_c);
        break;
      case 4:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                 MULTIPLICATION PAR VECTEUR REPRESENTATION -2-         |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
        create_liste_rep_2(&teterep1, nbr_l, nbr_c);
        affichage_liste_rep_2(teterep1);
        affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        printf("Entrer nombre de ligne du vecteur : ");
        scanf("%d", &nbr_lvect);
        printf("LE REMPLISSAGE DE VECTEUR : ");
        create_liste_rep_2(&teterep2, nbr_lvect, 1);
        affichage_liste_rep_2(teterep2);
        affichage_matrice_rep2(teterep2, nbr_lvect, 1);
        multiplication_vect_rep2(teterep1, teterep2, &teteoprep2, nbr_l, nbr_c, nbr_lvect, 1);
        printf("l'affichage de la liste obtenue : \n");
        affichage_liste_rep_2(teteoprep2);
        printf("le resultats de la multiplication est : \n");
        affichage_matrice_rep2(teteoprep2, nbr_l, 1);

        break;
      case 5:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|               MULTIPLICATION DE DEUX MATRICE REPRESENTATION -2-       |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA 1ERE MATRICE : \n\n");
        create_liste_rep_2(&teterep1, nbr_l, nbr_c);
        affichage_liste_rep_2(teterep1);
        affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l2);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c2);
        printf("\n\nLE REMPLISSAGE DE LA 2EM MATRICE : \n\n");
        create_liste_rep_2(&teterep2, nbr_l2, nbr_c2);
        affichage_liste_rep_2(teterep2);
        affichage_matrice_rep2(teterep2, nbr_l2, nbr_c2);
        printf("le resultats de la multiplication est : \n");
        multiplication_rep2(teterep1, teterep2, nbr_l, nbr_c, nbr_l2, nbr_c2);
        break;
      case 6:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|               TRANSPOSEE D'UNE MATRICE REPRESENTATION -2-            |\n");
        printf("----------------------------------------------------------------------- \n");
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
        create_liste_rep_2(&teterep1, nbr_l, nbr_c);
        affichage_liste_rep_2(teterep1);
        affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        transposee_rep2(teterep1, &teteoprep2, nbr_l, nbr_c);
        printf("LE MATRICE TRANSPOSE : \n\n ");
        affichage_liste_rep_2(teteoprep2);
        affichage_matrice_rep2(teteoprep2, nbr_c, nbr_l);
        break;
      case 7:
        //-----------------------------------------------------------//
        oper_logique2 = menu_operation_logique();
        switch (oper_logique2) // operation logique sur representation -1-
        {
        case 1:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'NON' REPRESENTATION -2-              |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
          create_liste_rep_2(&teterep1, nbr_l, nbr_c);
          affichage_liste_rep_2(teterep1);
          affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
          operation_non_rep2(teterep1, &teteoprep2, nbr_l, nbr_c);
          printf("LE NON DE LA MATRICE  : \n ");
          affichage_liste_rep_2(teteoprep2);
          affichage_matrice_rep2(teteoprep2, nbr_l, nbr_c);
          break;
        case 2:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'ET' REPRESENTATION -2-               |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne des deux matrice : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne des deux matrice : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE 1 : \n\n");
          create_liste_rep_2(&teterep1, nbr_l, nbr_c);
          affichage_liste_rep_2(teterep1);
          affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE 2 : \n\n");
          create_liste_rep_2(&teterep2, nbr_l, nbr_c);
          affichage_liste_rep_2(teterep2);
          affichage_matrice_rep2(teterep2, nbr_l, nbr_c);
          operation_et_rep2(teterep1, teterep2, &teteoprep2);
          printf("l'affichage de la liste obtenue : \n");
          affichage_liste_rep_2(teteoprep2);
          printf("le resultat de et logique : \n");
          affichage_matrice_rep2(teteoprep2, nbr_l, nbr_c);
          break;
        case 3:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'OU' REPRESENTATION -2-               |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne des deux matrice : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne des deux matrice : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE 1 : \n\n");
          create_liste_rep_2(&teterep1, nbr_l, nbr_c);
          affichage_liste_rep_2(teterep1);
          affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE 2 : \n\n");
          create_liste_rep_2(&teterep2, nbr_l, nbr_c);
          affichage_liste_rep_2(teterep2);
          affichage_matrice_rep2(teterep2, nbr_l, nbr_c);
          operation_ou_rep2(teterep1, teterep2, &teteoprep2);
          printf("l'affichage de la liste obtenue : \n");
          affichage_liste_rep_2(teteoprep2);
          printf("le resultat de ou logique : \n");
          affichage_matrice_rep2(teteoprep2, nbr_l, nbr_c);
          break;
        case 4:
          system("cls");
          printf("----------------------------------------------------------------------- \n");
          printf("|               OPERATION LOGIQUE 'OU exclusif' REPRESENTATION -2-      |\n");
          printf("----------------------------------------------------------------------- \n");
          printf("Entrer nombre de ligne des deux matrice : ");
          scanf("%d", &nbr_l);
          printf("Entrer nombre de colonne des deux matrice : ");
          scanf("%d", &nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE 1 : \n\n");
          create_liste_rep_2(&teterep1, nbr_l, nbr_c);
          affichage_liste_rep_2(teterep1);
          affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
          printf("\n\nLE REMPLISSAGE DE LA MATRICE 2 : \n\n");
          create_liste_rep_2(&teterep2, nbr_l, nbr_c);
          affichage_liste_rep_2(teterep2);
          affichage_matrice_rep2(teterep2, nbr_l, nbr_c);
          operation_oux_rep2(teterep1, teterep2, &teteoprep2);
          printf("l'affichage de la liste obtenue : \n");
          affichage_liste_rep_2(teteoprep2);
          printf("le resultat de ou exlusif : \n");
          affichage_matrice_rep2(teteoprep2, nbr_l, nbr_c);
          break;
        } // switch
        //----------------------------------------------------------//
        break;
      case 8:
        system("cls");
        printf("----------------------------------------------------------------------- \n");
        printf("|                MODIFICATION PAR CHAMP REPRESENTATION -2-             |\n");
        printf("----------------------------------------------------------------------- \n");
        int cpt, val, vallig, valcol;
        Pointeur_Li tete;
        printf("Entrer nombre de ligne : ");
        scanf("%d", &nbr_l);
        printf("Entrer nombre de colonne : ");
        scanf("%d", &nbr_c);
        printf("\n\nLE REMPLISSAGE DE LA MATRICE : \n\n");
        create_liste_rep_2(&teterep1, nbr_l, nbr_c);
        affichage_liste_rep_2(teterep1);
        affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        printf("Enter la ligne du champ que vous voulez modifier : ");
        scanf("%d", &vallig);
        printf("Enter la colonne du champ que vous voulez modifier : ");
        scanf("%d", &valcol);
        printf("Enter la nouvelle valeur : ");
        scanf("%d", &val);
        if (vallig <= nbr_l && valcol <= nbr_c && valcol >= 0 && vallig >= 0)
        {
          modification_champ_rep2(&teterep1, val, vallig, valcol);
          affichage_liste_rep_2(teterep1);
          affichage_matrice_rep2(teterep1, nbr_l, nbr_c);
        }
        else
        {
          printf("LE CHAMP N'EXISTE PAS");
        }
        break;
      }
      break;
    }
    printf("\n");
    printf("\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("--->>> Est que vous voulez faire d'autre operation sur les matrices creuses (y/n) : ");
    scanf("%s", &reponce);
    printf("-------------------------------------------------------------------------------\n");
  }
  system("cls");
  menu_quitter();
}
