#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "../prototype.h"

#define VIDE 0 // definie un enplacement du goban vide.
#define BLANC 1 // definie une pierre Blanche.
#define NOIRE 2 // definie une pierre Noire.


int jeu_b(int h, int *t, ALLEGRO_BITMAP *passer2,
          ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) {/* fonction permettant le tour des pierres blanches */

    int a = -1, fin = 1, f = 1;// variable position goban, quitter, passer.
    al_draw_bitmap(passer2, 560, 570, 0);// on affiche le boutton passer
    al_draw_textf(font, al_map_rgb(255, 255, 255), 475, 20, -1, "C'est aux blancs de jouer !");
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (h == 9) {// si goban 9*9
            if (state.buttons & 1 && t[cases9(state.x, state.y) - 1] == VIDE)
                a = cases9(state.x, state.y) - 1;
            if (state.buttons & 1)
                fin = echap(state.x, state.y);
            if (state.buttons & 1)
                f = passe_b(state.x, state.y);
        }
        if (h == 13) {// si goban 13*13
            if (state.buttons & 1 && t[cases13(state.x, state.y) - 1] == VIDE)
                a = cases13(state.x, state.y) - 1;
            if (state.buttons & 1)
                fin = echap(state.x, state.y);
            if (state.buttons & 1)
                f = passe_b(state.x, state.y);
        }
        if (h == 19) {// si goban 19*19
            if (state.buttons & 1 && t[cases19(state.x, state.y) - 1] == VIDE)
                a = cases19(state.x, state.y) - 1;
            if (state.buttons & 1)
                fin = echap(state.x, state.y);
            if (state.buttons & 1)
                f = passe_b(state.x, state.y);
        }
    } while (t[a] != VIDE && fin != 0 && f != 0);
    t[a] = BLANC;// a etant l'endroit ou la sourie a cliquer, on y met une pierre.

    if (f == 0) { fin = 2; }
    if (fin == 0 && a != -1 && f == 0) { t[a] = VIDE; }
    return (fin);
}

int jeu_n(int h, int *t, ALLEGRO_BITMAP *passer1,
          ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) {/* fonction permettant le tour des pierres noires */

    int a = -1, fin = 1, f = 1;// variable position goban, quitter, passer.
    al_draw_bitmap(passer1, 300, 570, 0);// on affiche le boutton passer
    al_draw_textf(font, al_map_rgb(255, 255, 255), 475, 20, -1, "C'est aux noirs de jouer !");
    ALLEGRO_MOUSE_STATE state;
    do {
        al_get_mouse_state(&state);
        if (h == 9) {// si goban 9*9
            if (state.buttons & 1 && t[cases9(state.x, state.y) - 1] == VIDE)
                a = cases9(state.x, state.y) - 1;
            if (state.buttons & 1)
                fin = echap(state.x, state.y);
            if (state.buttons & 1)
                f = passe_n(state.x, state.y);
        }
        if (h == 13) {// si goban 13*13
            if (state.buttons & 1 && t[cases13(state.x, state.y) - 1] == VIDE)
                a = cases13(state.x, state.y) - 1;
            if (state.buttons & 1)
                fin = echap(state.x, state.y);
            if (state.buttons & 1)
                f = passe_n(state.x, state.y);
        }
        if (h == 19) {// si goban 19*19
            if (state.buttons & 1 && t[cases19(state.x, state.y) - 1] == VIDE)
                a = cases19(state.x, state.y) - 1;
            if (state.buttons & 1)
                fin = echap(state.x, state.y);
            if (state.buttons & 1)
                f = passe_n(state.x, state.y);
        }
    } while (t[a] != VIDE && fin != 0 && f != 0);
    t[a] = NOIRE;// a etant l'endroit ou la sourie a cliquer, on y met une pierre.

    if (f == 0) { fin = 2; }

    if (fin == 0 && a != -1) { t[a] = VIDE; }
    return (fin);
}
