/****************************************************************************** 
  Interface du module image
******************************************************************************/

#ifndef _contour_H_
#define _contour_H_
#include "geom2D.h"
#include "image.h"
#include "list.h"



/* 
 Type enuméré Orientation
 */
typedef enum {N,S,E,W} Orientation;                //(NORD,SUD,EST,OUEST)


/*
    type Robot
*/

typedef struct robot_{
  Point p;   //  position
  Orientation o;   //  ordonne
}Robot;

// avancer robot d'une case
void avancer(Robot *r);

//robot tourne à gauche
void gauche(Robot *r);

//robot tourne à droite
void droite(Robot *r);

/*cherche le point de départ du robot si point de depart
 non existant la fct sort avec une erreur*/
Point point_depart(Image I);

//procedure qui modifie l'orientation du robot en fonction des pixels devant de facon à avoir toujours le pixel noir à gauche et blanc a droite et 
void nouvelle_orientation(Image I,Robot *r);
 
/*fct recoie une image pbm un robot non initialisé et un point de depart du robot 
et calcul le contour à partir du point de depart donné en argument et renvoie le 
contour sous forme de liste de points*/
Liste_Point calcul_contour(Image I, Robot *r, Point pi);

/*ecrire le contour L a l'ecran 
cette procedure montre un exemple de conversion d'une liste de points en
tableau de points afin de pouvoir par la suite acceder aux element d'une sequence 
de points par indice*/
void ecrire_contour_ecran(Liste_Point L);

//ecrire dans le fichier nom_fich en mode append, le nombre de points, et les cordonnees des points d' un contours
void ecrire_contour_inFile(Liste_Point L, char *nom_fich );

/*procedure prend en argument un contour une largeur une hauteur,
 et cree un fichier eps <nom_fich> avec un bounding box <0 0 largeur hauteur>
  et les instructions de traçage du contour selon le mod1*/
void ecrire_contour_inEPS_mod1(UINT largeur, UINT hauteur, Liste_Point L, char *nom_fich);

/*procedure prend en argument un contour une largeur une hauteur,
 et cree un fichier eps <nom_fich> avec un bounding box <0 0 largeur hauteur>
  et les instructions de traçage du contour selon le mod2*/
void ecrire_contour_inEPS_mod2(UINT largeur, UINT hauteur, Liste_Point L, char *nom_fich);


/*procedure prend en argument un contour une largeur une hauteur,
 et cree un fichier eps <nom_fich> avec un bounding box <0 0 largeur hauteur>
  et les instructions de traçage du contour selon le mod3*/
void ecrire_contour_inEPS_mod3(UINT largeur, UINT hauteur, Liste_Point L, char *nom_fich);

/*fct recoie une image pbm, son masque M, un robot non initialisé et un point de depart du robot 
et calcul le contour à partir du point de depart donné en argument et renvoie le 
contour sous forme de liste de points, tout en mettant en BLANC  le pixel SUD EST par rapport
 à la position du robot dans le masque si le robot est orienté EST */
Liste_Point calcul_C_modif_M(Image I, Image *M, Robot *r, Point pi);

/*procedure qui calcul tous les contours de l'image I et les stock dans le fichier nom_fich,
et ecrit au debut de ce fichier le nombre de contour de l'image I*/
void calcul_contours(Image I, Robot *r,char *nom_fich);

/*procedure qui prend en argument un fichier au format ensemble de contours 
et affiche à l'écran: -le nombre de contours
                      -le nombre totale de points
                      -le nombre total de segments
*/
void info_contours(char *nom_fich);

/*procedure qui cree un fichier EPS de nom (fich_eps) de largeur et hauteur données en arguments
en mod3 remplissage, à partir d'une sequence de contours (fich_contours) */
void contours_to_EPS(UINT largeur, UINT hauteur, char *fich_contours, char *fich_eps);

#endif /* _contour_H_ */