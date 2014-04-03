#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define VIDE 0 //definie un enplacement du goban vide.
#define BLANC 1//definie une pierre Blanche.
#define NOIRE 2//definie une pierre Noire.

#include "../prototype.h"

static int coup_ia = 0;

void init_ia() { coup_ia = 0; }

int ia(int *t, int couleur, int h) {/* Intelligence artificielle */
    int i, x = 0;
    if (h == 19) {// si taille goban= 19*19
        if (coup_ia >= 150) {
            return 400;
        }
        if (coup_ia >= 0 && coup_ia < 5) {
            do {
                do {
                    x = rand() % 300;
                } while (x != 60 && x != 72 && x != 288 && x != 300 && x != 200 && x != 180 && x != 67 && x != 195 &&
                         x != 207);
            } while (t[x] != VIDE);
        }
        if (coup_ia >= 5) {
            if (couleur == BLANC) {
                for (i = 0; i < 361; i++) {//en fonction du coup NOIRE l'ia cherche a entourer les chaines adverse
                    if (t[i] == NOIRE) {
                        if (t[i + 1] == VIDE && suicide(i + 1, t, NOIRE, h) != 0) { x = i + 1; }
                        if (t[i - 1] == VIDE && suicide(i - 1, t, NOIRE, h) != 0) { x = i - 1; }
                        if (t[i + 19] == VIDE && suicide(i + 19, t, NOIRE, h) != 0) { x = i + 19; }
                        if (t[i - 19] == VIDE && suicide(i - 19, t, NOIRE, h) != 0) { x = i - 19; }
                    }
                }
            }
            if (couleur == NOIRE) {
                for (i = 361; i > -1; i--) {//en fonction du coup BLANC l'ia cherche a entourer les chaines adverse
                    if (t[i] == BLANC) {
                        if (t[i + 19] == VIDE && suicide(i + 19, t, BLANC, h) != 0) { x = i + 19; }
                        if (t[i - 19] == VIDE && suicide(i - 19, t, BLANC, h) != 0) { x = i - 19; }
                        if (t[i + 1] == VIDE && suicide(i + 1, t, BLANC, h) != 0) { x = i + 1; }
                        if (t[i - 1] == VIDE && suicide(i - 1, t, BLANC, h) != 0) { x = i - 1; }
                    }
                }
            }
        }
    }
    if (h == 13) {// si taille goban= 13*13
        if (coup_ia >= 80) {
            return 400;
        }
        if (coup_ia >= 0 && coup_ia < 5) {
            do {
                do {
                    x = rand() % 130;
                } while (x != 42 && x != 45 && x != 48 && x != 120 && x != 126 && x != 123 && x != 81 && x != 84 &&
                         x != 78);
            } while (t[x] != VIDE);
        }
        if (coup_ia >= 5) {
            if (couleur == BLANC) {
                for (i = 0; i < 169; i++) {//en fonction du coup NOIRE l'ia cherche a entourer les chaines adverse
                    if (t[i] == NOIRE) {
                        if (t[i + 1] == VIDE && suicide(i + 1, t, NOIRE, h) != 0) { x = i + 1; }
                        if (t[i - 1] == VIDE && suicide(i - 1, t, NOIRE, h) != 0) { x = i - 1; }
                        if (t[i + 13] == VIDE && suicide(i + 13, t, NOIRE, h) != 0) { x = i + 13; }
                        if (t[i - 13] == VIDE && suicide(i - 13, t, NOIRE, h) != 0) { x = i - 13; }
                    }
                }
            }
            if (couleur == NOIRE) {
                for (i = 169; i > -1; i--) {//en fonction du coup BLANC l'ia cherche a entourer les chaines adverse
                    if (t[i] == BLANC) {
                        if (t[i + 13] == VIDE && suicide(i + 13, t, BLANC, h) != 0) { x = i + 13; }
                        if (t[i - 13] == VIDE && suicide(i - 13, t, BLANC, h) != 0) { x = i - 13; }
                        if (t[i + 1] == VIDE && suicide(i + 1, t, BLANC, h) != 0) { x = i + 1; }
                        if (t[i - 1] == VIDE && suicide(i - 1, t, BLANC, h) != 0) { x = i - 1; }
                    }
                }
            }
        }
    }
    if (h == 9) {// si taille goban= 9*9
        if (coup_ia >= 50) {
            return 400;
        }
        if (coup_ia >= 0 && coup_ia < 5) {
            do {
                do {
                    x = rand() % 80;
                } while (x != 20 && x != 24 && x != 48 && x != 56 && x != 60 && x != 38 && x != 40 && x != 42 &&
                         x != 58 && x != 78);
            } while (t[x] != VIDE);
        }
        if (coup_ia >= 5) {
            if (couleur == BLANC) {
                for (i = 0; i < 81; i++) {//en fonction du coup NOIRE l'ia cherche a entourer les chaines adverse
                    if (t[i] == NOIRE) {
                        if (t[i + 1] == VIDE && suicide(i + 1, t, NOIRE, h) != 0) { x = i + 1; }
                        if (t[i - 1] == VIDE && suicide(i - 1, t, NOIRE, h) != 0) { x = i - 1; }
                        if (t[i + 9] == VIDE && suicide(i + 9, t, NOIRE, h) != 0) { x = i + 9; }
                        if (t[i - 9] == VIDE && suicide(i - 9, t, NOIRE, h) != 0) { x = i - 9; }
                    }
                }
            }
            if (couleur == NOIRE) {
                for (i = 81; i > -1; i--) {//en fonction du coup BLANC l'ia cherche a entourer les chaines adverse
                    if (t[i] == BLANC) {
                        if (t[i + 9] == VIDE && suicide(i + 9, t, BLANC, h) != 0) { x = i + 9; }
                        if (t[i - 9] == VIDE && suicide(i - 9, t, BLANC, h) != 0) { x = i - 9; }
                        if (t[i + 1] == VIDE && suicide(i + 1, t, BLANC, h) != 0) { x = i + 1; }
                        if (t[i - 1] == VIDE && suicide(i - 1, t, BLANC, h) != 0) { x = i - 1; }
                    }
                }
            }
        }
    }
    t[x] = couleur;
    coup_ia++;
    return 3;
}

