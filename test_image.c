#include<stdio.h>
#include<stdlib.h>
#include "image.h"






int main(int argc, char **argv){
  Image I;


  I=lire_fichier_image(argv[1]);
  printf("image %s\n",argv[1]);
  ecrire_image(I);
  
  supprimer_image(&I);
  printf("image vide\n");
  ecrire_image(I);
  
  return 0;
}