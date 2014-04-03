/*

Fichier comportant des variables statiques pour une optimisation de l'application des r�gles

*/
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define VIDE 0
#define BLANC 1
#define NOIRE 2
#include "../prototype.h"

static int t[19][19];   /* Goban de calcul */
static int l[19][19];   /* tableau des libert�s (0 si pierres sans libert�s) */
static int ml[19][19];  /* tableau d'�tude des pierres (pour savoir si des pierres ont d�j� �t� etudi�) */

static int lib=0;       /* variable de libert�(ou de territoire) temporel */
static int capt_b1, capt_b2;  /* pierre blanche captur�es */
static int capt_n1, capt_n2;  /* pierre noire captur�es */
static int capt_b, capt_n;    /* nb de pierres captur�es par les blancs et par les noires */


void trad(int *g,int h)
{/* fait la traduction entre tableau d'affichage et tableau de calcul */
    int i,j;
    for(i=0;i<h;i++){
        for(j=0;j<h;j++){
            t[i][j]=g[(i*h)+j];
            }
    }
}

void retrad(int *g, int h)
{/* fait la traduction entre tableau tableau de calcul et d'affichage   */
    int i,j;
    for(i=0;i<h;i++){
        for(j=0;j<h;j++){
            g[(i*h)+j]=t[i][j];
            }
    }
}



void ping(int i ,int j ,int couleur,int h)
{/* Incr�mante lib lorsque du VIDE est reper� ou continu � chercher lorsque la COULEUR est d�tect� */

 ml[i][j] = VIDE;

/* check en haut */
 if (i!=0){
    if ((t[i - 1][j] == VIDE) && ml[i - 1][j]){
       lib++;
       ml[i - 1][j] = VIDE;
     }
    else
       if ((t[i - 1][j] == couleur) && ml[i - 1][j])
	  ping(i - 1, j, couleur,h);
  }
/* check en dessous */
 if (i!=(h-1)){
    if ((t[i + 1][j] == VIDE) && ml[i + 1][j]){
       lib++;
       ml[i + 1][j] = VIDE;
     }
    else
       if ((t[i + 1][j] == couleur) && ml[i + 1][j])
	  ping(i + 1, j, couleur,h);
  }
/* check � gauche */
 if (j!=0){
    if ((t[i][j - 1] == VIDE) && ml[i][j - 1]){
       lib++;
       ml[i][j - 1] = VIDE;
     }
    else
       if ((t[i][j - 1] == couleur) && ml[i][j - 1])
	  ping(i, j - 1, couleur,h);
  }
/* check � droite */
 if (j!=(h-1)){
    if ((t[i][j + 1] == VIDE) && ml[i][j + 1]){
       lib++;
       ml[i][j + 1] = VIDE;
     }
    else
       if ((t[i][j + 1] == couleur) && ml[i][j + 1])
	  ping(i, j + 1, couleur,h);
  }
}

void compt_lib(int m, int n, int couleur,int h)
{/* R.A.Z du tableau d'�tude et ping au coordonn�es joint */
    int i, j;
    for (i = 0; i < h; i++)
        for (j = 0; j < h; j++)
            ml[i][j] = 1;
    ping(m, n, couleur,h);
}

void eval(int couleur, int h)
{/* cherche les libert�s de chaque pierre */
  int i, j;
  for (i = 0; i < h; i++)
    for (j = 0; j < h; j++)
      if (t[i][j] == couleur){
        lib = 0;
        compt_lib(i, j, couleur,h);
        l[i][j] = lib;
      }
}

void capture(int couleur, int h)
{/* capture les pierre et compte les pierres captur�s */
   int i, j, n;
/* cherche les libert�s de chaque pierre */
   eval(couleur,h);
/* initialise les pierre captur� */
   if (couleur == BLANC)
     {
      capt_b1 = -1;
      capt_b2 = -1;
    }
   else
     {
      capt_n1 = -1;
      capt_n2 = -1;
    }
   n = 0; /* r�gle du Ko */

/* supprimer toutes les pierres sans libert�s */
   for (i = 0; i < h; i++)
     for (j = 0; j < h; j++)
       if ((t[i][j] == couleur) && (l[i][j] == 0))
	 {
	  t[i][j] = VIDE;
/* enregistre les pierre capt */
	  if (couleur == BLANC)
	    {
	     capt_b1 = i;
	     capt_b2 = j;
	     ++capt_b;
	   }
	  else
	    {
	     capt_n1 = i;
	     capt_n2 = j;
	     ++capt_n;
	   }
	  n++;  /* incr�mente le nb de capture de ce tour (Ko) */
	}
/* remet � -1 si plus d'une pierre captur� quand le Ko �tait possible */
   if (couleur == BLANC && n > 1)
     {
       capt_b1 = -1;
       capt_b2 = -1;
     }
   else if ( n > 1 )
     {
       capt_n1 = -1;
       capt_n2 = -1;
     }
}



void ping2(int i ,int j ,int couleur, int h)
{/* Incr�mante lib lorsque la couleur est reper� ou continu � chercher lorsque il y a du vide */
 ml[i][j] = 1;

/* check en haut */
 if (i!=0){
    if ((t[i - 1][j] == couleur) && ml[i - 1][j]!=1){
       lib++;
       ml[i - 1][j] = 1;
     }
    else
       if ((t[i - 1][j] == VIDE) && ml[i - 1][j]!=1)
	  ping2(i - 1, j, couleur,h);
  }

/* check en dessous */
 if (i!=(h-1)){
    if ((t[i + 1][j] == couleur) && ml[i + 1][j]!=1){
       lib++;
       ml[i + 1][j] = 1;
     }
    else
       if ((t[i + 1][j] == VIDE) && ml[i + 1][j]!=1)
	  ping2(i + 1, j, couleur,h);
  }

/* check � gauche */
 if (j!=0){
    if ((t[i][j - 1] == couleur) && ml[i][j - 1]!=1){
       lib++;
       ml[i][j - 1] = 1;
     }
    else
       if ((t[i][j - 1] == VIDE) && ml[i][j - 1]!=1)
	  ping2(i, j - 1, couleur,h);
  }

/* check � droite */
 if (j!=(h-1)){
    if ((t[i][j + 1] == couleur) && ml[i][j + 1]!=1){
       lib++;
       ml[i][j + 1] = 1;
     }
    else
       if ((t[i][j + 1] == VIDE) && ml[i][j + 1]!=1)
	  ping2(i, j + 1, couleur,h);
  }
}

void compt_lib2(int m, int n, int couleur, int h)
{/* R.A.Z du tableau d'�tude et ping2 au coordonn�es joint */
    int i, j;
    for (i = 0; i < h; i++)
        for (j = 0; j < h; j++)
            ml[i][j] = 0;
    ping2(m, n, couleur,h);
}

void eval2(int couleur, int h)
{/* Pour chaque case vide on ping2 au coordonn�es et entre dans le tableau l:
    0 si territoire adverse ou >0 si territoire contest�  */
  int i, j;
  for(i=0;i<h;i++)
    for(j=0;j<h;j++)
      if(t[i][j]==VIDE){
            lib = 0;
            compt_lib2(i, j, couleur,h);
            l[i][j] = lib;
        }
}

int exam(int couleur, int h)
{/* retourne les points de la couleurs adverse */
    int i, j, n=0;
    eval2(couleur,h);
    for(i=0;i<h;i++){
        for(j=0;j<h;j++){
            if((t[i][j] == VIDE) && (l[i][j] == 0)){/* pour chaque 0 dans le tableau on incr�mante les pts de 1 */
                    n=n+1;
            }
        }
    }
    if(couleur==BLANC){n=n+capt_b;}
    if(couleur==NOIRE){n=n+capt_n+6;}
    return n;
}



int suicide(int x, int *t,int couleur, int h)
{/* R�gle du sucide: retourne 0 si il y a suicide */
    if(t[x-1]==couleur && t[x+1]==couleur && t[x-h]==couleur && t[x+h]==couleur){
        return 0;
    }
    return 1;
}

void sauve_stats(int t[5], int h)
{/* sauvegarde les pierres captur�es dans le tableau des stats */
    t[0]=capt_b;
    t[1]=capt_n;
    t[2]=h;
}

void charge_stats(int t[5])
{/* charge les pierres captur�es du tableau des stats */
    capt_b=t[0];
    capt_n=t[1];
}



int pierrebcap()
{/* retourne les pierres blanches captur�s */
    return capt_b;
}

int pierrencap()
{/* retourne les pierres noires captur�s */
    return capt_n;
}

void init_pierrecap()
{/* initialise les pierres captur�s */
    capt_b=0;capt_n=0;
}


