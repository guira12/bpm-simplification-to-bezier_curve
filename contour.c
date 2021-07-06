#include<stdlib.h>
#include<stdio.h>
#include "contour.h"



void avancer(Robot *r){
    switch(r->o){
    case N:
      r->p.y-=1;
      break;
    case S:
      r->p.y+=1;
      break;
    case E:
      r->p.x+=1;
      break;
    case W:
      r->p.x-=1;
      break;
    default:
      fprintf(stderr,"erreur: orientaion robot");
  }
}

//tourner à gauche
void gauche(Robot *r){
  switch(r->o){
    case N:
      r->o=W;
      break;
    case S:
      r->o=E;
      break;
    case E:
      r->o=N;
      break;
    case W:
      r->o=S;
      break;
    default:
      fprintf(stderr,"erreur: orientaion robot");
  }
}

//tourner à droite
void droite(Robot *r){
    switch(r->o){
    case N:
      r->o=E;
      break;
    case S:
      r->o=W;
      break;
    case E:
      r->o=S;
      break;
    case W:
      r->o=N;
      break;
    default:
      fprintf(stderr,"erreur: orientaion robot");
  }
}



/*cherche le point de départ du robot si point de depart
 non existant la fct sort avec une erreur*/
Point point_depart(Image I){
  Point p;
  for(int j=1; j<=I.H; j++){
    for(int i=1; i<=I.L; i++){
      if(get_pixel_image(I, i, j-1)==BLANC && get_pixel_image(I, i, j)==NOIR){   //condition if: si le pixel parcourue est noir et son voisin nord et blanc on rentre dans le if{}
        p.x=i-1;                                                                  //si (x,y) est hors de l'image la fonction get_pixel()  renvoie BLANC
        p.y=j-1;                                                                  //le point de depart du robot se trouve au sommet NW du pixel de depart
        return p;
      }
    }
  }
  //cas ou l'image est blache càd pas de pixel candidat trouvé la fct renvoie un point de départ impossible en dehors  de l'image
  fprintf(stderr,"erreur de calcul point de depart: aucun pixel de depart trouve donc image totalement blanche\n");
  exit(-1);
}

//change l'orientation du robot de facon à pouvoir tourner autour du motif noir sur l'image
void nouvelle_orientation(Image I,Robot *r){
 Pixel pG,pD;
 //couleur pixel avant gauche et avant droit cela depend de l'orientation du robot
 switch(r->o){
   case N:
     pG=get_pixel_image(I, (r->p.x), (r->p.y));
     pD=get_pixel_image(I, (r->p.x)+1, r->p.y);
     break;
   case S:
     pG=get_pixel_image(I, (r->p.x)+1, (r->p.y)+1);
     pD=get_pixel_image(I, (r->p.x), (r->p.y)+1);
     break;
   case E:
     pG=get_pixel_image(I, (r->p.x)+1, (r->p.y));
     pD=get_pixel_image(I, (r->p.x)+1, (r->p.y)+1);
     break;
   case W:
     pG=get_pixel_image(I, (r->p.x), (r->p.y)+1);
     pD=get_pixel_image(I, (r->p.x), (r->p.y));
     break;
   default:
     fprintf(stderr,"erreur: orientation lors du calcule de contour");
     exit(1);
     break;
 }
 if(pG==NOIR)                  //4 cas de figure pris en compte
   gauche(r);
 else if(pD==BLANC)
   droite(r);
}

/*fct recoie une image pbm un robot non initialisé et un point de depart du robot 
et calcul le contour à partir du point de depart donné en argument et renvoie le 
contour sous forme de liste de points*/
Liste_Point calcul_contour(Image I, Robot *r, Point pi){
  int boucle=1;      //est un bool
  Liste_Point L=creer_liste_Point_vide(); 
  //initialisation robot
  r->p.x=pi.x;
  r->p.y=pi.y;
  r->o=E;
  //boucle contour et affichage points
  while(boucle){
    L=ajouter_element_liste_Point(L,set_point(r->p.x, r->p.y));
    avancer(r);
    nouvelle_orientation(I,r);
    if(r->p.x==pi.x && r->p.y==pi.y && r->o==E)   //si le robot et revenu à la position initial et à l'orientation initial-EST-on sort de la boucle
      boucle=0;
  }
  L=ajouter_element_liste_Point(L,set_point(r->p.x, r->p.y));
  return L;
}


/*ecrire le contour L a l'ecran 
cette procedure montre un exemple de conversion d'une liste de points en
tableau de points afin de pouvoir par la suite acceder aux element d'une sequence 
de points par indice*/
void ecrire_contour_ecran(Liste_Point L){
  Tableau_Point TP=sequence_points_liste_vers_tableau(L);
  int k;
  int nP=TP.taille;
  
  printf("%d points : [" , nP);
  for(k=0; k<nP; k++){
    Point P=TP.tab[k]; //recuperer le point d'indice k
    printf(" (%5.1f,%5.1f)", P.x, P.y);
  }
  printf("]\n");
  
  free(TP.tab);   //supprimer le tableau de point TP
}



//ecrire dans le fichier nom_fich en mode append, le nombre de points, et les cordonnees des points d' un contours
void ecrire_contour_inFile(Liste_Point L, char *nom_fich ){
  FILE *f;
  Tableau_Point TP=sequence_points_liste_vers_tableau(L);
  int nP=TP.taille;
  Point P;
  
  
  f=fopen(nom_fich,"a");
  if(f==NULL){
    fprintf(stderr,"erreur ouverture fichier en ecriture\n");
    exit(1);
  }
  
  //ecriture nombre de points du contour
  fprintf(f,"\n\n");
  fprintf(f,"%d\n",nP);
  //boucle ecriture des points du contour
  for(int k=0; k<nP; k++){
    P=TP.tab[k];
    fprintf(f," %.2f %.2f\n",P.x, P.y);
  }
  fclose(f);
  free(TP.tab);   //supprimer le tableau de point TP
}


/*procedure prend en argument un contour une largeur une hauteur,
 et cree un fichier eps <nom_fich> avec un bounding box <0 0 largeur hauteur>
  et les instructions de traçage du contour selon le mod1*/
void ecrire_contour_inEPS_mod1(UINT largeur, UINT hauteur, Liste_Point L, char *nom_fich){
  FILE *f;
  Cellule_Liste_Point *el;
  int estPremierPoint=1;
  double px,py;    //cordonnées repere eps
  
  //ouverture fichier en ecriture +verification bonne ouverture
  f=fopen(nom_fich,"w");
  if(f==NULL){
    fprintf(stderr,"erreur ouverture fichier en ecriture\n");
    exit(1);
  }
  
  //ecriture en-tete et boite englobente
  fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);
  
  //boucle de tracage
  el=L.first;
  while(el!=NULL){
    //calcul des cordonnés points adaptées au repère eps
    px=el->data.x;
    py=hauteur-(el->data.y);
    if(estPremierPoint==1){                                      //si premier point du contour
      fprintf(f,"%f %f moveto\n", px, py);
      estPremierPoint=0;
    }
    else{
      fprintf(f,"%f %f lineto\n", px, py);
    }
    el=el->suiv;
  }
  
  //config epaisseur ligne de traçage et couleu
  fprintf(f,"0 0 0 setrgbcolor 0 setlinewidth\n");
  //instruction tracé
  fprintf(f,"stroke\n");
  fprintf(f,"showpage\n");
  
  
  fclose(f);
}


/*procedure prend en argument un contour une largeur une hauteur,
 et cree un fichier eps <nom_fich> avec un bounding box <0 0 largeur hauteur>
  et les instructions de traçage du contour selon le mod2*/
void ecrire_contour_inEPS_mod2(UINT largeur, UINT hauteur, Liste_Point L, char *nom_fich){
  FILE *f;
  Cellule_Liste_Point *el;
  int estPremierPoint=1;
  double px,py;    //cordonnées repere eps
  double r=0.2;  //rayon des disques condition r<0.5 sinon cercles qui se chevaucher
  
  //ouverture fichier en ecriture +verification bonne ouverture
  f=fopen(nom_fich,"w");
  if(f==NULL){
    fprintf(stderr,"erreur ouverture fichier en ecriture");
    exit(1);
  }
  
  //ecriture en-tete et boite englobente
  fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);
  
  /*******boucle de tracage des segments**********/
  el=L.first;
  while(el!=NULL){
    //calcul des cordonnés points adaptées au repère eps
    px=el->data.x;
    py=hauteur-(el->data.y);
    if(estPremierPoint==1){                                      //si premier point du contour
      fprintf(f,"%f %f moveto\n", px, py);
      estPremierPoint=0;
    }
    else{
      fprintf(f,"%f %f lineto\n", px, py);
    }
    el=el->suiv;
  }
  //config epaisseur ligne de traçage et couleu
  fprintf(f,"0 0 0 setrgbcolor 0.1 setlinewidth\n");
  //instruction tracé
  fprintf(f,"stroke\n");
  
  /*******boucle de tracage des disques**********/
  el=L.first;
  fprintf(f,"0 0 1 setrgbcolor\n");
  while(el->suiv!=NULL){
    //calcul des cordonnés points adaptées au repère eps
    px=el->data.x;
    py=hauteur-(el->data.y);
    //instruction cercle eps
    fprintf(f,"newpath\n");
    fprintf(f,"%f %f %f 0 360 arc\n", px, py, r);
    
    fprintf(f,"fill\n");
    fprintf(f,"closepath\n");
    el=el->suiv;
  }


  fprintf(f,"showpage\n");
  
  
  fclose(f);
}




/*procedure prend en argument un contour une largeur une hauteur,
 et cree un fichier eps <nom_fich> avec un bounding box <0 0 largeur hauteur>
  et les instructions de traçage du contour selon le mod3*/
void ecrire_contour_inEPS_mod3(UINT largeur, UINT hauteur, Liste_Point L, char *nom_fich){
  FILE *f;
  Cellule_Liste_Point *el;
  int estPremierPoint=1;
  double px,py;    //cordonnées repere eps
  
  //ouverture fichier en ecriture +verification bonne ouverture
  f=fopen(nom_fich,"w");
  if(f==NULL){
    fprintf(stderr,"erreur ouverture fichier en ecriture");
    exit(1);
  }
  
  //ecriture en-tete et boite englobente
  fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);
  
  //boucle de tracage
  el=L.first;
  while(el!=NULL){
    //calcul des cordonnés points adaptées au repère eps
    px=el->data.x;
    py=hauteur-(el->data.y);
    if(estPremierPoint==1){                                      //si premier point du contour
      fprintf(f,"%f %f moveto\n", px, py);
      estPremierPoint=0;
    }
    else{
      fprintf(f,"%f %f lineto\n", px, py);
    }
    el=el->suiv;
  }
  
  //config epaisseur ligne de traçage et couleu
  fprintf(f,"0 0 0 setrgbcolor 0 setlinewidth\n");
  //instruction tracé
  fprintf(f,"fill\n");
  fprintf(f,"showpage\n");
  
  
  fclose(f);
}

/*fct recoie une image pbm, son masque M, un pointeur vers un robot non initialisé et un point de depart du robot 
et calcul le contour à partir du point de depart donné en argument et renvoie le 
contour sous forme de liste de points, tout en mettant en BLANC  le pixel SUD EST par rapport
 à la position du robot dans le masque si le robot est orienté EST */
Liste_Point calcul_C_modif_M(Image I, Image *M, Robot *r, Point pi){
  int boucle=1;      //est un bool
  Liste_Point L=creer_liste_Point_vide(); 
  int x,y;  //cordonnée du pixel SE du robot 

  //initialisation robot
  r->p.x=pi.x;
  r->p.y=pi.y;
  r->o=E;
  //boucle contour et affichage points
  while(boucle){
    /*modification du masque si robot est orienté EST */
    if(r->o==E){               //si robot orienté EST
      x=(r->p.x)+1 ;             // calcul des cordonnés du pixel SE du robot (pixel candidat correspondant)
      y=(r->p.y)+1;
      set_pixel_image(*M, x, y, BLANC );   // rendre le pixel SE BLANC
    }
    /*calcul du contour*/
    L=ajouter_element_liste_Point(L,set_point(r->p.x, r->p.y));
    avancer(r);
    nouvelle_orientation(I,r);
    if(r->p.x==pi.x && r->p.y==pi.y && r->o==E)   //si le robot et revenu à la position initial et à l'orientation initial-EST-on sort de la boucle
      boucle=0;
  }
  L=ajouter_element_liste_Point(L,set_point(r->p.x, r->p.y));
  return L;
}

/*procedure qui calcul tous les contours de l'image I et les stock dans le fichier nom_fich,
et ecrit au debut de ce fichier le nombre de contour de l'image I*/
void calcul_contours(Image I, Robot *r,char *nom_fich){
  Image M=calculer_masque_image(I);      //initialisation du masque M de I 
  UINT L,H;   // largeur et hauteur de l'image et du masque
  Pixel pix_M;   //Pixel du masque
  Point pi; //point initial contour
  Contour C;
  int cc=0;   // contours counter
  char c;  // utilise pour stocker les charactere du fichier tmp pour les copier vers le fichier nom_fich
  int err_del; //resultat de la fct suppression fichier tmp
  FILE *f,*g;
  
  /*calcul des dimensions*/
  L=largeur_image(I);
  H=hauteur_image(I);
  /*parcours du masque */
  for(int y=1; y<=H; y++){
    for(int x=1; x<=L; x++){ 
      pix_M=get_pixel_image(M, x, y);
      if(pix_M==NOIR){         //si pixel du masque noir 
        pi.x=x-1;            //calcul des cordonnés du point initial du contour à calculer  
        pi.y=y-1;
        C=calcul_C_modif_M(I, &M, r, pi);   // calcul du contour et modification du masque, tout les pixels candidats adjacents au contour en BLANC
        ecrire_contour_inFile(C, "tmp_sign143316032021" ); // ecriture dans un fichier temporaire en mode append
        cc++;             //incrementation du compteur de contour 
      }
    }
  }
    
  // ouverture du fichier nom_fich en ecriture
  f=fopen(nom_fich, "w");
  if(f==(FILE *)NULL){
    fprintf(stderr, "erreur ouverture fichier en ecriture\n");
    exit(-1);
  }
  //ecriture nombre de contours dans nom_fich
  fprintf(f,"%d", cc);
  // ouverture du fichier tmp_sign143316032021 en ecriture
  g=fopen("tmp_sign143316032021", "r");
  if(f==(FILE *)NULL){
    fprintf(stderr, "erreur ouverture fichier temporaire en lecture\n");
    exit(-2);
  }
  
  /*boucle copy du fichier temporaire dans la suite de  nom_fich*/ 
  while(!feof(g)){
    fscanf(g,"%c",&c);
    fprintf(f,"%c",c);
  }
  
  //fermeture fichier 
  fclose(f);
  //fermeture fichier temporaire et supression du fichier
  fclose(g);
  err_del=remove("tmp_sign143316032021");   //err_del=0 si supression reussi sinon =autre chose
  if(err_del){
    fprintf(stderr,"erreur lors de la suppression du fichier temporaire tmp_sign143316032021");
    exit(-1);
  }
  //liberer espace alloué pour contour
  supprimer_liste_Point(C);
}

/*procedure qui prend en argument un fichier au format ensemble de contours 
et affiche à l'écran: -le nombre de contours
                      -le nombre totale de points
                      -le nombre total de segments
*/
void info_contours(char *nom_fich){
  FILE *f;
  int n;  //nombre contours
  int n_p,n_pt=0; //nombre de points, nombre de points total
  float a_c;     // variable qui lit les points pour avancer le curseur
  int n_st; // nombre de segments
  
  //ouverture fichier en lecture
  f=fopen(nom_fich,"r");
  if(f==(FILE *)NULL){
    fprintf(stderr,"erreur lors de l'ouverture du fichier en lecture, dans la procedure info_contours dans le module contour\n ");
    exit(-1);
  }
   
  fscanf(f,"%d",&n);     //extraction nombre contours
  
  /*boucle pour avoir le nombre de points total calculé par accumulation*/
  for(int j=0 ; j<n; j++){
    fscanf(f,"%d",&n_p);    //extractions nombre de points pour un contour
    n_pt+=n_p;          //accumulation 
    //boucle pour avancer le cursseur au nombre de points du contour suivant
    for(int i=n_p*2; i>=1; i--){  // *2 car constitué abscice et d'ordonnée
      fscanf(f,"%f",&a_c);
    }    
  }
  // calcul nombre de segment total
  n_st=n_pt-n; // car pour un contour n_segments=n_points - 1
  
  fprintf(stdout,"info concernant %s :\n",nom_fich);
  fprintf(stdout, "\tNombre de contours= %d\n", n);
  fprintf(stdout, "\ttotal de points= %d\n", n_pt);
  fprintf(stdout, "\ttotal de segments= %d\n", n_st);
  
  
}


/*procedure qui cree un fichier EPS de nom (fich_eps) de largeur et hauteur données en arguments
en mod3 remplissage, à partir d'une sequence de contours (fich_contours) */
void contours_to_EPS(UINT largeur, UINT hauteur, char *fich_contours, char *fich_eps){
  FILE *f,*g;
  int n,n_p; //n:nombre de contours, n_p=nombre de point pour un contour
  int estPremierPoint=1; // bool vrai si premier point d'un contours, faux sinon
  double x,y;  //coordonnées points repere pbm
  double py;   //ordonnée points repere eps =hauteur-y, l'abscice reste le meme =x
  
  //ouverture des deux fichier 
  f=fopen(fich_eps,"w");
  g=fopen(fich_contours,"r");
  if(f==(FILE *)NULL || g==(FILE *)NULL){
    fprintf(stderr,"erreur ouverture fichier dans procedure <contours_to_EPS>");
    exit(-1);
  }
  
  //ecriture en-tete et boite englobente
  fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f,"%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);

  fscanf(g,"%d",&n);     //extraction nombre contours
  /*boucle de traçage de differnet contours*/
  for(int i=0; i<n; i++){
    fscanf(g,"%d",&n_p);    //extractions nombre de points pour un contour
    for(int j=0; j<n_p; j++){
      fscanf(g,"%lf",&x);  // extraction abscice
      fscanf(g,"%lf",&y);  // extraction ordonnée
      py=hauteur-y;
      if(estPremierPoint){
        fprintf(f,"%f %f moveto\n", x, py);
        estPremierPoint=0;
      }
      else{
        fprintf(f,"%f %f lineto\n", x, py);
      }
    }
    estPremierPoint=1;  // on remet le bool à un pour le premier point du nouveau contour
  }
  
  
  //config epaisseur ligne de traçage et couleu
  fprintf(f,"0 0 0 setrgbcolor 0 setlinewidth\n");
  //instruction tracé
  fprintf(f,"fill\n");
  fprintf(f,"showpage\n");
  
  fclose(f);
  fclose(g);
}

