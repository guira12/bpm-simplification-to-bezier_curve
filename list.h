/****************************************************************************** 
  Interface du module list
******************************************************************************/

#ifndef _list_H_
#define _list_H_
#include "geom2D.h"


/*******le type cellule de liste de point****************/
typedef struct Cellule_Liste_Point_{
  Point data;  // donnée de l'element de la liste
  struct Cellule_Liste_Point_ *suiv;   // pointeur sur l'elemnt suivant
}Cellule_Liste_Point;



/*******Le type liste de point ***************************/
typedef struct Liste_Point_{
  unsigned int taille;    //nombre d'elemnt dans la liste
  Cellule_Liste_Point *first;  //pointeur sur le premier element de la liste 
  Cellule_Liste_Point *last;  // pointeur sur le dernier element de la liste
                        //firt=last=NULL et taille =0   <=> liste vide
}Liste_Point;
typedef Liste_Point Contour;  // type Contour = type Liste_Point
 

/*******************Le type tableau de points**************/
typedef struct Tableau_Point_{
  unsigned int taille; //nombre d'éléments dans le tableau 
  Point *tab;           
}Tableau_Point;



/*Creer une cellule de liste avec l'element v renvoie le pointeur 
sur la cellule de liste cree la fct s'arrete si la creation n'a pas pu se faire*/
Cellule_Liste_Point *creer_element_liste_Point(Point v);


/*creer une liste vide*/
Liste_Point creer_liste_Point_vide();

/*ajouter l'element e en fin de la liste L, renvoie la liste L modifiée */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/*supression de tous les elements de la liste, renvoie la liste L vide*/
Liste_Point supprimer_liste_Point(Liste_Point L);

/*concatène L2 a la suite de L1, renvoie la liste L1 modifiée*/
Liste_Point concatener_liste_Point(Liste_Point L1,Liste_Point L2);


/*creer une sequence de points sous forme d'un tableau de points
 a partir de la liste de points L*/
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

//affichage Liste_Point à l'ecran, si vide affichage message liste vide
void affichage_Liste_Point(Liste_Point L);






#endif /* _list_H_ */
