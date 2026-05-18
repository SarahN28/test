#include <bib.h>
#include <constante.h>
#include <struct.h>
#include <fonction.h>

// programme principal
 int main () {
 int numerocol = 0;
 int finpartie = 1;
 int nvlig, nbpivot, nbcase;
 int retF = 0;
 char carlu;
 char reprise = ' ';
 pivot piv;
 jeu nvJeu;
 FILE *f = NULL;
 srand(time(NULL));
   
 f=fopen("SauvP5.txt", "rb") ;
 if(f!= NULL) {                                                                                                      // verification si sauvegarde du jeu existe
  while(reprise != 'o' && reprise != 'O' && reprise != 'n' && reprise != 'N') {
    do {
      if (reprise == '\n'){
        printf("erreur 2 de saisie\n");
      }
      printf("Voulez vous reprendre l'ancienne partie ? O pour Oui, N pour Non \n");
      scanf("%c", &reprise);
    } while (reprise == '\n');
    carlu = getchar();
    while (carlu != '\n') {
      carlu = getchar();
    }
  }
}
if (reprise=='o' || reprise == 'O') {                                                                    // initialisation jeu avec sauvegarde
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
if(f!= NULL) {                                                                                         // suppression du fichier de sauvegarde
 retF = fclose(f);
 retF = remove("SauvP5.txt");
}
printGame(nvJeu, NBLIG, NBCOL);
while(finpartie == 1) {                                                                                  // a faire tant que partie non terminée
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
      reprise = ' ';
      do {
        printf("Voulez vous sauvegarder la partie ? O pour Oui, N pour Non \n");
        scanf("%c", &reprise);
        if(reprise == 'o' || reprise == 'O') { 
          sauvJeux(nvJeu, f);
          return 0;
        }
      } while (reprise!='o' && reprise!='O' && reprise!='n' && reprise!='N' || reprise == '\n');
      carlu = getchar();
      while (carlu != '\n') {
        carlu = getchar();
       }
    }
    nvlig= deplacement_bas(nvJeu.grille, nvJeu.numeroJoueur+2, numerocol);                  // insertion du jeton : valeur jeton = indice  du joueur + 2
   }                                                                                        // fin insertion du jeton : le nouveau pion sera en nvlig, numerocol
  printGame(nvJeu, NBLIG, NBCOL);
  piv = choixPivot(nbcase, nvlig, numerocol);                                               // demande position du pivot
  if (piv.ligne==99) {
    finpartie = 2;
    return 0;
   }
  if (demanderRotation() ==1 ) {                                                            // demande du type de rotation
   rotationHoraire(nvJeu.grille, nbcase, piv);
   }
  else {
    rotationAntiHoraire(nvJeu.grille, nbcase, piv);
   }
  printGame(nvJeu, NBLIG, NBCOL);
  gravitePivot(nvJeu.grille, piv, nbcase);                                                 // gravité suite à la rotation
  printGame(nvJeu, NBLIG, NBCOL);
  finpartie = finJeu(nvJeu.grille, nvJeu.jo);                                              // si finpartie = 2 => Terminée pas de gagnant, si = 0 : gagnant
  if (nvJeu.numeroJoueur >= nvJeu.nbJoueur-1) {                                            // calcul du nouveau joueur qui doit jouer
    nvJeu.numeroJoueur = 0;
   }
   else {
     nvJeu.numeroJoueur =  nvJeu.numeroJoueur+1;
    }
}                                                                                         //fin de partie
if (finpartie == 2) {                                                                      // affichage résultat 
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
