// saisie du nombre de joueur
int constructJoueur (defJoueur joueur[3]){
  int n = 0;
  int j;
  char carlu;
  do{
     printf("Nombre de joueurs:\n");
     printf("2 : 2joueurs       3 : 3joueurs       sinon pour sortir tapez 99 :\n");
     scanf("%d", &n);
     getchar();
     if (n!=2 && n!=3 && n!=99) {
       printf("Erreur :  le nombre de joueur est incorrect\n");}
  } while (n!=2 && n!=3 && n!=99);
  if (n==99) {
   return(n);
  }
  for(int i=0; i<n; i++) {
   joueur[i].numJoueur = i+1;
   joueur[i].pieceJoueur = i+1;
   joueur[i].aGagner = 0;
   printf("Entrez le nom du joueur %d et tapez sur la touche Entrée \n", i+1);
   carlu = ' ';
   j=0;
   while (carlu !='\n') {
     scanf("%c", &carlu);
     if (j < 10) {
       joueur[i].nomJoueur[j] = carlu;
       j++;
     }
   }
  }
  return(n);
 }
