#include<stdlib.h>
#include<stdio.h>
#include "simplification.h"

int main(int argc, char **argv){
  Contour Ca=creer_liste_Point_vide();  // creer contour vide
  Point P;
  Bezier2 B; // bezier aproximente
  Tableau_Point C;
  
  //ajout premier point au contour
  P.x=1;
  P.y=2;
  Ca=ajouter_element_liste_Point(Ca, P);
  
  //ajout deuxieme point au contour
  P.x=1;
  P.y=3;
  Ca=ajouter_element_liste_Point(Ca, P);
  
  //affichage des points du contour à simplifier
  printf("liste points du contour a simplifier:\n");
  affichage_Liste_Point(Ca);
  
  C=sequence_points_liste_vers_tableau(Ca); //transformation en contour version tabulée
  B=approx_bezier2(C, 0, 1);   //appreximation courbe de bezier2
  
  // affichage des points de controles
  printf("les points de controle de bezier 2 sont:\n");
  printf("C0 = ( %lf , %lf )\n", B.C0.x, B.C0.y);
  printf("C1 = ( %lf , %lf )\n", B.C1.x, B.C1.y);
  printf("C2 = ( %lf , %lf )\n", B.C2.x, B.C2.y);
  
  
  supprimer_liste_Point(Ca);
  return 0;
}