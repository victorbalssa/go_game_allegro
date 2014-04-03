#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "../prototype.h"

#define VIDE 0 //definie un enplacement du goban vide.
#define BLANC 1//definie une pierre Blanche.
#define NOIRE 2//definie une pierre Noire.


int option_1(ALLEGRO_BITMAP *option1,
             ALLEGRO_BITMAP *quitter,
             ALLEGRO_DISPLAY *display) {/* menu d'option permettant de choisir le goban 9*9/13*13/19*19 */
    int x = 0;
    al_draw_bitmap(option1, 0, 0, 0);
    al_draw_bitmap(quitter, 980, 0, 0);
    al_flip_display();
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (state.buttons & 1 && state.x > 154 && state.x < 262 && state.y > 231 && state.y < 295)
            x = 9;// 9*9
        if (state.buttons & 1 && state.x > 135 && state.x < 282 && state.y > 327 && state.y < 391)
            x = 13;// 13*13
        if (state.buttons & 1 && state.x > 136 && state.x < 283 && state.y > 424 && state.y < 493)
            x = 19;// 19*19
        if (state.buttons & 1 && state.x > 980 && state.x < 1094 && state.y > 0 && state.y < 114)
            x = 1;// quitter
    } while (x == 0);
    return x;
}

int option_2(
        ALLEGRO_BITMAP *option2,
        ALLEGRO_DISPLAY *display) {/* menu d'option permettant de choisir une nouvelle partie ou d'en charger une sauvegard� */
    int x = 0;
    al_draw_bitmap(option2, 0, 0, 0);
    al_flip_display();
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (state.buttons & 1 && state.x > 841 && state.x < 1107 && state.y > 268 && state.y < 355)
            x = 2;// continuer
        if (state.buttons & 1 && state.x > 867 && state.x < 1086 && state.y > 420 && state.y < 546)
            x = 3;// new partie
        if (state.buttons & 1 && state.x > 888 && state.x < 1056 && state.y > 121 && state.y < 202)
            x = 1;// quitter
    } while (x == 0);
    return x;
}

int option_3(ALLEGRO_BITMAP *option3,
             ALLEGRO_DISPLAY *display) {/* menu d'echap permettant de sauvegarder la partie ou de quitter sans sauvegarder */
    int x = 0;
    al_draw_bitmap(option3, 0, 0, 0);
    al_flip_display();
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (state.buttons & 1 && state.x > 54 && state.x < 358 && state.y > 138 && state.y < 274)
            x = 2;//sauvegarder
        if (state.buttons & 1 && state.x > 51 && state.x < 365 && state.y > 367 && state.y < 510)
            x = 1;// quitter sans sauvegarder
    } while (x == 0);
    return x;
}

int option_4(ALLEGRO_BITMAP *option4,
             ALLEGRO_DISPLAY *display) {/* menu d'option permettant le choix de la couleur jou� contre l'IA et l'affichage d'une partie IA vs IA en 19*19 */
    int x = 0;
    al_draw_bitmap(option4, 0, 0, 0);
    al_flip_display();
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (state.buttons & 1 && state.x > 93 && state.x < 202 && state.y > 291 && state.y < 400)
            x = 2;//couleur NOIRE
        if (state.buttons & 1 && state.x > 365 && state.x < 480 && state.y > 291 && state.y < 400)
            x = 3;//couleur BLANCHE
        if (state.buttons & 1 && state.x > 745 && state.x < 952 && state.y > 240 && state.y < 337)
            x = 4;//ia vs ia
        if (state.buttons & 1 && state.x > 980 && state.x < 1094 && state.y > 0 && state.y < 114)
            x = 1;//quitter
    } while (x == 0);
    return x;
}

void
affiche_victoire(ALLEGRO_BITMAP *quitter, ALLEGRO_BITMAP *egalite, ALLEGRO_BITMAP *win_n, ALLEGRO_BITMAP *win_b, int p,
                 int n, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) {/* Fonction qui affiche le gagnant et les pts des joueurs   */
    int x = 0;
    if (n > p) {
        al_draw_bitmap(win_n, 0, 0, 0);//On affiche le gagnant.
        al_draw_textf(font, al_map_rgb(255, 255, 255), 600, 350, -1, "Points noir: %i points blanc: %i", n, p);
    }
    if (p > n) {
        al_draw_bitmap(win_b, 0, 0, 0);//On affiche le gagnant.
        al_draw_textf(font, al_map_rgb(255, 255, 255), 525, 350, -1, "Points blanc: %i points noir: %i", p, n);
    }
    if (p == n) {
        al_draw_bitmap(egalite, 0, 0, 0);//On affiche le gagnant.
        al_draw_textf(font, al_map_rgb(255, 255, 255), 500, 300, -1, "EGALITE !!");
        al_draw_textf(font, al_map_rgb(255, 255, 255), 525, 350, -1, "avec %i pour les blancs et %i pour les noires", p, n);
    }
    al_draw_bitmap(quitter, 980, 114, 0);
    al_flip_display();
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (state.buttons & 1 && state.x > 980 && state.x < 1100 && state.y > 120 && state.y < 300) {
            x = 1;// on attend que l'utilisateur clique sur quitter
        }
    } while (x == 0);
}

int affichage_regle(ALLEGRO_BITMAP *tib[4], int i, int x, int y) {/* Fonction d'affichage des notions et r�gles du jeu */
    int l = 0;
    al_draw_bitmap(tib[i], 0, 0, 0);//On affiche les r�gles du jeu de go.
    al_flip_display();
    x = i;
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (state.buttons & 1 && state.x > 212 && state.x < 982 && state.y > 622 && state.y < 662 && i != 3 &&
            state.x != x &&
            state.y != y)
            x++;// page du bas
        if (state.buttons & 1 && state.x > 210 && state.x < 981 && state.y > 85 && state.y < 127 && i != 0 &&
            state.x != x &&
            state.y != y)
            x--;// page du haut
        if (state.buttons & 1 && state.x > 454 && state.x < 723 && state.y > 585 && state.y < 678 && i == 3 &&
            state.x != x &&
            state.y != y)
            l = -1;
    } while (x == i && l == 0);
    if (l == 0) {
        i = x;
        return i;
    }
    if (l != 0) {
        return l;
    }
}

int echap(int x, int y) {/* Retourne la valeur 0 si l'utilisateur a cliqu� sur le bouton quitter */
    int r = 1;
    //x et y sont les coordonn�es de la souris lors du clic.
    if (x > 980 && x < 1094 && y > 0 && y < 114)//r=0 lorsque l'on clique sur ces coordonn�es
        r = 0;
    return (r);
}

int passe_n(int x, int y) {/* Retourne la valeur 0 si le joueur noir a cliqu� sur le bouton passer */
    int r = 1;
    if (x > 360 && x < 560 && y > 577 && y < 663)//r=0 lorsque l'on clique sur ces coordonn�es
        r = 0;
    return (r);
}

int passe_b(int x, int y) {/* Retourne la valeur 0 si le joueur blanc a cliqu� sur le bouton passer */
    int r = 1;
    if (x > 560 && x < 760 && y > 577 && y < 663)//r=0 lorsque l'on clique sur ces coordonn�es
        r = 0;
    return (r);
}

int cases9(int x,
           int y) {/* Retourne la valeur de la case dans laquelle l'utilisateur a cliqu�. Les paramettres d'entr�e sont les coordonn�es de la souris */
    int i, j, x1, x0, y0, y1, a = 0;
    x0 = 335;// 385 et 80 sont les coordonn�es de la premi�re case.
    y0 = 80;
    for (i = 0; i <
                9; i++) {// y0  et y1 repr�sentent les extr�mit�s verticale d'une case. A chaque boucle, on incr�mente de la taille d'une case soit 50, pour descendre � la ligne en dessous.
        y1 = y0 + 50;
        for (j = 1; j <
                    10; j++) {// x0 et x1 sont les extr�mit�s horizontale d'une case. A chaque boucle, on incr�mente de la taille d'une case pour d�caler d'une case � droite.
            x1 = j * 50 + 335;
            if (x > x0 && x < x1 && y > y0 &&
                y < y1) {// On regarde si le clic se trouve dans l'intervalle de la case point�e.
                a = i * 9 +
                    j;//Si c'est le cas, le nombre prend la valeur de 9 fois le num�ro de ligne plus le num�ro de colonne.
            }
            x0 = x1;// pour se d�caler d'une case, la valeur de l'extr�mit� � gauche prend celle de l'extr�mit� qui �tait � droite.
        }
        x0 = 335;//On revient � la position de d�part pour recommencer une ligne.
        y0 = y1;// pour se d�caler d'une case, la valeur de l'extr�mit� du bas prend celle de l'extr�mit� qui �tait en haut.
    }
    return (a);
}

int cases13(int x,
            int y) {/* Retourne la valeur de la case dans laquelle l'utilisateur a cliqu�. Les paramettres d'entr�e sont les coordonn�es de la souris */
    int i, j, x1, x0, y0, y1, a = 0;
    x0 = 335;// 335 et 80 sont les coordonn�es de la premi�re case.
    y0 = 80;
    for (i = 0; i <
                13; i++) {// y0  et y1 repr�sentent les extr�mit�s verticale d'une case. A chaque boucle, on incr�mente de la taille d'une case soit 35, pour descendre � la ligne en dessous.
        y1 = y0 + 35;
        for (j = 1; j <
                    14; j++) {// x0 et x1 sont les extr�mit�s horizontale d'une case. A chaque boucle, on incr�mente de la taille d'une case pour d�caler d'une case � droite.
            x1 = j * 35 + 335;
            if (x > x0 && x < x1 && y > y0 &&
                y < y1) {// On regarde si le clic se trouve dans l'intervalle de la case point�e.
                a = i * 13 +
                    j;//Si c'est le cas, le nombre prend la valeur de 13 fois le num�ro de ligne plus le num�ro de colonne.
            }
            x0 = x1;// pour se d�caler d'une case, la valeur de l'extr�mit� � gauche prend celle de l'extr�mit� qui �tait � droite.
        }
        x0 = 335;//On revient � la position de d�part pour recommencer une ligne.
        y0 = y1;// pour se d�caler d'une case, la valeur de l'extr�mit� du bas prend celle de l'extr�mit� qui �tait en haut.
    }
    return (a);
}

int cases19(int x,
            int y) {/* Retourne la valeur de la case dans laquelle l'utilisateur a cliqu�. Les paramettres d'entr�e sont les coordonn�es de la souris */
    int i, j, x1, x0, y0, y1, a = 0;
    x0 = 335;// 335 et 80 sont les coordonn�es de la premi�re case.
    y0 = 80;
    for (i = 0; i <
                19; i++) {// y0  et y1 repr�sentent les extr�mit�s verticale d'une case. A chaque boucle, on incr�mente de la taille d'une case soit 24, pour descendre � la ligne en dessous.
        y1 = y0 + 24;
        for (j = 1; j <
                    20; j++) {// x0 et x1 sont les extr�mit�s horizontale d'une case. A chaque boucle, on incr�mente de la taille d'une case pour d�caler d'une case � droite.
            x1 = j * 24 + 335;
            if (x > x0 && x < x1 && y > y0 &&
                y < y1) {// On regarde si le clic se trouve dans l'intervalle de la case point�e.
                a = (i * 19) +
                    j;//Si c'est le cas, le nombre prend la valeur de 7 fois le num�ro de ligne plus le num�ro de colonne.
            }
            x0 = x1;// pour se d�caler d'une case, la valeur de l'extr�mit� � gauche prend celle de l'extr�mit� qui �tait � droite.
        }
        x0 = 335;//On revient � la position de d�part pour recommencer une ligne.
        y0 = y1;// pour se d�caler d'une case, la valeur de l'extr�mit� du bas prend celle de l'extr�mit� qui �tait en haut.
    }
    return (a);
}

void affichage_jeux(int h, int *g, ALLEGRO_BITMAP *fond, ALLEGRO_BITMAP *goban, ALLEGRO_BITMAP *pierre_b,
                    ALLEGRO_BITMAP *pierre_n, ALLEGRO_BITMAP *quitter,
                    ALLEGRO_BITMAP *goban_13, ALLEGRO_BITMAP *goban_19, ALLEGRO_BITMAP *pierre_b_13,
                    ALLEGRO_BITMAP *pierre_n_13, ALLEGRO_BITMAP *pierre_b_19,
                    ALLEGRO_BITMAP *pierre_n_19,
                    ALLEGRO_DISPLAY *display,
                    ALLEGRO_FONT *font) {/* Cette fonction sert � afficher le plateau au cours du jeu */
    int x, y, i, j;
    y = 80;//La premi�re ligne du tableau est � 80 pixels � partir du haut de l'�cran.
    x = 0;
    al_draw_bitmap(quitter, 980, 0, 0);
    if (h == 9) {
        al_draw_bitmap(goban, 335, 80, 0);
        for (i = 0; i < 81; i = i + 9) {// Nous traversons les 9 lignes du plateau sur ses 9 colonnes.
            for (j = 0; j < 9; j++) {
                x = j * 50 + 335;//Nous avons ici la position de la colonne de la "j i�me" case de la ligne.
                if (g[i + j] == NOIRE)
                    al_draw_bitmap(pierre_n, x, y, 0);
                if (g[i + j] == BLANC)
                    al_draw_bitmap(pierre_b, x, y, 0);

            }
            y = y + 50;//On descend d'une ligne en incr�mentent d'une case.
        }
    }
    if (h == 13) {
        al_draw_bitmap(goban_13, 335, 80, 0);
        for (i = 0; i < 169; i = i + 13) {// Nous traversons les 13 lignes du plateau sur ses 13 colonnes.
            for (j = 0; j < 13; j++) {
                x = j * 35 + 335;//Nous avons ici la position de la colonne de la "j i�me" case de la ligne.
                if (g[i + j] == NOIRE)
                    al_draw_bitmap(pierre_n_13, x, y, 0);
                if (g[i + j] == BLANC)
                    al_draw_bitmap(pierre_b_13, x, y, 0);

            }
            y = y + 35;//On descend d'une ligne en incr�mentent d'une case.
        }
    }
    if (h == 19) {
        al_draw_bitmap(goban_19, 335, 80, 0);
        for (i = 0; i < 361; i = i + 19) {// Nous traversons les 19 lignes du plateau sur ses 19 colonnes.
            for (j = 0; j < 19; j++) {
                x = j * 24 + 340;//Nous avons ici la position de la colonne de la "j ieme" case de la ligne.
                if (g[i + j] == NOIRE)
                    al_draw_bitmap(pierre_n_19, x, y + 5, 0);
                if (g[i + j] == BLANC)
                    al_draw_bitmap(pierre_b_19, x, y + 5, 0);

            }
            y = y + 24;//On descend d'une ligne en incr�mentent d'une case.

        }
    }
    al_draw_textf(font, al_map_rgb(255, 255, 255), 130, 200, -1, "Blanc(s) capture(s): %i", pierrebcap());
    al_draw_textf(font, al_map_rgb(255, 255, 255), 930, 200, -1, "Noir(s) capture(s): %i", pierrencap());
    al_draw_textf(font, al_map_rgb(255, 255, 255), 930, 225, -1, "Point(s) Blancs: %i", exam(NOIRE, h));
    al_draw_textf(font, al_map_rgb(255, 255, 255), 130, 225, -1, "Point(s) Noirs: %i", exam(BLANC, h));
    al_flip_display();
}



