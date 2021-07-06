/****************************************************************************** 
  Interface du module simplification
******************************************************************************/

#ifndef _simplification_H_
#define _simplification_H_
#include "contour.h"
#include<math.h>

/*fct prend en argument un contour forme tabulée deux indices et une distance seuil d, 
et simplifie la partie du contour entre les deux indices avec une distance seuil d, et renvoie une liste de point simplifiant cette partie du contour*/
Liste_Point simplification_DP(Tableau_Point C, UINT j1, UINT j2, double d);

/*fct qui prendrend en arguments un fichier contours 
simplifie ce fichier (selon une distance seuil d ) et l'ecrit au format eps dans le fichier f_eps donné en argument 
largeur et hauteur sont les dimensions de l'image pbm correspondante a f_contours
et renvoie le nombre de segment total apres simplification*/
int simp_contours_to_EPS(char *f_contours, char *f_eps, double d, UINT largeur, UINT hauteur);

/*procedure qui prend en argument une image pbm et simplifie tous les contours (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps
 et renvoie le nombre de segment total apres simplification*/
int simp_PBM_to_EPS(char *f_pbm, char *f_eps, double d);


/********************************************************************************
simplification par courbe de bezier
*********************************************************************************/

/*fct qui prend en argument un contour format tabulé et deux indices du contour,
calcul une approximation du contour par une courbe de bezier de degre2 entre les deux indice
et renvoie cette courbe de bezier*/
Bezier2 approx_bezier2(Tableau_Point C, UINT j1, UINT j2);

/*fct qui simplifie le contour C format tabulé  de l'indice j1 à l'indice j2 avec une courbe de bezier de degré 2
selon une distance seuil d, 
et renvoie la liste des courbes de béziers apres simplification, 
attention chaque trois points successives du debut de la liste constitue une courbe de bézier*/
Liste_Point simplification_DP_Bezier2(Tableau_Point C, UINT j1, UINT j2, double d);

/*
fct  qui prend une liste de bezier 2 calcul son equivalent en liste de bezier 3 et la renvoie
*/
Liste_Point elevation_degre_liste(Liste_Point LB2);

/*fct qui prend en arguments un fichier contours 
simplifie ce fichier avec des courbes de bezier2 (selon une distance seuil d ) et l'ecrit au format eps dans le fichier f_eps donné en argument 
largeur et hauteur sont les dimensions de l'image pbm correspondante a f_contours
et renvoie le nombre de bezier2 total apres simplification*/
UINT simp_contours_to_EPS_bezier2(char *f_contours, char *f_eps, double d, UINT largeur, UINT hauteur);

/*procedure qui prend en argument une image pbm et simplifie tous les contours avec beziers2 (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps
 et renvoie le nombre de bezier2 total apres simplification*/
UINT simp_PBM_to_EPS_bezier2(char *f_pbm, char *f_eps, double d);

/*fonction Gamma gamma(k,n)=6 k^4 - 8 n k^3 + 6 k^2 - 4*n*k + n^4 - n^2*/
double Gamma(double k, double n);

/*fct qui prend en argument un contour format tabulé et deux indices du contour,
calcul une approximation du contour par une courbe de bezier de degre3 entre les deux indice
et renvoie cette courbe de bezier*/
Bezier3 approx_bezier3(Tableau_Point C, UINT j1, UINT j2);

/*fct qui simplifie le contour C format tabulé  de l'indice j1 à l'indice j2 avec une courbe de bezier de degré 3
selon une distance seuil d, 
et renvoie la liste des courbes de béziers apres simplification, 
attention chaque quatre points successives du debut de la liste constitue une courbe de bézier*/
Liste_Point simplification_DP_Bezier3(Tableau_Point C, UINT j1, UINT j2, double d);

/*fct qui prend en arguments un fichier contours 
simplifie ce fichier avec des courbes de bezier3 (selon une distance seuil d ) et l'ecrit au format eps dans le fichier f_eps donné en argument 
largeur et hauteur sont les dimensions de l'image pbm correspondante a f_contours
et renvoie le nombre de bezier3 total apres simplification*/
UINT simp_contours_to_EPS_bezier3(char *f_contours, char *f_eps, double d, UINT largeur, UINT hauteur);

/*procedure qui prend en argument une image pbm et simplifie tous les contours avec beziers3 (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps
 et renvoie le nombre de bezier3 total apres simplification*/
UINT simp_PBM_to_EPS_bezier3(char *f_pbm, char *f_eps, double d);



#endif