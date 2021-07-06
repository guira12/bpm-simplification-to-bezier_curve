#include<stdio.h>
#include<stdlib.h>
#include "geom2D.h"

/*programme qui ne prend rien en argument,et qui demande à l'utilisateur de saisir les cordonée de chaque point (P,A et B)
la saisie des cordonné pour chaque point ce fait selon le format suivant:
x y entrer
x et y sont des double */
int main(int argc, char **argv){
  double xA, yA, xB, yB, xP, yP, dP;
  Point A, B, P;
  // entree par l'utilisateur ____________________________________________
  //cordonnees du point P
  printf("entrer les cordonnee du point P:\n");
  scanf("%lf", &xP);
  scanf("%lf", &yP);
  
  //cordonnees du point A
  printf("entrer les cordonnee du point A:\n");
  scanf("%lf", &xA);
  scanf("%lf", &yA);
  
  //cordonnees du point B
  printf("entrer les cordonnee du point B:\n");
  scanf("%lf", &xB);
  scanf("%lf", &yB);
  
  //initialisation des points______________________________________________
  P=set_point(xP, yP);
  A=set_point(xA, yA);
  B=set_point(xB, yB);
  
  //calcul distance______________________________________________
  dP=distance_point_segment(P, A, B);
  
  //affichage de la distance à l'ecran________________________
  fprintf(stdout,"--->la distance entre P et [AB] est: %lf\n", dP);
  
  
  return 0;
}