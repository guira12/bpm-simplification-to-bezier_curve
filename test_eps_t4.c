#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "contour.h"



int main(int argc, char **argv){
  Image I;
  Robot r;
  Point pi;
  Contour C;
  UINT largeur,hauteur;
  
  
  //lecture fichier image et stockage dans la structure informatique I
  I=lire_fichier_image(argv[1]);
  //recherche du point de depart
  pi=point_depart(I);
  //initialisation robot et memorisation position
  C=calcul_contour(I, &r, pi);
  //largeur et hauteur de l'image
  largeur=largeur_image(I);
  hauteur=hauteur_image(I);
  //ecrire fichier eps pour tracage de l'image selon le mod choisi
  if(!(strcmp(argv[3], "1")))
    ecrire_contour_inEPS_mod1(largeur, hauteur, C, argv[2]);
  else if(!(strcmp(argv[3], "2")))
    ecrire_contour_inEPS_mod2(largeur, hauteur, C, argv[2]);
  else if(!(strcmp(argv[3], "3")))
    ecrire_contour_inEPS_mod3(largeur, hauteur, C, argv[2]);
  else{
    fprintf(stderr,"erreur: mode de tracage eps\n");
    exit(-1);
  }
  return 0;
}