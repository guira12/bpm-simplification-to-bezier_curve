#include<stdio.h>
#include<stdlib.h>
#include"contour.h"

/*ce programme prend en argument une image bmp et un nom de fichier de sortie
il calcule tout les contours de l'image bmp et les ecrit dans le fichier suivant un format precis*/ 
int main(int argc, char **argv){
  Image I;
  Robot r;
  Point pi;
  Contour C;

  //lecture fichier image et stockage dans la structure uinformatique I
  I=lire_fichier_image(argv[1]);
  // calcul contours et ecriture dans le fichier sortie
  calcul_contours(I, &r,argv[2]);
  //affiche le nombre de contours, le total des points et le total des segments
  info_contours(argv[2]);
  return 0;
}