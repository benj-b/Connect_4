#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "jeu.h"

#define J1 ('X')
#define J2 ('O')

#define NB_li (7)
#define NB_co (7)

char grille[NB_co][NB_li];
int nb_joueurs;

void affiche_grille(){
    int co;
    int li;

    printf("\n+");

    for (co = 1; co <= NB_co; co++){
        printf("---+");
    }
    printf("\n");
    for (li = 0; li < NB_li; li++){
        printf("|");
        for (co = 0; co < NB_co; co++){
            if (isalpha(grille[co][li])) printf(" %c |", grille[co][li]);
            else printf(" %c |", ' ');
        }
        printf("\n+");
        for (co = 1; co <= NB_co; co++){
            printf("---+");
        }
        printf("\n");
    }
    for (co = 1; co <= NB_co; co++){
        printf("  %d ", co);
    }
    printf("\n");
}

pos *calcul_pos(int coup, struct pos *position){
    /* on rentre la colonne et on cherche sur quelle ligne on peut placer */
    int j;
    position->col = coup - 1;
    for (j = NB_li - 1 ; j >= 0; j--){
        if (grille[position->col][j] == ' '){
            position->lig = j;
            break;
        }
    }
    return position;
}

void init_grille(){
    /* on initialise la grille avec ' ' sur toutes les cases */
    int i;
    int j;
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            grille[i][j] = ' ';
        }
    }
}

int verif_grille(){
    /* on verifie si on a un gagnant */
    int i;
    int j;
    int j_win = 0;
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            if (grille[i][j] == grille[i][j+1] && grille[i][j] == grille[i][j+2] && grille[i][j] == grille[i][j+3] && j+3 < NB_li){
                if (grille[i][j] == J1) j_win = 1;
                if (grille[i][j] == J2) j_win = 2;
            }

            if (grille[i][j] == grille[i+1][j] && grille[i][j] == grille[i+2][j] && grille[i][j] == grille[i+3][j] && i+3 < NB_co){
                if (grille[i][j] == J1) j_win = 1;
                if (grille[i][j] == J2) j_win = 2;
            }

            if (grille[i][j] == grille[i+1][j+1] && grille[i][j] == grille[i+2][j+2] && grille[i][j] == grille[i+3][j+3] && i+3 < NB_co && j+3 < NB_li){
                if (grille[i][j] == J1) j_win = 1;
                if (grille[i][j] == J2) j_win = 2;
            }

            if (grille[i][j] == grille[i+1][j-1] && grille[i][j] == grille[i+2][j-2] && grille[i][j] == grille[i+3][j-3] && i+3 < NB_co && j-3 >= 0){
                if (grille[i][j] == J1) j_win = 1;
                if (grille[i][j] == J2) j_win = 2;
            }
        }
    }
    return j_win;
}

int grille_complete(){
    /* on verifie si la grille est complete */
    int i;
    int j;
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            if (grille[i][j] == ' ') return 0;
        }
    }
    return 1;
}

int coup_valide(int coup){
    /* on verifie si le coup est valide = si la colonne et valide et qu'elle n'est pas pleine */
    return (coup <= NB_co && coup > 0 && grille[coup-1][0] == ' ' ) ? 1 : 0;
}

void rotat_D(){ 
    /* on tourne le plateau sur la droite */
    int i;
    int j;
    char ngrille[NB_co][NB_li];
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            ngrille[i][j] = grille[j][NB_li-1-i];
        }
    }
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            grille[i][j] = ngrille[i][j];
        }
    }
    tombe();
}

void rotat_G(){
    /* idem mais sur la gauche */
    int i;
    int j;
    char ngrille[NB_co][NB_li];
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            ngrille[i][j] = grille[NB_co-1-j][i];
        }
    }
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            grille[i][j] = ngrille[i][j];
        }
    }
    tombe();
}

void retourne_plateau(){
    /* on retourne le plateau */
    int i;
    int j;
    char ngrille[NB_co][NB_li];
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            ngrille[i][j] = grille[i][NB_li-1-j];
        }
    }
    for (i = 0; i < NB_co; i++){
        for (j = 0; j < NB_li; j++){
            grille[i][j] = ngrille[i][j];
        }
    }
    tombe();
}

void tombe(){ 
    /* on applique la gravité lorsque l'on va tourner le plateau */
    int i;
    int j;
    int k;
    for (j = NB_li - 2; j >= 0; j--){
        for (i = 0; i < NB_co; i++){
            if (grille[i][j] != ' ' && grille[i][j+1] == ' '){
                k = j + 1;
                while (grille[i][k] == ' ' && k < NB_li){
                    grille[i][k] = grille[i][k-1];
                    grille[i][k-1] = ' ';
                    k++;
                }
            }
        }
    }
}

int random_co(){
    return (rand() / ((double)RAND_MAX + 1.) * (NB_co + 1));
    /* renvoie un nombre entre 0 et NB_co */
}

int random_action(){
    return (rand() / ((double)RAND_MAX + 1.) * 3);
    /* 
    return 0 = rotat_G
    return 1 = rotat_D
    return 2 = retourne_plateau */
}

int action(){
    int nb = rand() / ((double)RAND_MAX + 1.) * 20;
    if (nb != 1) return 1;
    return 0; 
    /* renvoie 1 si l'ia joue (place un jeton)
        renvoie 0 si l'ia fait une action (default : 1/20) */
}

int IA_joue(int joueur){
    /* fait jouer l'ia */
    int coup;
    int tourne;
    pos *pos;

    if (action()){
        coup = random_co();
        while (!(coup_valide(coup))){
            coup = random_co();
        }
        pos = calcul_pos(coup, pos);
        grille[pos->col][pos->lig] = (joueur == 1) ? J1 : J2;
        return coup;
    }
    else{
        coup = random_action();
        if (coup == 0) {rotat_G(); tourne = 71;}
        else if (coup == 1) {rotat_D(); tourne = 68;}
        else if (coup == 2) {retourne_plateau(); tourne = 82;}
        return tourne;
    }
}

int joueur_humain(){
    /* demande au joueur si il veut etre joueur 1 ou 2 dans le cas ou il est le seul a jouer */
    int joueur_h;

    printf("Voulez vous etre joueur 1 ou 2 ?\n -> ");
    scanf("%d", &joueur_h);
    return joueur_h;
}

int menu(void) {
    /* affiche le menu */
    int nb_joueurs;

    printf("\t MENU\n");
    printf("- 1 - Solo.\n");
    printf("- 2 - Duo.\n");
    printf("- 0 - Ghost.\n");
    printf("\n -> ");
    scanf("%d", &nb_joueurs);

    return nb_joueurs;
}