void resultPlayer(Player plgame[3], int nbplay) {
  int gameplay[3] = {0 ;0 ;0} ;
  int gamewin[3] = {0 ;0 ;0} ;
  int nblu, trouv, i, j, k ;
  Game gamelu ;
  FILE *fr ;
  fr = fopen("ResultP5.txt ", "rb") ;
  nblu =1 ;
  while(nblu==1) {   
    nblu = fread((&gamelu, sizeof(Game), 1, fr) ;  
    if (nblu == 1) {      
      for ( i = 1 ; i<3 ; i++) {               
        for ( j=1 ; j<nbplay ; j++) { 
          trouv = 1 ;
          for  (k=0 ; k<10 ; k++) {   
            if (plgame[j].namePlayer[k] !=gamelu.pl[i]. namePlayer[k]) { 
              trouv = 0 ;
             }
           }
          if (trouv == 1) {
            gameplay[j]=gameplay[j]+1 ;
            if (gamelu.pl[i].Win == 1) {
              gamewin[j]=gamewin[j]+1 ;
             }
           }
         }
       }
     }
   }
  nblu = fclose(fr);

// affichage du résultat
  for (i = 0 ; i<nbplay ; i++){
    printf("le joueur %s a gagné %d partie(s) sur %d soit %d % de victoire  \n ",  plgame[i].namePlayer, gamewin[i] , gameplay[i], (gameplay[i]/gameplay[j]*100) ) ;
   }
}
