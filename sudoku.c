/**
* @page Programme jeu de sudoku.
* @author BROSSARD
* @version 1.0
* @date 29 novembre 2023
* Ce programme propose de jouer a une partie de sudoku a partire d'une grille de sudoku externe
*/

#include <stdio.h>
#include <stdlib.h>
//===========================================================================
//------------------------------constante------------------------------------
//===========================================================================

#define N 3
/**
* @def TAILLE
* @brief constante pour donner la hauteur et largeur de la grille
*/
const int TAILLE = 9;
/**
* @def VICTOIRE
* @brief constante pour donner la valeur du tableau fini
*/
const int VICTOIRE = 405;

//constante pour l'affichage de la grille
/**
* @def HORIZONTAL
* @brief constante pour l'affichage du tableau
*/
const char HORIZONTAL = '-';
/**
* @def VERTICAL
* @brief constante pour l'affichage du tableau
*/
const char VERTICAL = '|';
/**
* @def CROISEMENT
* @brief constante pour l'affichage du tableau
*/
const char CROISEMENT = '+';
/**
* @def VIDE
* @brief constante pour l'affichage du tableau
*/
const char VIDE = '.';
/**
* @def ESPACEMENT
* @brief constante pour l'affichage du tableau
*/
const char ESPACEMENT = ' ';
/**
* @def INDENTATION
* @brief constante pour l'affichage du tableau
*/
const char INDENTATION = 5;

//type de la grille
/**
* @typedef tGrille
* @brief type tableau de N*N par N*N entier
* Le type tGrille sert pour le format des donné de la grille de sudoku
*/
typedef int tGrille[N*N][N*N];

//===========================================================================
//------------------------------fonction-------------------------------------
//===========================================================================


/**
* @fn void afficherGrille(tGrille grille)
* @brief Affiche la grille de jeu.
* @param grille : La grille à afficher.
* affiche en fonction de N et TAILLE la grille mise en form avec les constante d'affichage
*/
void afficherGrille(tGrille grille){
    int ligne,colonne,boucle,boucle2,boucleEspace;
    //affichage des numéros des colonnes
    printf("\n");
    for(boucle = 0; boucle < TAILLE;boucle++){
        if(boucle == 0){
            for(boucleEspace = 0; boucleEspace < INDENTATION ; boucleEspace++){
                printf("%c",ESPACEMENT);
            }
        }
        else if(boucle % N == 0){
            printf("%c",ESPACEMENT);
            printf("%c",ESPACEMENT);
        }
        printf("%c",ESPACEMENT);
        //affichage du numeros
        printf("%d",boucle+1);
    }

    for(ligne=0;ligne<TAILLE;ligne++){
        //traits horizontaux
        if(ligne %N == 0){
            //indentation
            printf("\n");
            for(boucle = 0; boucle < INDENTATION-1 ; boucle++){
                printf("%c",ESPACEMENT);
            }
            //linge horizontal
            printf("%c",CROISEMENT);
            for(boucle2 = 0; boucle2 < N ; boucle2++){
                for(boucle = 0; boucle < ((N*2)+1) ; boucle++){
                    printf("%c",HORIZONTAL);
                }
                printf("%c",CROISEMENT);
            }
        }
        //affichage du numéros de ligne
        printf("\n%d%c%c%c",ligne+1,ESPACEMENT,ESPACEMENT,ESPACEMENT);
        //affichage des ligne
        for (colonne = 0; colonne < TAILLE; colonne++){
            if (colonne %N == 0)
            {
                //affichage des traits verticaux toutes les 3 valeurs
                printf("%c%c",VERTICAL,ESPACEMENT);
            }
            //affichage d'une valeur vide
            if(grille[ligne][colonne]==0){
                printf("%c%c",VIDE,ESPACEMENT);
            }
            //sinon affichage de la valeur
            else{
                printf("%d%c",grille[ligne][colonne],ESPACEMENT);
            }
        }
        //affichage du trait vertical de fin de ligne
        printf("%c",VERTICAL);
    }
    //dernier trait horizontal
    printf("\n");
    for(boucle = 0; boucle < INDENTATION-1 ; boucle++){
        printf("%c",ESPACEMENT);
    }
    //linge horizontal
    printf("%c",CROISEMENT);
    for(boucle2 = 0; boucle2 < N ; boucle2++){
        for(boucle = 0; boucle < ((N*2)+1) ; boucle++){
            printf("%c",HORIZONTAL);
        }
        printf("%c",CROISEMENT);
    }
    printf("\n");
}

/**
* @fn void saisir(int *val_inser)
* @brief recupere une valeur donner par l'utilisateur.
* @param val_inser : valeur qui contient la saisie de l'utilisateur.
* recupere une valeure entre 1 et 9 donner par 'utilisateur, si la valeur n'est pas correct alors une autre demande est faite.
*/
void saisir(int *val_inser){
    int val_valable;
    char ch[49];
    val_valable = 1;//la valeur n'est pour l'instant ni saisie ni valable
    while(val_valable==1){
        scanf("%s", ch);
        if (sscanf(ch, "%d", val_inser) !=0){
            // la conversion a reussi, val_inser contient la
            // valeur entiere lue au clavier
            if ((*val_inser > 10) || (*val_inser < 0)){
                printf("entrez une valeur entre 1 et %d compris \n",TAILLE);
            }
            else{
                val_valable = 0;// la valeur est valable
            }
        } 
        else {
            //la conversion en entier a echoue
            printf("entrez un nombre entier \n");
        }
    }
}
/**
* @fn void chargerGrille(tGrille grille,int *erreurFichier)
* @brief Charge une grille depuis un fichier existant.
* @param grille : La grille de jeu.
* @param erreurFichier : entier de 1 ou 0 qui sert a signal.
* charge la grille d'apres le fichier choisie par l'utilisateur, si le fichier est inexistant il stop le programme en affichant une erreur
*/
void chargerGrille(tGrille grille,int *erreurFichier){
    char nomFichier[30];
    FILE * f;
    //recuperation du nom du fichier
    printf("Nom du fichier ? \n");
    scanf("%s", nomFichier);
    //verification de l'existance du fichier et ouvertur si possible
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\nERREUR sur le fichier %s\n", nomFichier);
        *erreurFichier = 1;
    } else {
        fread(grille, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}


/**
* @fn int possible(tGrille grille, int ligne, int colonne, int valeur)
* @brief Vérifie si une valeur peut être placée a l'emplacement de la grille.
* 
* @param grille La grille de jeu.
* @param ligne La ligne de la case choisie.
* @param colonne La colonne de la case choisie.
* @param valeur La valeur à inserer dans la grille.
* @return 1 si la valeur ne peut pas être placée, 0 sinon.
* vérifie si dans la colonne et la ligne, et la sous case n'on pas de doublons de la valeur qui veut etre inserer
*/
int possible(tGrille grille, int ligne, int colonne, int valeur){
    int boucle,boucleLigne, boucleColonne, possible,ligneCase,colonneCase;
    ligneCase = ligne;
    colonneCase = colonne;
    possible = 0; //0 veut dire qu'on par du principe que c'est possible
    //verification de doublons dans la ligne et ou dans la colonne
    for (boucle = 0 ; boucle < TAILLE ; boucle++){
        if((grille[boucle][colonne]==valeur)||(grille[ligne][boucle]==valeur)){
            possible = 1; //1 c'est donc impossible
        }
    }
    //vérification de doublons dans la case la case
    //placement de ligneCase et colonneCase dans le coin superieur gauche de leurs case
    while(ligneCase % N != 0){
        ligneCase = ligneCase - 1;
    }
    while(colonneCase % N != 0){
        colonneCase = colonneCase - 1;
    }
    //parcours de la sous-case
    for (boucleLigne = ligneCase ; boucleLigne < (ligneCase+N) ; boucleLigne++){
        for (boucleColonne = colonneCase ; boucleColonne < (colonneCase + N) ; boucleColonne++){
            if(grille[boucleLigne][boucleColonne]==valeur){//si la valeur est déja dans le sous carré alors c'est impossible
                possible = 1; //1 c'est donc impossible
            }
        }
    }

    if(possible == 1){
        printf("ERREUR, impossible de jouer ce coup car la valeur fait doublon");
    }
    return possible;
}


/**
* @fn int victoire(tGrille grille)
* @brief Vérifie si la partie est gagnée.
* 
* @param grille La grille de jeu.
* @return 1 si la partie est gagnée, 0 sinon.
* calcul la somme de tous le tableau et verifie si il a atteint le palier de VICTOIRE
*/
int victoire(tGrille grille){
    int total,victoire,i,j;
    total = 0;
    //parcours tous le tableau
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++) 
        {
            total = total + grille[i][j]; //ajoute toute les valeur du tableau a total
        }
        
    }
    //si le total n'atteint pas le seuil de victoire alors le jeu continu sinon le jeu s'arrete
    if (total < VICTOIRE){ 
        victoire = 0;
    }
    else{
        victoire = 1;
        printf("Grille pleine, fin de partie\n");
    }
    return victoire;
}

//===========================================================================
//------------------------------main-----------------------------------------
//===========================================================================


/**
* @fn int main()
* @brief Fonction principale du programme.
* 
* @return 0 en cas de succès.
* programme principal basé sur l'ouverture du fichier contenant la grille puis d'une boucle qui fait des tour de jeu temps que ce n'est pas gagner
*/
int main(){
    tGrille grille;
    int numLigne, numColonne, valeur,erreurFichier;
    erreurFichier = 0;
    chargerGrille(grille,&erreurFichier);//charge la grille et renvoie une erreur si echec
    if(erreurFichier == 0){//si la grille est charger, alors lancer la boucle de jeu
        while (victoire(grille)==0)//tant que la partie n'est pas gagner alors continuer de jouer
        {
            afficherGrille(grille);
            //recuperation des numeros de la case cible
            printf("Indices de la case ? ligne puis colonne \n");
            saisir(&numLigne);
            saisir(&numColonne);
            //passage des numeros de la case en indice (utilisable dans les tableau en C)
            numLigne = numLigne - 1; 
            numColonne = numColonne - 1;
            if (grille[numLigne][numColonne]!=0)//si la case n'est pas vide alors un message d'erreur empeche de modifier la case
            {
                printf("IMPOSSIBLE, la case n'est pas libre.\n");
            }
            else{
                //recuperation de la valeur
                printf("valeur a inserer?\n");
                saisir(&valeur);
                if (possible(grille, numLigne, numColonne, valeur)==0 ){//si les regles du sudoku n'empeche pas de placer la valeur alors : placer la valeur
                    grille[numLigne][numColonne] = valeur;
                }
            }
        }
    }
}