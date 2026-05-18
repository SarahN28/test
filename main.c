#include <bib.h>
#include <constante.h>
#include <struct.h>
#include <fonction.h>

int main () {
  int nvlig, nbpivot, nbcase, ok;
  int numerocol = 0;
  int finpartie = 1;
  int retF = 0;
  char carlu;
  char reprise = ' ';
  pivot piv;
  jeu nvJeu;
  FILE *f = NULL;
  srand(time(NULL));

  f=fopen("SauvP5.txt", "rb") ;                                            // verification si sauvegarde du jeu existe
  if(f!= NULL) {
    while(reprise != 'o' && reprise != 'O' && reprise != 'n' && reprise != 'N') {
      printf("Voulez vous reprendre l'ancienne partie ? O pour Oui, N pour Non \n");
      scanf("%c", &reprise);
      carlu = getchar();
      while (carlu != '\n') {
      carlu = getchar();
    }
  }
}

// initialisation jeu avec sauvegarde
if (reprise=='o' || reprise == 'O') {
  retF = fread(&nvJeu, sizeof(jeu), 1, f);
  if (retF!=1) {
    printf("Dernier jeux introuvable, vous allez commencer une nouvelle partie \n");
  }
}
// initialisation du jeu si non récupérer du fichier de sauvegarde
if (retF != 1) {
  nvJeu.nbJoueur=constructJoueur(nvJeu.jo);
  if (nvJeu.nbJoueur == 99) {
    return 0;
  }                                                               //finpartie
  createPiste(nvJeu.grille, NBLIG, NBCOL);
  nvJeu.numeroJoueur = 0; 
}
// suppression du fichier de sauvegarde
if(f!= NULL) {
 retF = fclose(f);
 retF = remove("SauvP5.txt");
}

printGame(nvJeu, NBLIG, NBCOL);


// a faire tant que partie non terminée
while(finpartie == 1) {
  printf("Au tour du joueur %s \n", nvJeu.jo[nvJeu.numeroJoueur].nomJoueur);
  nvlig = -1;
   // calcul largeur carré à pivoter
  nbpivot = selectionpivot();
  nbcase = nbpivot/2;
  
  //insertion du jeton du nv joueur
  while(nvlig==-1) {
    // demander la colonne où insérer le jeton ou 99 pour sortir
    numerocol = saisiecolonne(nvJeu.numeroJoueur); 
    if (numerocol ==99) {
      finpartie = 2;
      printf("Voulez vous sauvegarder la partie ? O pour Oui, N pour Non \n");
      scanf("%c", &reprise);
      if(reprise == 'o' || reprise == 'O') { 
        sauvJeux(nvJeu, f);}
      return 0;
    }
    // insertion du jeton : valeur jeton = indice  du joueur + 2
    nvlig= deplacement_bas(nvJeu.grille, nvJeu.numeroJoueur+2, numerocol);
   
  }
  // fin insertion du jeton : le nouveau pion sera en nvlig, numerocol
  printGame(nvJeu, NBLIG, NBCOL);
 
 
 // sélection du pivot
  ok = 1;
  while(ok==1) {
  // demande position du pivot
  piv = choixPivot(nbcase, nvlig, numerocol);
  if (piv.ligne==99) {
      finpartie = 2;
      return 0;
    }
  
  // a tester : vérification que le nouveau pion est bien dans la zone de pivot 
    ok = verifpivot(piv, nbcase, nvlig, numerocol);
    if (ok==1) {
     printf("votre pion n'est pas dans la zone de rotation : %d case(s) autour du pivot. Veuillez re-saisir le pivot \n", nbcase);
     }
  }
 
  // demande du type de rotation
  if (demanderRotation() ==1 ) {
   rotationHoraire(nvJeu.grille, nbcase, piv);
   }
  else {
    rotationAntiHoraire(nvJeu.grille, nbcase, piv);
   }
 
   printGame(nvJeu, NBLIG, NBCOL);
   
   // gravité suite à la rotation
   gravitePivot(nvJeu.grille, piv, nbcase);
   
   printGame(nvJeu, NBLIG, NBCOL);
  
  // si finpartie = 2 => Terminée pas de gagnant, si = 0 : gagnant
  finpartie = finJeu(nvJeu.grille, nvJeu.jo);
  
  // calcul du nouveau joueur qui doit jouer
  if (nvJeu.numeroJoueur >= nvJeu.nbJoueur-1) {
    nvJeu.numeroJoueur = 0;
  }
  else {
    nvJeu.numeroJoueur =  nvJeu.numeroJoueur+1;
  }
}
//fin de partie

// affichage résultat :
if (finpartie == 2) {
 printf("La partie est terminée, SANS gagnant \n");
 }
 else {
  for (int i=0; i<3; i++) {
    if (nvJeu.jo[i].aGagner == 1) {
      printf("BRAVO au joueur %s, vous avez gagné\n", nvJeu.jo[i].nomJoueur);
    }
  }
 }

return 0;
}
