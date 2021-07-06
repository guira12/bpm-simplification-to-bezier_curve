/****************************************************************************** 
  Interface du module image
******************************************************************************/

#ifndef _geometrie2D_H_
#define _geometrie2D_H_
#include<math.h>


/*
    type point et vecteur
*/

typedef struct Point_{
  double x;   //  abscice
  double y;   //  ordonne
}Point;
typedef Point Vecteur;  // type Point = type Vecteur

/*
types courbe de bézier
*/

//structure representant une courbe de bezier de degre 2 identifié avec les trois points de controle
typedef struct Bezier2_{
  Point C0;
  Point C1;
  Point C2;
}Bezier2;

//structure representant une courbe de bezier de degre 3 identifié avec les quattre points de controle
typedef struct Bezier3_{
  Point C0;
  Point C1;
  Point C2;
  Point C3;
}Bezier3;

/**************************************************************
    operation point
****************************************************************/

/* renvoie le point de coordonne (x,y)*/
Point set_point(double x, double y);

/*somme de deux point, resultat (x1+x2,y1+y2)*/
Point add_point(Point P1,Point P2);

/*negatif d'un point càd si on a en entree le point p(x,y) en sortie on aura p'(-x,-y),
 p' est aussi l'image par symetrie central par rapport à l'origine*/
Point minus_point(Point p);

/*distance entre deux points*/
double dist(Point p1, Point p2);



/****************************************************************
    operation vecteur
*****************************************************************/

/*prend en entree deux points P1 P2  et donne en sortie le vecteur allant du point P1 vers le point P2 */
Vecteur vect_bipoint(Point p1, Point p2);

/*somme de deux vecteurs*/
Vecteur add_vecteur(Vecteur v1, Vecteur v2);

/*sustraction de vecteur, resultat v1-v2*/
Vecteur sub_vecteur(Vecteur v1, Vecteur v2);

/*multiplication d'un vecteur par un scalaire*/
Vecteur scalar_vecteur(double a, Vecteur v);

/*produit scalaire entre deux vecteurs*/
double  prod_vecteur(Vecteur v1, Vecteur v2);

/*norme d'un vecteur*/
double norm(Vecteur v);

/*fct qui calcul la distance entre le point P et le segment [AB],
et renvoie la cette distance*/
double distance_point_segment(Point P, Point A, Point B);

/****************************************************************
    Bezier
*****************************************************************/

/*
fct qui prend en argument une courbe de bezier 2 et un parametre t 
et calcul le point de la courbe C(t) et le renvoie*/
Point bezier2(Bezier2 B, double t);

/*fct qui prend on argument un point P, une courbe de bezier B, et un parametre ti,
calcul et renvoie la distance entre le point P et le point de la courbe B ayant comme paramètre ti*/
double distance_point_bezier2(Point P, Bezier2 B, double t);

/*
fct prend en argument une courbe de bezier de degré 2, 
et renvoie la meme courbe eleve au degré 3*/
Bezier3 elevation_degre(Bezier2 B2);

/*
fct qui prend en argument une courbe de bezier 3 et un parametre t 
et calcul le point de la courbe C(t) et le renvoie*/
Point bezier3(Bezier3 B, double t);

/*fct qui prend on argument un point P, une courbe de bezier 3 B, et un parametre t,
calcul et renvoie la distance entre le point P et le point de la courbe B ayant comme paramètre t*/
double distance_point_bezier3(Point P, Bezier3 B, double t);

#endif /* _geometrie2D_H_ */