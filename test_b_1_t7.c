#include<stdlib.h>
#include<stdio.h>
#include "simplification.h"

int main(int argc, char **argv){
  
  Bezier2 B;         // bezier degre 2 utiilisateur
  Bezier2 Bs;        // bezier degre 2 en sortie apres apres aproximation du contour polygonal
  Point Pi;
  UINT n;          //n+1= nombre de point de la partie du contour à simplifier
  double ti;        //parametre 
  Liste_Point L=creer_liste_Point_vide(); //n + 1 points Pi sur la courbe B(Q0,Q1,Q2) 
  int test_reussi=1; // bool =1 si test reussi  sinon =0
  Tableau_Point C;
  
  //initialisation bezier B=( Q0  , Q1 , Q2 )
  fprintf(stdout,"initialisation points de controle bezier2:\n");
  fprintf(stdout,"entrer le point Q0:\n");
  fscanf(stdin,"%lf %lf", &(B.C0.x), &(B.C0.y));
  fprintf(stdout,"entrer le point Q1:\n");
  fscanf(stdin,"%lf %lf", &(B.C1.x), &(B.C1.y));
  fprintf(stdout,"entrer le point Q2:\n");
  fscanf(stdin,"%lf %lf", &(B.C2.x), &(B.C2.y));
  
  //initialisation de n 
  fprintf(stdout,"entrer n:\n");
  fscanf(stdin, "%u", &n);
  
  // calcul des Pi=C(i/n)
  for(UINT i=0; i<=n; i++){
    ti= ((double)i) / ((double)n);
    Pi=bezier2(B, ti);                // Pi <- C(i/n)
    L=ajouter_element_liste_Point(L, Pi);  // ajout de Pi à la liste L
  }
  
  //affichage de L liste des Pi sur la courbe de bezier2 ( Q0  , Q1 , Q2 )
  fprintf(stdout, "la liste des Pi sur la courbe de bezier2 ( Q0  , Q1 , Q2 ) est la suivante:\n");
  affichage_Liste_Point(L);
  
  fprintf(stdout,"*********************************************************\n");
  fprintf(stdout,"* calcul de la Bezier de degre 2 Bs(C0,C1,C2) approchant*\n");
  fprintf(stdout,"* le contour polygonal (P0, P1, . . . , Pn)             *\n");
  fprintf(stdout,"*********************************************************\n");
  
  //calcul de la Bezier de degre 2 Bs(C0,C1,C2) approchant le contour polygonal (P0, P1, . . . , Pn)
  C=sequence_points_liste_vers_tableau(L);      //transformation en contour version tabulée
  Bs=approx_bezier2(C, 0, n);
  
  //tests egalité des deux beziers
  if(B.C0.x==Bs.C0.x && B.C0.y==Bs.C0.y){
    fprintf(stdout,"C0=Q0=( %lf , %lf )\n", B.C0.x, B.C0.y);
  }
  else{
    fprintf(stdout,"attention    C0!=Q0 :  Q0( %lf , %lf ) et C0( %lf , %lf )\n", B.C0.x, B.C0.y, Bs.C0.x, Bs.C0.y);
    test_reussi=0;
  }

  if(B.C1.x==Bs.C1.x && B.C1.y==Bs.C1.y){
    fprintf(stdout,"C1=Q1=( %lf , %lf )\n", B.C1.x, B.C1.y);
  }
  else{
    fprintf(stdout,"attention    C1!=Q1 :  Q1( %lf , %lf ) et C1( %lf , %lf )\n", B.C1.x, B.C1.y, Bs.C1.x, Bs.C1.y);
    test_reussi=0;
  }
  
  if(B.C2.x==Bs.C2.x && B.C2.y==Bs.C2.y){
    fprintf(stdout,"C2=Q2=( %lf , %lf )\n", B.C2.x, B.C2.y);
  }
  else{
    fprintf(stdout,"attention    C2!=Q2 :  Q2( %lf , %lf ) et C2( %lf , %lf )\n", B.C2.x, B.C2.y, Bs.C2.x, Bs.C2.y);
    test_reussi=0;
  }

  //affichage resultat test
  if(test_reussi){
    printf("TEST PASSED\n");  
  }
  else{
    printf("TEST FAILED\n");
  }


  supprimer_liste_Point(L);
  return 0;
}