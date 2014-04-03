/*

    ___      ___      _       _
  / __ \   / __ \   /\ \    /\ \
 /\ \_\ \ /\ \_\ \  \ \ \   \ \ \
 \ \____ \\ \____/   \ \ \   \ \ \
  \/____\ \\/___/     \ \_\   \ \_\
    /\____/            \/\_\   \/\_\
    \_/__/              \/_/    \/_/

*/
/****************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define VIDE 0 //definie un enplacement du goban vide.
#define BLANC 1//definie une pierre Blanche.
#define NOIRE 2//definie une pierre Noire.

#include "../prototype.h"

/****************/

void initialisation(int *g, int n, int t[5]) {/* On initialise le tableau d'affichage, les pierres captur�es, et le tableau
    de stat (pts, taille du goban) */
    int i;
    for (i = 0; i < n; i++) {
        g[i] = VIDE;
    }
    init_pierrecap();
    for (i = 0; i < 5; i++) {
        t[i] = 0;
    }
}

void sauvgarder(FILE *sauve, FILE *stat, int *g, int h, int t[5]) {/* On sauvegarde le goban et les statistiques (pts, taille du goban) de la partie
    dans 2 fichiers (sauve et stat) */
    int i;
    sauve = fopen("sauvegarde.txt", "w");
    stat = fopen("stat.txt", "w");
    sauve_stats(t, h);
    for (i = 0; i < (h * h); i++) {
        fprintf(sauve, "%i ", g[i]);
    }
    for (i = 0; i < 5; i++) {
        fprintf(stat, "%i ", t[i]);
    }
    fclose(sauve);
    fclose(stat);
}

void chargement(FILE *sauve, FILE *stat, int *g, int n,
                int t[5]) {/* On charge le goban et les stats pour rejouer une ancienne partie (a partir des memes fichiers .txt) */
    int i;
    sauve = fopen("sauvegarde.txt", "r");
    stat = fopen("stat.txt", "r");
    for (i = 0; i < n; i++) {
        fscanf(sauve, "%i", &g[i]);
    }
    for (i = 0; i < 5; i++) {
        fscanf(stat, "%i", &t[i]);
    }
    charge_stats(t);
    fclose(sauve);
    fclose(stat);
}

int chargement_taille(FILE *stat,
                      int t[5]) {/* On charge juste la taille du goban et on l'envoi au main pour allou� la m�moire qu'il faut pour rejou� la partie sauvegard� */
    int i;
    stat = fopen("stat.txt", "r");
    for (i = 0; i < 5; i++) {
        fscanf(stat, "%i", &t[i]);
    }
    fclose(stat);
    return (t[2]);
}

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_FONT *font = NULL;

int main() {
    char buf[80];//buffer pour sprite menu
    int *g;// tableau d'affichage (goban)
    int t[5];// tableau des stat (pts, taille du goban)
    ALLEGRO_BITMAP *MenuGO, *goban, *fond, *pierre_b, *pierre_n, *quitter,
            *option1, *option2, *option3, *option4, *pierre_b_13, *pierre_n_13, *pierre_b_19, *pierre_n_19,
            *goban_13, *goban_19, *passer1, *passer2, *win_n, *win_b;// toutes les images du programme
    ALLEGRO_BITMAP *ANIM[9], *page;// image pour effet du menu
    ALLEGRO_BITMAP *tib[4];// regles du jeu
    FILE *sauve, *stat;// ficher sauvegarde
    int choix, i, n, l, h = 0;// variables pour les differents choix de l'utilisateur
    int imcourante = 0;// variable pour effet du menu
    int jeu1, jeu2, r;// variables pour les differents choix de l'utilisateur
    l = NOIRE;// initialisation de la couleur jou� en premier contre l'IA

    al_init();//Initialisation obligatoire d'allegro.
    al_install_keyboard();//Initialisation du clavier.
    al_install_mouse();//Instalation de la souris.
    display = al_create_display(1200, 750);//On ouvre une fenetre graphique de 1200 par 750.
    al_show_mouse_cursor(display); //affiche la souris
    al_set_window_title(display, "Le Jeu de GO !");
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    font = al_load_font("font/blackWolf.ttf", 20, 0);

    // on initialise toutes les variables images
    passer1 = al_load_bitmap("bmp/passen.bmp");
    passer2 = al_load_bitmap("bmp/passeb.bmp");
    goban_13 = al_load_bitmap("bmp/Goban_13x13.bmp");
    goban_19 = al_load_bitmap("bmp/Goban_19x19.bmp");
    option1 = al_load_bitmap("bmp/option1.bmp");
    option2 = al_load_bitmap("bmp/option2.bmp");
    option3 = al_load_bitmap("bmp/echap.bmp");
    option4 = al_load_bitmap("bmp/option4.bmp");
    pierre_b_13 = al_load_bitmap("bmp/pierre_b_13.bmp");
    pierre_n_13 = al_load_bitmap("bmp/pierre_n_13.bmp");
    pierre_b_19 = al_load_bitmap("bmp/pierre_b_19.bmp");
    pierre_n_19 = al_load_bitmap("bmp/pierre_n_19.bmp");
    quitter = al_load_bitmap("bmp/quitter.bmp");
    pierre_n = al_load_bitmap("bmp/Pierrenoire.bmp");
    pierre_b = al_load_bitmap("bmp/Pierreblanche.bmp");
    MenuGO = al_load_bitmap("bmp/MenuGO.bmp");
    fond = al_load_bitmap("bmp/fond.bmp");
    goban = al_load_bitmap("bmp/goban_9x9.bmp");
    tib[0] = al_load_bitmap("bmp/commentjouer.bmp");
    tib[1] = al_load_bitmap("bmp/commentjouer2.bmp");
    tib[2] = al_load_bitmap("bmp/commentjouer3.bmp");
    tib[3] = al_load_bitmap("bmp/commentjouer4.bmp");
    win_n = al_load_bitmap("bmp/win_n.bmp");
    win_b = al_load_bitmap("bmp/win_b.bmp");

    // creation de sprites pour amelioration visuelle du menu
    for (i = 0; i < 9; i++) {
        sprintf(buf, "bmp/menu%d.bmp", i + 1);
        ANIM[i] = al_load_bitmap(buf);
    }
    page = al_create_bitmap(1200, 700);

    do {
        imcourante = (imcourante + 1) % 9;
        al_set_target_bitmap(page);
        al_draw_bitmap(ANIM[imcourante], 0, 0, 0);
        al_set_target_backbuffer(display);
        al_draw_bitmap(page, 0, 0, 0);
        al_flip_display();
    } while (imcourante != 8);

    do {
        choix = 0;//On fait une boucle qui attend que l'utilisateau ai clique sur un choix.
        ALLEGRO_MOUSE_STATE state;
        al_draw_bitmap(MenuGO, 0, 0, 0);//on montre l'image du menu a l'ecran
        al_draw_bitmap(quitter, 950, 0, 0);
        al_flip_display();
        do {
            al_get_mouse_state(&state);
            if (state.buttons == 1) {//Si le clique souris est d�tect�. on affecte le choix suivant ou il a cliqu�.
                if (state.x > 388 && state.x < 813 && state.y > 298 && state.y < 383)
                    choix = 1;
                if (state.x > 396 && state.x < 807 && state.y > 163 && state.y < 251)
                    choix = 2;
                if (state.x > 379 && state.x < 822 && state.y > 581 && state.y < 666)
                    choix = 4;
                if (state.x > 452 && state.x < 748 && state.y > 438 && state.y < 522)
                    choix = 3;
                if (state.x > 950 && state.x < 1150 && state.y > 0 && state.y < 120)
                    choix = 9;
            }
        } while (choix == 0);
        switch (choix) {
            case 1:  //choix jeux 2 joueurs
                jeu1 = -1, jeu2 = -1, r = -1;
                r = option_2(option2, display);
                if (r == 1) { break; }
                if (r == 2) {
                    h = chargement_taille(stat, t);
                    n = h * h;
                    g = malloc(n * sizeof(int));
                    initialisation(g, n, t);
                    chargement(sauve, stat, g, n, t);
                }
                if (r == 3) {
                    h = option_1(option1, quitter, display);
                    if (h == 1) { break; }
                    n = h * h;
                    g = malloc(n * sizeof(int));
                    initialisation(g, n, t);
                }
                affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                               pierre_n_13, pierre_b_19, pierre_n_19, display, font);
                do {
                    al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                    jeu1 = jeu_n(h, g, passer1, display, font);
                    trad(g, h);
                    capture(BLANC, h);
                    retrad(g, h);
                    affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                   pierre_n_13, pierre_b_19, pierre_n_19, display, font);
                    al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                    jeu2 = jeu_b(h, g, passer2, display, font);
                    trad(g, h);
                    capture(NOIRE, h);
                    retrad(g, h);
                    affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                   pierre_n_13, pierre_b_19, pierre_n_19, display, font);
                } while (jeu1 != 0 && jeu2 != 0 && (jeu1 != 2 || jeu2 != 2));
                if (jeu1 == 2 && jeu2 == 2) {
                    affiche_victoire(quitter, fond, win_n, win_b, exam(NOIRE, h), exam(BLANC, h), display, font);
                }
                r = -1;
                if (jeu1 == 0 || jeu2 == 0) {
                    r = option_3(option3, display);
                    if (r == 2) { sauvgarder(sauve, stat, g, h, t); }
                    initialisation(g, n, t);
                }
                break;


            case 2:  //choix humain vs ia
                jeu1 = -1, jeu2 = -1, r = -1;
                r = option_2(option2, display);
                if (r == 1) { break; }
                if (r == 2) {
                    h = chargement_taille(stat, t);
                    n = h * h;
                    g = malloc(n * sizeof(int));
                    initialisation(g, n, t);
                    init_ia();
                    chargement(sauve, stat, g, n, t);
                }
                if (r == 3) {
                    h = option_1(option1, quitter, display);
                    if (h == 1) { break; }
                    n = h * h;
                    g = malloc(n * sizeof(int));
                    initialisation(g, n, t);
                    init_ia();
                }
                affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                               pierre_n_13, pierre_b_19, pierre_n_19, display, font);
                do {
                    if (l == NOIRE) {
                        al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                        jeu1 = jeu_n(h, g, passer1, display, font);
                        trad(g, h);
                        capture(BLANC, h);
                        retrad(g, h);
                        affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                       pierre_n_13, pierre_b_19, pierre_n_19, display, font);

                        al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                        jeu2 = ia(g, BLANC, h);
                        trad(g, h);
                        capture(NOIRE, h);
                        retrad(g, h);
                    }
                    if (l == BLANC) {
                        al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                        jeu1 = ia(g, NOIRE, h);
                        trad(g, h);
                        capture(BLANC, h);
                        retrad(g, h);
                        affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                       pierre_n_13, pierre_b_19, pierre_n_19, display, font);

                        al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                        jeu2 = jeu_b(h, g, passer2, display, font);
                        trad(g, h);
                        capture(NOIRE, h);
                        retrad(g, h);
                    }
                    affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                   pierre_n_13, pierre_b_19, pierre_n_19, display, font);
                } while (jeu1 != 0 && jeu2 != 0 && ((jeu1 != 2 || jeu2 != 400) && (jeu1 != 400 || jeu2 != 2)));
                if ((jeu1 == 2 && jeu2 == 400) || (jeu1 == 400 && jeu2 == 2)) {
                    affiche_victoire(quitter, fond, win_n, win_b, exam(NOIRE, h), exam(BLANC, h), display, font);
                }
                r = -1;
                if (jeu1 == 0) {
                    r = option_3(option3, display);
                    if (r == 2) { sauvgarder(sauve, stat, g, h, t); }
                    initialisation(g, n, t);
                }
                break;


            case 3:  // choix option ia vs ia et choix quelle pierre jouer
                jeu1 = -1, jeu2 = -1, r = -1;
                r = option_4(option4, display);
                if (r == 4) {
                    h = 19;
                    n = h * h;
                    g = malloc(n * sizeof(int));
                    initialisation(g, n, t);
                    init_ia();
                    affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                   pierre_n_13, pierre_b_19, pierre_n_19, display, font);
                    do {
                        al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                        jeu1 = ia(g, NOIRE, h);
                        trad(g, h);
                        capture(BLANC, h);
                        retrad(g, h);
                        affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                       pierre_n_13, pierre_b_19, pierre_n_19, display, font);

                        al_draw_bitmap(fond, 0, 0, 0);//On colle notre fond a l'ecran.
                        jeu2 = ia(g, BLANC, h);
                        trad(g, h);
                        capture(NOIRE, h);
                        retrad(g, h);
                        affichage_jeux(h, g, fond, goban, pierre_b, pierre_n, quitter, goban_13, goban_19, pierre_b_13,
                                       pierre_n_13, pierre_b_19, pierre_n_19, display, font);
                    } while (jeu1 != 400 || jeu2 != 400);
                    affiche_victoire(quitter, fond, win_n, win_b, exam(NOIRE, h), exam(BLANC, h), display, font);
                    break;
                }
                if (r == 1) { break; }
                if (r == 2) {
                    l = NOIRE;
                    break;
                }//on choisi les noirs
                if (r == 3) {
                    l = BLANC;
                    break;
                }//on choisi les blancs

            case 4:  //choix comment jouer ?
                al_draw_bitmap(tib[0], 0, 0, 0);//On affiche la page 1 des r�gles du jeu de go.
                al_flip_display();
                r = 0;//incr�mantation de z (z �tant le num�ro de la page des r�gles)
                ALLEGRO_MOUSE_STATE state;
                do {
                    al_get_mouse_state(&state);
                    r = affichage_regle(tib, r, state.x, state.y);//On affiche la page z des r�gles du jeu de go.
                } while (r != -1);
                break;
        }
    } while (choix != 9);

    al_destroy_bitmap(MenuGO);
    al_destroy_bitmap(passer1);
    al_destroy_bitmap(passer2);
    al_destroy_bitmap(goban_13);
    al_destroy_bitmap(goban_19);
    al_destroy_bitmap(option1);
    al_destroy_bitmap(option2);
    al_destroy_bitmap(option3);
    al_destroy_bitmap(pierre_b_13);
    al_destroy_bitmap(pierre_n_13);
    al_destroy_bitmap(pierre_b_19);
    al_destroy_bitmap(pierre_n_19);
    al_destroy_bitmap(quitter);
    al_destroy_bitmap(pierre_n);
    al_destroy_bitmap(pierre_b);
    al_destroy_bitmap(fond);
    al_destroy_bitmap(goban);
    al_destroy_bitmap(tib[0]);
    al_destroy_bitmap(tib[1]);
    al_destroy_bitmap(tib[2]);
    al_destroy_bitmap(tib[3]);


    return 0;
}
