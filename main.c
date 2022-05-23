#include <time.h>
#ifdef _WIN64
#include <windows.h>
#endif

#include "jeu.c"

int main(){
    time_t t;
    
    int joueur = 1, nb_joueurs, joueur_h;
    char coup;
    struct pos *pos;

    srand((unsigned) time(&t));

    nb_joueurs = menu();
    joueur_h = joueur_humain();    

    if (nb_joueurs != 0){
        printf("Pour jouer, il suffit de taper le numero de la colonne ou vous voulez jouer.\n");
        printf("Ou bien D, G ou R pour effectuer des rotations.\n");
        printf("Appuyez sur Q durant la partie pour y mettre fin.\n");
        printf("Bon match !\n\n");
        #ifdef _WIN64
        Sleep(1000);
        #else
        sleep(1000);
        #endif
    }
    if (nb_joueurs == 0){
        printf("Super ! Nous allons assister a un combat entre machines !!");
        #ifdef _WIN64
        Sleep(500);
        #else
        sleep(500);
        #endif
    }

    init_grille();
    affiche_grille();

    while(1){
        switch(nb_joueurs){
            case 0:
                if (verif_grille() == 0 && grille_complete() == 0){
                    IA_joue(joueur);
                    printf("\nL'IA %d a choisi !\n", joueur);
                    affiche_grille();
                    joueur = (joueur == 1) ? 2 : 1;
                    #ifdef _WIN64
                    Sleep(500);
                    #else
                    sleep(500);
                    #endif
                }
                if  (verif_grille() != 0) {printf("\nL'IA %d remporte le DUEL !!", verif_grille()); return 0;}
                if (!verif_grille() && grille_complete()) {printf("\nAucun vainqueur entre ces deux machines..."); return 0;}
                break;
            default:
                if (joueur_h == joueur){
                    printf("A vous de jouer, joueur %d : ", joueur);
                    scanf("%s", &coup);
                    if ((int)(coup) == 68 || (int)(coup) == 100) rotat_D();
                    else if ((int)(coup) == 71 || (int)(coup) == 103) rotat_G();
                    else if ((int)(coup) == 82 || (int)(coup) == 114) retourne_plateau();
                    else if ((int)(coup) == 81 || (int)(coup) == 113) {
                        printf("Le joueur %d a mis fin a la partie.", joueur);
                        return 0;}
                    else if (coup_valide((int)(coup)-48) && !(grille_complete())){
                        pos = calcul_pos((int)(coup)-48, pos);
                        grille[pos->col][pos->lig] = (joueur == 1) ? J1 : J2;}
                    else printf("Erreur.");
                    joueur = (joueur == 1) ? 2 : 1;}
                if (nb_joueurs == 1 && joueur_h != joueur){
                    printf("\n\n");
                    #ifdef _WIN64
                    Sleep(500);
                    #else
                    sleep(500);
                    #endif
                    if (!verif_grille() && !grille_complete()){
                        IA_joue(joueur);
                        if (verif_grille() == 2) {affiche_grille(); printf("Battu par un ordi ? MOUAHAHA"); return 0;}
                        else {printf("L'IA a fait son choix. A vous !"); joueur = (joueur == 1) ? 2 : 1;}
                    }
                }
                affiche_grille();
                break;
        }

        if(grille_complete() && !(verif_grille()) && nb_joueurs > 0){
            printf("Match nul, suoer nul meme...");
            return 0;}

        if(verif_grille() == 1 && nb_joueurs != 0) {printf("Le joueur 1 a gagne !"); return 0;}
        if(verif_grille() == 2 && nb_joueurs == 2) {printf("Le joueur 2 a gagne !"); return 0;}
    }
}