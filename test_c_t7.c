#include<stdio.h>
#include<stdlib.h>
#include "simplification.h"

int main(int argc, char **argv){
  Contour C=creer_liste_Point_vide();  // creer contour vide
  Point Pi;
  Bezier2 B; // bezier aproximente
  UINT n;          //n+1= nombre de point de la partie du contour à simplifier 
  double dist;
  Tableau_Point cnt;  // contour saisi version tabulée
  double ti;  // ti parametre courbe de bezier indicé selon point de la courbe ti=i/n

  
  //initialisation contour par l'utilisateur et n 
  printf("saisir le nombre de points du contour qui sera simplifie:\n");
  fscanf(stdin,"%u", &n);    //saisi nombre de points 
  n--;                     // decrementation pour avoir le nombre n du poly
  printf("saisir les points du contour:\n");
  for(UINT i=0; i<=n; i++){
    fscanf(stdin,"%lf %lf", &(Pi.x), &(Pi.y));
    C=ajouter_element_liste_Point(C, Pi);      //ajout de Pi au contour
  }
  
  //transformation contour forme tabulée
  cnt=sequence_points_liste_vers_tableau(C);
  
  fprintf(stdout,"************************************************************\n");
  fprintf(stdout,"* calcul de Bezier2 B(C0,C1,C2) aproximant le contour saisi*\n");
  fprintf(stdout,"************************************************************\n");
  
  //calcul B(C0,C1,C2)
  B=approx_bezier2(cnt, 0, n);
  printf("C0=( %lf , %lf )\n", B.C0.x, B.C0.y);  //affichage point C0
  printf("C1=( %lf , %lf )\n", B.C1.x, B.C1.y);  //affichage point C1
  printf("C2=( %lf , %lf )\n", B.C2.x, B.C2.y);  //affichage point C2
  
  fprintf(stdout,"************************************************************\n");
  fprintf(stdout,"* calcul des distances entre les points saisi et la courbe *\n");
  fprintf(stdout,"************************************************************\n");
  
  
  
  printf("|-----|---------------|\n");
  printf("|  i  |  d(Pi,C(ti))  |\n");
  printf("|-----|---------------|\n");
  for(UINT i=0; i<=n; i++){
    ti= ((double)i) / ((double)n);
    dist=distance_point_bezier2(cnt.tab[i], B, ti);  //dist <- d(Pi,C(ti))    
    printf("|  %u  |  %lf     |\n", i, dist);
    printf("|-----|---------------|\n");  
  }
  
  
  C=supprimer_liste_Point(C);  //liberation memoire
  return 0;
}