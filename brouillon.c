void resultPlayer(Player plgame[3], int nbplay) {
int gameplay[3] = {0 ;0 ;0} ;
int gamewin[3] = {0 ;0 ;0} ;
int nblu, trouv, i, j, k ;
Game gamelu ;
FILE *fr ;
 fr = fopen("ResultP5.txt ", "rb") ;
nblu =1 ;
while(nblu==1) {   // nblu : nombre de block lu par fread : si !=1 : fin de fichier ou erreur
   nblu = fread((&gamelu, sizeof(Game), 1, fr) ;   // gamelu.pl contient la liste des joueurs
  if (nblu == 1) {      
      for ( i = 1 ; i<3 ; i++) {                      //boucle sur joueur récupéré dans le fichier gamelu.pl  
           for ( j=1 ; j<nbplay ; j++) {     // boucle sur les joueurs à analyser
                 trouv = 1 ;
                  for  (k=0 ; k<10 ; k++) {     // boucle sur le nom pour vérifier s’ils sont identiques
                        If(plgame[j].namePlayer[k] !=gamelu.pl[i]. namePlayer[k]) { 
                               trouv = 0 ;
                       } /* fin if */
                   } /* fin k */
                 If (trouv == 1) {      // le nom est identique : on augment le nb de partie du joueur j
                     gameplay[j]=gameplay[j]+1 ;
                     if (gamelu.pl[i].Win == 1) {      // si la partie pour le joueur récupéré était gagnée
                           gamewin[j]=gamewin[j]+1 ;
                     }
                  } /* fin si trouv ==1 */
               } // fin boucle j :on a vérifié l’égalité sur tous les joueurs à analyser pour le joueur i
            } // fin boucle i : on a vérifier tous les joueurs i  récupérés de la lecture
    } /* fin if nblu==1 */
} /* fin  lecture fichier : boucle while*/
nblu = fclose(fr);
// affichage du résultat
For(i = 0 ; i<nbplay ; i++){
   Printf("le joueur %s a gagné %d partie(s) sur %d soit %d % de victoire  \n ",
  plgame[i].namePlayer, gamewin[i] , gameplay[i], (gameplay[i]/gameplay[j]*100) ) ;
} // fin boucle for
} /* fin fonction */
