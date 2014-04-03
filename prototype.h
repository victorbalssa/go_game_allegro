#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/* main.c */
void initialisation(int *g, int n, int t[5]);

void sauvgarder(FILE *sauve, FILE *stat, int *g, int n, int t[5]);

void chargement(FILE *sauve, FILE *stat, int *g, int n, int t[5]);

int chargement2(FILE *stat, int t[5]);

/* regles.c */
int pierrebcap();

int pierrencap();

void init_pierrecap();

void trad(int *g, int h);

void retrad(int *g, int h);

void ping(int i, int j, int couleur, int h);

void compt_lib(int m, int n, int couleur, int h);

void eval(int couleur, int h);

void capture(int couleur, int h);

int exam(int couleur, int h);

void ping2(int i, int j, int couleur, int h);

void compt_lib2(int m, int n, int couleur, int h);

void eval2(int couleur, int h);

int suicide(int x, int *t, int couleur, int h);

int stat_pierre(int t[5], int h);

int stat_pierre2(int t[5]);

void sauve_stats(int t[5], int h);

void charge_stats(int t[5]);

/* joueurs.c */
int jeu_b(int h, int *t, ALLEGRO_BITMAP *passer2, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font);

int jeu_n(int h, int *t, ALLEGRO_BITMAP *passer1, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font);

/* ia.c */
int ia(int *t, int couleur, int h);

void init_ia();

/* graphisme.c */
int option_1(ALLEGRO_BITMAP *option1, ALLEGRO_BITMAP *quitter, ALLEGRO_DISPLAY *display);

int option_2(ALLEGRO_BITMAP *option2, ALLEGRO_DISPLAY *display);

int option_3(ALLEGRO_BITMAP *option3, ALLEGRO_DISPLAY *display);

int option_4(ALLEGRO_BITMAP *option4, ALLEGRO_DISPLAY *display);

void affiche_victoire(ALLEGRO_BITMAP *quitter, ALLEGRO_BITMAP *egalite, ALLEGRO_BITMAP *win_n, ALLEGRO_BITMAP *win_b, int p, int n, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font);

int affichage_regle(ALLEGRO_BITMAP *tib[4], int i, int x, int y);

int echap(int x, int y);

int passe_n(int x, int y);

int passe_b(int x, int y);

int cases9(int x, int y);

int cases13(int x, int y);

int cases19(int x, int y);

void affichage_jeux(int h, int *g, ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *goban, ALLEGRO_BITMAP *pierre_b,
                    ALLEGRO_BITMAP *pierre_n, ALLEGRO_BITMAP *quitter,
                    ALLEGRO_BITMAP *goban_13, ALLEGRO_BITMAP *goban_19, ALLEGRO_BITMAP *pierre_b_13,
                    ALLEGRO_BITMAP *pierre_n_13, ALLEGRO_BITMAP *pierre_b_19, ALLEGRO_BITMAP *pierre_n_19,
                    ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font);


