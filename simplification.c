#include<stdio.h>
#include<stdlib.h>
#include "simplification.h"



/*fct prend en argument un contour forme tabulée deux indices et une distance seuil d, 
et simplifie la partie du contour entre les deux indices avec une distance seuil d, et renvoie une liste de point simplifiant cette partie du contour*/
Liste_Point simplification_DP(Tableau_Point C, UINT j1, UINT j2, double d){
  double dmax=0;  //distance maximal separent un points du morceau de contour et le segment S=[Pj1 , Pj2]
  UINT k=j1;
  double dj; // distance entre le point Pj et le segment S=[Pj1 , Pj2]
  Point Pj1=C.tab[j1]; // point d'indice j1
  Point Pj2=C.tab[j2]; // point d'indice j2
  Point Pj;         
  Liste_Point L,L1,L2; // listes de segments L etant la liste final, et les autre liste pour technique diviser pour regner
  //initialisation des listes de segments
  L=creer_liste_Point_vide();
  L1=creer_liste_Point_vide();
  L2=creer_liste_Point_vide();
  
  /* (1)_recherche du point Pk le plus eloigné du segment S=[Pj1 , Pj2], ainsi que la distance dmax*/
  for(int j=j1+1; j<=j2; j++){
    Pj=C.tab[j];
    dj=distance_point_segment(Pj, Pj1, Pj2);  // distance entre Pj et le segment S
    if(dmax<dj){
      dmax=dj;
      k=j;
    }
  }
  
  if(dmax<=d){
    /*(2)_ dmax<=d: simplification suivant le segment S*/
    L=ajouter_element_liste_Point(L, Pj1);
    L=ajouter_element_liste_Point(L, Pj2);     //L<-[Pj1,Pj2]
  }
  else{
    /*(3)_diviser pour regner */
    // (3.1.1)_ simplifier la partie du contour cnt commpris entre les indices j1 et k avec la distance-seuil d
    L1=simplification_DP(C, j1, k, d);
    // (3.1.2)_ simplifier la partie du contour cnt commpris entre les indices k et j2 avec la distance-seuil d
    L2=simplification_DP(C, k, j2, d);
    //fusionner les deux séquence L1 et L2
    L=concatener_liste_Point(L1,L2);
  }
  return L; //retourner liste de segment simmplifiée
}



/*fct qui prendrend en arguments un fichier contours 
simplifie ce fichier (selon une distance seuil d ) et l'ecrit au format eps dans le fichier f_eps donné en argument 
largeur et hauteur sont les dimensions de l'image pbm correspondante a f_contours
et renvoie le nombre de segment total apres simplification*/
int simp_contours_to_EPS(char *f_contours, char *f_eps, double d, UINT largeur, UINT hauteur){
  FILE *f_e,*f_c;   // descripteurs de fichiers f_eps et f_contours
  int n,n_p; //n:nombre de contours, n_p=nombre de point pour un contour
  Contour C=creer_liste_Point_vide();  //contour non simplifié
  Tableau_Point cnt;                  //contour non simplifié version tabulée
  Point p;
  Contour C_simp=creer_liste_Point_vide();  //C_simp est un ensemble de segments 
  Cellule_Liste_Point *el;
  double px,py; // cordonnées pour le fichier eps
  int estPremierPoint=1; //boolenn indiquant que le point est le premier d'une liste de points
  int nst=0; //  nombre de segments total apres simplification
  
  // ouverture de f_contours en lecture et de f_eps en ecriture
  f_c=fopen(f_contours,"r");
  if(f_c==(FILE *)NULL){
    fprintf(stderr, "erreur d'ouverture fichier contours en lecture: dans la procedure simp_contours_to_EPS dans le module simplification\n");
    exit(-1);
  }
  f_e=fopen(f_eps,"w");
  if(f_e==(FILE *)NULL){
    fprintf(stderr, "erreur d'ouverture fichier eps en ecriture: dans la procedure simp_contours_to_EPS dans le module simplification\n");
    exit(-1);
  }
  
  //ecriture en-tete et boite englobente
  fprintf(f_e,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f_e,"%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);
  
  // parcours de f_contours et ecriture  contour par contour simplifié dans le fichier f_eps
  fscanf(f_c,"%d",&n);     //extraction nombre contours 
  for(int cc=0; cc<n; cc++){    //parcours des contours, cc est un "contour_counter"
    fscanf(f_c,"%d",&n_p);    //extractions nombre de points pour un contour
    for(int pc=0; pc<n_p; pc++){   // parcours des points d'un contour, pc pour "point_counter"
      /*création de la liste de point C à partir d'un contour de f_contours*/
      fscanf(f_c,"%lf",&(p.x));  // extraction abscice
      fscanf(f_c,"%lf",&(p.y));  // extraction ordonnée
      C=ajouter_element_liste_Point(C, p);
    }
    cnt=sequence_points_liste_vers_tableau(C);//passage d'un contour en forme liste chainnée à la forme tableau de point
    
    /*simplification contour*********************************************/
    C_simp=simplification_DP(cnt, 0, n_p-1, d);   // de l'indice 0 à l'indice (nombre de points -1)
    C=supprimer_liste_Point(C);                // vider C
    /*ecriture du contour simplifié dans le fichier eps******************/
    el=C_simp.first;
    while(el!=NULL){
      // extraction des coordonées et adaptation pour le repere eps
      px=el->data.x;        
      py=hauteur - (el->data.y);
      //ecriture des instruction eps
      if(estPremierPoint==1){                                      //si premier point du contour
        fprintf(f_e,"%f %f moveto\n", px, py);
        el=el->suiv;        //passage à la celule suivante
        estPremierPoint=0;
      }
      else{
        fprintf(f_e,"%f %f lineto\n", px, py);
        nst++;      //incrementation nombre de segments total apres simplification
        /*si ce n'est pas premier point on l'ecrit et on saute un point*/
        el=el->suiv;        //passage à la celule suivante
        if(el!=NULL){  //verification pour eviter de lire un pointeur null et avoir un segmentation fault
          el=el->suiv;
        }
      }
    }  
    C_simp=supprimer_liste_Point(C_simp);    //vider C_simp 
    estPremierPoint=1;    // remise du boleen à vrai apres la fin  d'un contour 
    
  }
  
  //config epaisseur ligne de traçage et couleu
  fprintf(f_e,"0 0 0 setrgbcolor 0 setlinewidth\n");
  //instruction tracé
  fprintf(f_e,"fill\n");
  fprintf(f_e,"showpage\n");
    
  // fermeture des deux fichiers
  fclose(f_e);
  fclose(f_c);
  
  return nst;
}



/*procedure qui prend en argument une image pbm et simplifie tous les contours (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps
 et renvoie le nombre de segment total apres simplification*/
int simp_PBM_to_EPS(char *f_pbm, char *f_eps, double d){
  Image I;
  Robot r;
  UINT largeur,hauteur;
  int nst; // nombre de segments total apres simplification 

  //lecture fichier image et stockage dans la structure uinformatique I
  I=lire_fichier_image(f_pbm);
  
  //initialisation largeur hauteur
  largeur=largeur_image(I);
  hauteur=hauteur_image(I);
  // calcul contours et ecriture dans le fichier tmp
  calcul_contours(I, &r,"tmp_1352300320218_tmp.contours");
  printf("INFO AVANT SIMPLIFICATION:\n");                        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  info_contours("tmp_1352300320218_tmp.contours");
  //simplification et ecriture dans f_eps
  nst=simp_contours_to_EPS("tmp_1352300320218_tmp.contours" , f_eps, d, largeur, hauteur);
  //supression du fichier tmp
  remove("tmp_1352300320218_tmp.contours");
  return nst;
}


/*fct qui prend en argument un contour format tabulé et deux indices du contour,
calcul une approximation du contour par une courbe de bezier de degre2 entre les deux indice
et renvoie cette courbe de bezier*/
Bezier2 approx_bezier2(Tableau_Point C, UINT j1, UINT j2){
  Bezier2 B;    // courbe de bezier definie  par trois points
  UINT n;       // (nombre de point entre l'indice j2 et j1 inclues) - 1
  Point Pj1=C.tab[j1]; // point d'indice j1
  Point Pj2=C.tab[j2]; // point d'indice j2
  double alpha,beta;
  Point SP={0,0}; // somme des points du contour entre l'indice j1 et j2 exclue
  
  B.C0=Pj1;
  B.C2=Pj2;
  n= j2 - j1;
  
  if(n==1){  // si le contour est reduit à deux points, soit un seul segment alors
    B.C1=scalar_vecteur(0.5, add_point(Pj1,Pj2));  // C1 <- 1/2 *(Pj1+Pj2)    
  }
  else{
    alpha= (3*((double)n)) /  (((double)n)*((double)n) -1); // alpha=(3n) / (n^2 -1)
    beta= (1 - 2*((double)n)) /  (2*((double)n +1));        // beta= (1-2n)/(2*(n+1))
    for(UINT i=1; i<= (n-1); i++){
      SP=add_point(SP,C.tab[i+j1]);
    }
    //C1 <- alpha * SP + beta(Pj1+Pj2)
    B.C1= add_point(scalar_vecteur(alpha, SP), scalar_vecteur(beta, add_point(Pj1,Pj2)));
  }
  
  return B;
}



/*fct qui simplifie le contour C format tabulé  de l'indice j1 à l'indice j2 avec une courbe de bezier de degré 2
selon une distance seuil d, 
et renvoie la liste des courbes de béziers apres simplification, 
attention chaque trois points successives du debut de la liste constitue une courbe de bézier*/
Liste_Point simplification_DP_Bezier2(Tableau_Point C, UINT j1, UINT j2, double d){
  
  
  UINT i;
  UINT n=j2-j1;  //nombre de segments de C entre les indices j1 et j2
  double dmax=0; //distance maximal entre les point du contour et la courbe de bézier de simplification
  UINT k=j1; //indice du point du contour le plus éloigné de la courbe
  double ti;  // parametre courbe bezier au pas i du calcul de la distance maximal
  double dj; //distance entre le point Pj et la courbe de bezier2
  Bezier2 B=approx_bezier2(C, j1, j2);    // approximation de la sequence des points entre les indices j1 et j2 par une Bézier de degré 2
  Liste_Point L,L1,L2; // listes courbes de bézier L etant la liste final, et les autre liste pour technique diviser pour regner
                        // ces liste contiennent les points de controle chaque trois points consecutifs constitue une courbe de bezier
  //initialisation des listes de segments
  L=creer_liste_Point_vide();
  L1=creer_liste_Point_vide();
  L2=creer_liste_Point_vide();
  
  
  for(UINT j=j1+1; j<=j2; j++){
    i=j-j1; //steps dans le calcul de la distance maximal
    ti= ((double)i) / ((double)n);
    dj=distance_point_bezier2(C.tab[j], B, ti); // dj <- dist(Pj, C(ti) )
    if(dmax<dj){
      dmax=dj;
      k=j;
    }    
  }
  
  if(dmax<=d){  // si dmax<=d alors faire: L<-{B}
    L=ajouter_element_liste_Point(L, B.C0);
    L=ajouter_element_liste_Point(L, B.C1);
    L=ajouter_element_liste_Point(L, B.C2);
  }
  else{ // sinon decomposer le problème en deux
    // simplifier la partie de C compris entre les indices j1 et k
    L1=simplification_DP_Bezier2(C, j1, k, d);
    // simplifier la partie de CONT compris entre les indices k et j2
    L2=simplification_DP_Bezier2(C, k, j2, d);
    // fusionner les deux s´equences L1 et L2
    L=concatener_liste_Point(L1, L2);
  }
  
  return L; // retourner la liste L contenant les points de controles des courbes de bezier de degré2 
}



/*
fct  qui prend une liste de bezier 2 calcul son equivalent en liste de bezier 3 et la renvoie
*/
Liste_Point elevation_degre_liste(Liste_Point LB2){
  Tableau_Point LB2t=sequence_points_liste_vers_tableau(LB2);  //convertion liste point bezier deux en version tabulée
  Bezier2 B2;
  Bezier3 B3;
  UINT n=LB2t.taille/3; //nombre de bezier2 dans la liste LB2
  Liste_Point LB3=creer_liste_Point_vide(); //liste bezier 3 de sorite
  
  
  for(UINT i=0; i<n; i++){ //parcours de LB2t
    // extraction d'une bezier 2
    B2.C0=LB2t.tab[i*3];
    B2.C1=LB2t.tab[i*3+1];
    B2.C2=LB2t.tab[i*3+2];
    //elevation de degre 2 à 3
    B3=elevation_degre(B2);
    //ajout de B3 à la liste Bezier 3
    LB3=ajouter_element_liste_Point(LB3, B3.C0);
    LB3=ajouter_element_liste_Point(LB3, B3.C1);
    LB3=ajouter_element_liste_Point(LB3, B3.C2);
    LB3=ajouter_element_liste_Point(LB3, B3.C3);
  }
  
  return LB3;
}




/*fct qui prend en arguments un fichier contours 
simplifie ce fichier avec des courbes de bezier2 (selon une distance seuil d ) et l'ecrit au format eps dans le fichier f_eps donné en argument 
largeur et hauteur sont les dimensions de l'image pbm correspondante a f_contours
et renvoie le nombre de bezier2 total apres simplification*/
UINT simp_contours_to_EPS_bezier2(char *f_contours, char *f_eps, double d, UINT largeur, UINT hauteur){
  FILE *f_e,*f_c;   // descripteurs de fichiers f_eps et f_contours
  UINT n, n_p; //nombre de contours, nombre de point d'un contour
  Contour C=creer_liste_Point_vide();  //contour non simplifié
  Tableau_Point cnt; //contour non simplifié version tabulée
  Point p;
  UINT tot_B=0; // total de bezier2 
  Liste_Point L_B2=creer_liste_Point_vide(); //liste bezier 2
  Liste_Point L_B3=creer_liste_Point_vide(); //liste bezier 3
  UINT n_B3; //nombre bezier3
  Tableau_Point L_B3t; // liste bezier 3 version tabulée
  Bezier3 B3;
   
  // ouverture de f_contours en lecture et de f_eps en ecriture
  f_c=fopen(f_contours,"r");
  if(f_c==(FILE *)NULL){
    fprintf(stderr, "erreur d'ouverture fichier contours en lecture: dans la fct simp_contours_to_EPS_bezier2 dans le module simplification\n");
    exit(-1);
  }
  f_e=fopen(f_eps,"w");
  if(f_e==(FILE *)NULL){
    fprintf(stderr, "erreur d'ouverture fichier eps en ecriture: dans la fct simp_contours_to_EPS_bezier2 dans le module simplification\n");
    exit(-1);
  }
  
  //ecriture en-tete et boite englobente
  fprintf(f_e,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f_e,"%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);
    
  // parcours de f_contours et ecriture  contour par contour simplifié dans le fichier f_eps
  fscanf(f_c,"%d",&n);     //extraction nombre contours 
  for(UINT cc=0; cc<n; cc++){    //parcours des contours, cc est un "contour_counter"
    fscanf(f_c,"%d",&n_p);    //extractions nombre de points pour un contour
    for(UINT pc=0; pc<n_p; pc++){   // parcours des points d'un contour, pc pour "point_counter"
      /*création de la liste de point C à partir d'un contour de f_contours*/
      fscanf(f_c,"%lf",&(p.x));  // extraction abscice
      fscanf(f_c,"%lf",&(p.y));  // extraction ordonnée
      C=ajouter_element_liste_Point(C, p);
    }
    cnt=sequence_points_liste_vers_tableau(C); // version tabulée contour non simplifié
       
    /*simplification contour par beziers 2*********************************************/
    L_B2=simplification_DP_Bezier2(cnt, 0, cnt.taille - 1 , d); 
    tot_B+=L_B2.taille/3;   //ajout de nombre de bezier du contour au nombre de bezier total
    /*elevation du degre du contour en bezier 3 */
    L_B3=elevation_degre_liste(L_B2);
    L_B3t=sequence_points_liste_vers_tableau(L_B3); //version tabulée
    n_B3=L_B3.taille/4;   //nombre de bezier3
    
    for(UINT i=0; i<n_B3; i++){  // parcours des beziers 3
      // extraction d'une bezier 3 cordonné PBM
      B3.C0=L_B3t.tab[i*4];
      B3.C1=L_B3t.tab[i*4+1];
      B3.C2=L_B3t.tab[i*4+2];
      B3.C3=L_B3t.tab[i*4+3];
      //conversion en cordonnee EPS
      B3.C0.y=hauteur - B3.C0.y;
      B3.C1.y=hauteur - B3.C1.y;
      B3.C2.y=hauteur - B3.C2.y;
      B3.C3.y=hauteur - B3.C3.y;
      //remplissage fichier EPS par courbe de bezier
      if(!i){ //si premier contour faire
        fprintf(f_e,"%f %f moveto %f %f %f %f %f %f curveto\n", B3.C0.x, B3.C0.y, B3.C1.x, B3.C1.y, B3.C2.x, B3.C2.y, B3.C3.x, B3.C3.y);
      }
      else{
        fprintf(f_e,"%f %f lineto %f %f %f %f %f %f curveto\n", B3.C0.x, B3.C0.y, B3.C1.x, B3.C1.y, B3.C2.x, B3.C2.y, B3.C3.x, B3.C3.y);
      }
    }
     
    //supression (liberation memoire)
    L_B3=supprimer_liste_Point(L_B3);
    L_B2=supprimer_liste_Point(L_B2); 
    C=supprimer_liste_Point(C);  
  }
  
  //config epaisseur ligne de traçage et couleu
  fprintf(f_e,"0 0 0 setrgbcolor 0 setlinewidth\n");
  //instruction tracé
  fprintf(f_e,"fill\n");
  fprintf(f_e,"showpage\n");
    
  // fermeture des deux fichiers
  fclose(f_e);
  fclose(f_c);
  
  return tot_B;        // retourner nombre de beziers2 total
}



/*procedure qui prend en argument une image pbm et simplifie tous les contours avec beziers2 (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps
 et renvoie le nombre de bezier2 total apres simplification*/
UINT simp_PBM_to_EPS_bezier2(char *f_pbm, char *f_eps, double d){
  Image I;
  Robot r;
  UINT largeur,hauteur;
  UINT tot_B; // nombre de bezier2 total apres simplification 

  //lecture fichier image et stockage dans la structure uinformatique I
  I=lire_fichier_image(f_pbm);
  
  //initialisation largeur hauteur
  largeur=largeur_image(I);
  hauteur=hauteur_image(I);
  // calcul contours et ecriture dans le fichier tmp
  calcul_contours(I, &r,"tmp_064912042021_tmp.contours");
  printf("INFO AVANT SIMPLIFICATION:\n");                        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  info_contours("tmp_064912042021_tmp.contours");
  //simplification et ecriture dans f_eps
  tot_B=simp_contours_to_EPS_bezier2("tmp_064912042021_tmp.contours", f_eps, d, largeur, hauteur);
  //supression du fichier tmp
  remove("tmp_tmp_064912042021_tmp.contours");
  return tot_B; //retourner nombre total de beziers2
}

/*fonction Gamma gamma(k,n)=6 k^4 - 8 n k^3 + 6 k^2 - 4*n*k + n^4 - n^2*/
double Gamma(double k, double n){
  return 6*pow(k, 4) - 8*n*pow(k, 3) + 6*pow(k, 2) - 4*n*k + pow(n, 4) - pow(n, 2);
}

/*fct qui prend en argument un contour format tabulé et deux indices du contour,
calcul une approximation du contour par une courbe de bezier de degre3 entre les deux indice
et renvoie cette courbe de bezier*/
Bezier3 approx_bezier3(Tableau_Point C, UINT j1, UINT j2){
  UINT n;   // (nombre de point entre l'indice j2 et j1 inclues) - 1
  Bezier2 B2;
  Bezier3 B3;
  double alpha, beta, lambda;
  Point sigma1={0,0}, sigma2={0,0};
  Point p1, p2, p3;  //points de calcul intermediaire
  
  n=j2-j1;
  if(n==1 || n==2){  // si contour reduit à deux ou trois points
    B2=approx_bezier2(C, j1, j2); 
    B3=elevation_degre(B2);   
  }
  else{ // n>=3  contourr avec au moins 4 points
    B3.C0=C.tab[j1];
    B3.C3=C.tab[j2];
    //calcul de alpha beta et lambda
    alpha=(-15)*pow((double)n, 3) + 5*pow((double)n, 2) + 2*((double)n) + 4;
    alpha=alpha/((3 * (((double)n)+2)  * (3 * pow((double)n, 2) + 1))) ;   
    beta=10*pow((double)n, 3) + (-15)*pow((double)n, 2) + ((double)n) + 2;
    beta=beta/((3 * (((double)n)+2)  * (3 * pow((double)n, 2) + 1)) );
    lambda=3* (pow((double)n, 2) - 1) * (pow((double)n, 2) - 4) * (3*pow((double)n, 2) + 1);
    lambda=(70*(double)n)/lambda;
    //calcul de sigma1 et sigma2
    for(UINT i=1; i<=(n-1); i++){
      sigma1=add_point(sigma1, scalar_vecteur(Gamma((double)i, (double)n), C.tab[j1+i]));
      sigma2=add_point(sigma2, scalar_vecteur(Gamma((double)n-i, (double)n), C.tab[j1+i]));
    }
    //calcul intermediaire
    p1=scalar_vecteur(alpha, C.tab[j1]);
    p2=scalar_vecteur(lambda, sigma1);
    p3=scalar_vecteur(beta, C.tab[j2]);
    B3.C1=add_point(add_point(p1, p2), p3); //calcul B3.C1
    //calcul intermediaire
    p1=scalar_vecteur(beta, C.tab[j1]);
    p2=scalar_vecteur(lambda, sigma2);
    p3=scalar_vecteur(alpha, C.tab[j2]);
    B3.C2=add_point(add_point(p1, p2), p3); //calcul B3.C2
  }  
  return B3;  
}


/*fct qui simplifie le contour C format tabulé  de l'indice j1 à l'indice j2 avec une courbe de bezier de degré 3
selon une distance seuil d, 
et renvoie la liste des courbes de béziers apres simplification, 
attention chaque quatre points successives du debut de la liste constitue une courbe de bézier*/
Liste_Point simplification_DP_Bezier3(Tableau_Point C, UINT j1, UINT j2, double d){
  
  
  UINT i;
  UINT n=j2-j1;  //nombre de segments de C entre les indices j1 et j2
  double dmax=0; //distance maximal entre les point du contour et la courbe de bézier de simplification
  UINT k=j1; //indice du point du contour le plus éloigné de la courbe
  double ti;  // parametre courbe bezier au pas i du calcul de la distance maximal
  double dj; //distance entre le point Pj et la courbe de bezier3
  Bezier3 B=approx_bezier3(C, j1, j2);    // approximation de la sequence des points entre les indices j1 et j2 par une Bézier de degré 3
  Liste_Point L,L1,L2; // listes courbes de bézier L etant la liste final, et les autre liste pour technique diviser pour regner
                        // ces liste contiennent les points de controle chaque trois points consecutifs constitue une courbe de bezier
  //initialisation des listes de segments
  L=creer_liste_Point_vide();
  L1=creer_liste_Point_vide();
  L2=creer_liste_Point_vide();
  
  
  for(UINT j=j1+1; j<=j2; j++){
    i=j-j1; //steps dans le calcul de la distance maximal
    ti= ((double)i) / ((double)n);
    dj=distance_point_bezier3(C.tab[j], B, ti); // dj <- dist(Pj, C(ti) )
    if(dmax<dj){
      dmax=dj;
      k=j;
    }    
  }
  
  if(dmax<=d){  // si dmax<=d alors faire: L<-{B}
    L=ajouter_element_liste_Point(L, B.C0);
    L=ajouter_element_liste_Point(L, B.C1);
    L=ajouter_element_liste_Point(L, B.C2);
    L=ajouter_element_liste_Point(L, B.C3);
  }
  else{ // sinon decomposer le problème en deux
    // simplifier la partie de C compris entre les indices j1 et k
    L1=simplification_DP_Bezier3(C, j1, k, d);
    // simplifier la partie de CONT compris entre les indices k et j2
    L2=simplification_DP_Bezier3(C, k, j2, d);
    // fusionner les deux s´equences L1 et L2
    L=concatener_liste_Point(L1, L2);
  }
  
  return L; // retourner la liste L contenant les points de controles des courbes de bezier de degré3 
}

/*fct qui prend en arguments un fichier contours 
simplifie ce fichier avec des courbes de bezier3 (selon une distance seuil d ) et l'ecrit au format eps dans le fichier f_eps donné en argument 
largeur et hauteur sont les dimensions de l'image pbm correspondante a f_contours
et renvoie le nombre de bezier3 total apres simplification*/
UINT simp_contours_to_EPS_bezier3(char *f_contours, char *f_eps, double d, UINT largeur, UINT hauteur){
  FILE *f_e,*f_c;   // descripteurs de fichiers f_eps et f_contours
  UINT n, n_p; //nombre de contours, nombre de point d'un contour
  Contour C=creer_liste_Point_vide();  //contour non simplifié
  Tableau_Point cnt; //contour non simplifié version tabulée
  Point p;
  UINT tot_B=0; // total de bezier3
  Liste_Point L_B3=creer_liste_Point_vide(); //liste bezier 3
  Tableau_Point L_B3t; //liste bezier 3 version tabulée
  Bezier3 B3; //une bezier 3
  UINT n_B3;
  
   
  // ouverture de f_contours en lecture et de f_eps en ecriture
  f_c=fopen(f_contours,"r");
  if(f_c==(FILE *)NULL){
    fprintf(stderr, "erreur d'ouverture fichier contours en lecture: dans la fct simp_contours_to_EPS_bezier3 dans le module simplification\n");
    exit(-1);
  }
  f_e=fopen(f_eps,"w");
  if(f_e==(FILE *)NULL){
    fprintf(stderr, "erreur d'ouverture fichier eps en ecriture: dans la fct simp_contours_to_EPS_bezier3 dans le module simplification\n");
    exit(-1);
  }
  
  //ecriture en-tete et boite englobente
  fprintf(f_e,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f_e,"%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);
    
  // parcours de f_contours et ecriture  contour par contour simplifié dans le fichier f_eps
  fscanf(f_c,"%d",&n);     //extraction nombre contours 
  for(UINT cc=0; cc<n; cc++){    //parcours des contours, cc est un "contour_counter"
    fscanf(f_c,"%d",&n_p);    //extractions nombre de points pour un contour
    for(UINT pc=0; pc<n_p; pc++){   // parcours des points d'un contour, pc pour "point_counter"
      /*création de la liste de point C à partir d'un contour de f_contours*/
      fscanf(f_c,"%lf",&(p.x));  // extraction abscice
      fscanf(f_c,"%lf",&(p.y));  // extraction ordonnée
      C=ajouter_element_liste_Point(C, p);
    }
    cnt=sequence_points_liste_vers_tableau(C); // version tabulée contour non simplifié
       
    /*simplification contour par beziers 3*********************************************/
    L_B3=simplification_DP_Bezier3(cnt, 0, cnt.taille - 1 , d); 
    n_B3=L_B3.taille/4;   //nombre de bezier3
    tot_B+=n_B3;   //ajout de nombre de bezier du contour au nombre de bezier total
    L_B3t=sequence_points_liste_vers_tableau(L_B3);
    
    for(UINT i=0; i<n_B3; i++){  // parcours des beziers 3
      // extraction d'une bezier 3 cordonné PBM
      B3.C0=L_B3t.tab[i*4];
      B3.C1=L_B3t.tab[i*4+1];
      B3.C2=L_B3t.tab[i*4+2];
      B3.C3=L_B3t.tab[i*4+3];
      //conversion en cordonnee EPS
      B3.C0.y=hauteur - B3.C0.y;
      B3.C1.y=hauteur - B3.C1.y;
      B3.C2.y=hauteur - B3.C2.y;
      B3.C3.y=hauteur - B3.C3.y;
      //remplissage fichier EPS par courbe de bezier
      if(!i){ //si premier contour faire
        fprintf(f_e,"%f %f moveto %f %f %f %f %f %f curveto\n", B3.C0.x, B3.C0.y, B3.C1.x, B3.C1.y, B3.C2.x, B3.C2.y, B3.C3.x, B3.C3.y);
      }
      else{
        fprintf(f_e,"%f %f lineto %f %f %f %f %f %f curveto\n", B3.C0.x, B3.C0.y, B3.C1.x, B3.C1.y, B3.C2.x, B3.C2.y, B3.C3.x, B3.C3.y);
      }
    }
     
    //supression (liberation memoire)
    L_B3=supprimer_liste_Point(L_B3);
    C=supprimer_liste_Point(C);  
  }
  
  //config epaisseur ligne de traçage et couleu
  fprintf(f_e,"0 0 0 setrgbcolor 0 setlinewidth\n");
  //instruction tracé
  fprintf(f_e,"fill\n");
  fprintf(f_e,"showpage\n");
    
  // fermeture des deux fichiers
  fclose(f_e);
  fclose(f_c);
  
  return tot_B;        // retourner nombre de beziers3 total
}

/*procedure qui prend en argument une image pbm et simplifie tous les contours avec beziers3 (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps
 et renvoie le nombre de bezier3 total apres simplification*/
UINT simp_PBM_to_EPS_bezier3(char *f_pbm, char *f_eps, double d){
  Image I;
  Robot r;
  UINT largeur,hauteur;
  UINT tot_B; // nombre de bezier3 total apres simplification 

  // lecture fichier image et stockage dans la structure uinformatique I
  I=lire_fichier_image(f_pbm);
  
  // initialisation largeur hauteur
  largeur=largeur_image(I);
  hauteur=hauteur_image(I);
  // calcul contours et ecriture dans le fichier tmp
  calcul_contours(I, &r,"tmp_144720042021_tmp.contours");
  printf("INFO AVANT SIMPLIFICATION:\n");                        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  info_contours("tmp_144720042021_tmp.contours");
  // simplification et ecriture dans f_eps
  tot_B=simp_contours_to_EPS_bezier3("tmp_144720042021_tmp.contours", f_eps, d, largeur, hauteur);
  // supression du fichier tmp
  remove("tmp_tmp_144720042021_tmp.contours");
  return tot_B; //retourner nombre total de beziers3
}