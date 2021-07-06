#include<stdio.h>
#include<stdlib.h>
#include "contour.h"


int main(int argc, char **argv){
  Image I;
  Robot r;
  Point pi;
  Contour C;

  //lecture fichier image et stockage dans la structure uinformatique I
  I=lire_fichier_image(argv[1]);
  //recherche du point de depart
  pi=point_depart(I);
  //initialisation robot et affichage contour
  C=calcul_contour(I, &r, pi);
  //ecriture contoure à l'écran
  printf("C : ");
  ecrire_contour_ecran(C);
  
  supprimer_liste_Point(C);
  return 0;
}