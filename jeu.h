typedef struct pos pos;
struct pos { 
    int col;
    int lig;
};

void affiche_grille();
pos* calcul_pos(int coup, struct pos *position);
void init_grille();
int verif_grille();
int grille_complete();
int coup_valide();
void rotat_D();
void rotat_G();
void retourne_plateau();
void tombe();
int random_co();
int random_action();
int action();
int IA_joue();
int joueur_humain();
int menu(void);
int main();