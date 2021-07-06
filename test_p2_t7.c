#include<stdlib.h>
#include<stdio.h>
#include "simplification.h"

/*programme de test de la fct approx_bezier, il ne prend rien en argument, parcontre programme interactif, demande a l'utilisateur le type de test souhaité, et effectue les tests de la tache 7 partie 2 (a,b,c) , les resultats sont affiché à l'ecran*/
int main(int argc, char **argv){
  UINT n=0;
  char c; //test souhaiter
  Contour cnt=creer_liste_Point_vide();
  Tableau_Point C;
  Point Pi;
  Bezier3 B3;
  int test=1;  //boleen test vrai ou faux
  Bezier3 Bs; //bezier de sortie pour test C
  double ti, dst; //ti parametre de bezier; dst distance entre un point et la courbe
  
  /*choix du test*/
  printf("saisir le test souhaite (a,b,c ou d) :\n");
  fscanf(stdin, "%c", &c);
  
  if(c=='a'){
    printf("saisir les deux points:\n");
    for(int i=0; i<2; i++){
      fscanf(stdin, "%lf %lf", &(Pi.x), &(Pi.y));
      cnt=ajouter_element_liste_Point(cnt, Pi);     
    }
    C=sequence_points_liste_vers_tableau(cnt);
    B3=approx_bezier3(C, 0, 1);             // aproximation du contour a deux point par une bezier 3
    //si C0=P0 faire:
    if(B3.C0.x==(C.tab[0]).x  &&  B3.C0.y==C.tab[0].y){ 
      printf("C0=P0\n");
    }
    else{test=0;}
    
    Pi=scalar_vecteur(2, C.tab[0]); //Pi <- 2*P0
    Pi=add_point(Pi, C.tab[1]);
    Pi=scalar_vecteur(1.0/3.0, Pi); // Pi<- (2*P0 + P1)/3
    //si C1=(2*P0 + P1)/3 faire:
    if(B3.C1.x==Pi.x && B3.C1.y==Pi.y){
      printf("C1=(2*P0 + P1)/3\n");
    }
    else{test=0;}
    
    Pi=scalar_vecteur(2, C.tab[1]); //Pi <- 2*P1
    Pi=add_point(Pi, C.tab[0]);
    Pi=scalar_vecteur(1.0/3.0, Pi); // Pi<- (P0 + 2*P1)/3
    //si C2=(P0 + 2*P1)/3 faire:
    if(B3.C2.x==Pi.x && B3.C2.y==Pi.y){
      printf("C2=(P0 + 2*P1)/3\n");
    }
    else{test=0;}
    
    //si C3=P1 faire:
    if(B3.C3.x==(C.tab[1]).x  &&  B3.C3.y==C.tab[1].y){ 
      printf("C3=P1\n");
    }
    else{test=0;}
    
    if(test){
      printf("TEST A: OK\n");
      printf("----------\n");
    }
    else{
      printf("TEST A: FAILED\n");
      printf("--------------\n");
    }    
  }
  
  
  else if(c=='b'){
    printf("saisir les trois points du contour:\n");
    for(int i=0; i<3; i++){
      fscanf(stdin, "%lf %lf", &(Pi.x), &(Pi.y));
      cnt=ajouter_element_liste_Point(cnt, Pi);     
    }
    C=sequence_points_liste_vers_tableau(cnt);
    B3=approx_bezier3(C, 0, 2);             // aproximation du contour a trois points par une bezier 3
    //si C0=P0 faire:
    if(B3.C0.x==(C.tab[0]).x  &&  B3.C0.y==C.tab[0].y){ 
      printf("C0=P0\n");
    }
    else{test=0;}
    
    Pi=scalar_vecteur(4, C.tab[1]); //Pi <- 4*P1
    Pi=sub_vecteur(Pi, C.tab[2]);
    Pi=scalar_vecteur(1.0/3.0, Pi); // Pi<- (4*P1 - P2)/3
    //si C1=(4*P1 - P2)/3 faire:
    if(B3.C1.x==Pi.x && B3.C1.y==Pi.y){
      printf("C1=(4*P1 - P2)/3\n");
    }
    else{test=0;}
    
    Pi=scalar_vecteur(4, C.tab[1]); //Pi <- 4*P1
    Pi=sub_vecteur(Pi, C.tab[0]);
    Pi=scalar_vecteur(1.0/3.0, Pi); // Pi<- (4*P1 - P0)/3
    //si C2=(4*P1 - P0)/3 faire:
    if(B3.C2.x==Pi.x && B3.C2.y==Pi.y){
      printf("C2=(4*P1 - P0)/3\n");
    }
    else{test=0;}
    
    //si C3=P2 faire:
    if(B3.C3.x==(C.tab[2]).x  &&  B3.C3.y==C.tab[2].y){ 
      printf("C3=P2\n");
    }
    else{test=0;}
    
    if(test){
      printf("TEST B: OK\n");
      printf("----------\n");
    }
    else{
      printf("TEST B: FAILED\n");
      printf("--------------\n");
    }    
  }
  
  
  else if(c=='c'){ 
    //initialisation bezier B=( Q0  , Q1 , Q2, Q3 )
    fprintf(stdout,"initialisation points de controle bezier3:\n");
    fprintf(stdout,"entrer le point Q0:\n");
    fscanf(stdin,"%lf %lf", &(B3.C0.x), &(B3.C0.y));
    fprintf(stdout,"entrer le point Q1:\n");
    fscanf(stdin,"%lf %lf", &(B3.C1.x), &(B3.C1.y));
    fprintf(stdout,"entrer le point Q2:\n");
    fscanf(stdin,"%lf %lf", &(B3.C2.x), &(B3.C2.y));
    fprintf(stdout,"entrer le point Q3:\n");
    fscanf(stdin,"%lf %lf", &(B3.C3.x), &(B3.C3.y));
    
    //initialisation de n 
    fprintf(stdout,"entrer n:\n");
    fscanf(stdin, "%u", &n);
  
    // calcul des Pi=C(i/n)
    for(UINT i=0; i<=n; i++){
      ti= ((double)i) / ((double)n);
      Pi=bezier3(B3, ti);                // Pi <- C(i/n)
      cnt=ajouter_element_liste_Point(cnt, Pi);  // ajout de Pi à la liste cnt
    }
      //affichage de cnt liste des Pi sur la courbe de bezier3 ( Q0  , Q1 , Q2, Q3 )
    fprintf(stdout, "la liste des Pi sur la courbe de bezier3 ( Q0  , Q1 , Q2, Q3 ) est la suivante:\n");
    affichage_Liste_Point(cnt);
    
    fprintf(stdout,"*************************************************************\n");
    fprintf(stdout,"* calcul de la Bezier de degre 2 Bs(C0,C1,C2,C3) approchant *\n");
    fprintf(stdout,"* le contour polygonal (P0, P1, . . . , Pn)                 *\n");
    fprintf(stdout,"*************************************************************\n");
    
    //calcul de la Bezier de degre 3 Bs(C0,C1,C2, C3) approchant le contour polygonal (P0, P1, . . . , Pn)
    C=sequence_points_liste_vers_tableau(cnt);      //transformation en contour version tabulée
    Bs=approx_bezier3(C, 0, n);
    
    //tests egalité des deux beziers
    if(B3.C0.x==Bs.C0.x && B3.C0.y==Bs.C0.y){
      fprintf(stdout,"C0=Q0=( %lf , %lf )\n", B3.C0.x, B3.C0.y);
    }
    else{
      fprintf(stdout,"attention    C0!=Q0 :  Q0( %lf , %lf ) et C0( %lf , %lf )\n", B3.C0.x, B3.C0.y, Bs.C0.x, Bs.C0.y);
      test=0;
    }
  
    if(dist(B3.C1, Bs.C1)==0){
      fprintf(stdout,"C1=Q1=( %lf , %lf )\n", B3.C1.x, B3.C1.y);
    }
    else{
      fprintf(stdout,"attention    C1!=Q1 :  Q1( %lf , %lf ) et C1( %lf , %lf )\n", B3.C1.x, B3.C1.y, Bs.C1.x, Bs.C1.y);
      test=0;
    }
    
    if(dist(B3.C2, Bs.C2)==0){                            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      fprintf(stdout,"C2=Q2=( %lf , %lf )\n", B3.C2.x, B3.C2.y);
    }
    else{
      fprintf(stdout,"attention    C2!=Q2 :  Q2( %lf , %lf ) et C2( %lf , %lf )\n", B3.C2.x, B3.C2.y, Bs.C2.x, Bs.C2.y);
      test=0;
    }
    
    if(B3.C3.x==Bs.C3.x && B3.C3.y==Bs.C3.y){              //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      fprintf(stdout,"C3=Q3=( %lf , %lf )\n", B3.C3.x, B3.C3.y);
    }
    else{
      fprintf(stdout,"attention    C3!=Q3 :  Q3( %lf , %lf ) et C3( %lf , %lf )\n", B3.C3.x, B3.C3.y, Bs.C3.x, Bs.C3.y);
      test=0;
    }
    
    //affichage resultat test
    if(test){
      printf("TEST PASSED\n");  
    }
    else{
      printf("TEST FAILED\n");
    }
  }
  else if(c=='d'){  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!a terminer
    //initialisation contour par l'utilisateur et n 
    printf("saisir le nombre de points du contour qui sera simplifie:\n");
    fscanf(stdin,"%u", &n);    //saisi nombre de points 
    n--;                     // decrementation pour avoir le nombre n du poly
    printf("saisir les points du contour:\n");
    for(UINT i=0; i<=n; i++){
      fscanf(stdin,"%lf %lf", &(Pi.x), &(Pi.y));
      cnt=ajouter_element_liste_Point(cnt, Pi);      //ajout de Pi au contour
    }
    
    //transformation contour forme tabulée
    C=sequence_points_liste_vers_tableau(cnt);
    
    fprintf(stdout,"***************************************************************\n");
    fprintf(stdout,"* calcul de Bezier3 B(C0,C1,C2,C3) aproximant le contour saisi*\n");
    fprintf(stdout,"***************************************************************\n");
    
    //calcul B(C0,C1,C2,C3)
    B3=approx_bezier3(C, 0, n);
    printf("C0=( %lf , %lf )\n", B3.C0.x, B3.C0.y);  //affichage point C0
    printf("C1=( %lf , %lf )\n", B3.C1.x, B3.C1.y);  //affichage point C1
    printf("C2=( %lf , %lf )\n", B3.C2.x, B3.C2.y);  //affichage point C2
    printf("C3=( %lf , %lf )\n", B3.C3.x, B3.C3.y);  //affichage point C3
    
    fprintf(stdout,"************************************************************\n");
    fprintf(stdout,"* calcul des distances entre les points saisi et la courbe *\n");
    fprintf(stdout,"************************************************************\n");
    
    
    
    printf("|-----|---------------|\n");
    printf("|  i  |  d(Pi,C(ti))  |\n");
    printf("|-----|---------------|\n");
    for(UINT i=0; i<=n; i++){
      ti= ((double)i) / ((double)n);
      dst=distance_point_bezier3(C.tab[i], B3, ti);  //dist <- d(Pi,C(ti))    
      printf("|  %u  |  %lf     |\n", i, dst);
      printf("|-----|---------------|\n");  
    }
  }
  
  
  supprimer_liste_Point(cnt);
  return 0;
}