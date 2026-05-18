typedef struct {
  int ligne;
  int colonne;
} pivot;

typedef struct {
  int numJoueur;
  char nomJoueur[11];
  int aGagner;
} defJoueur;

// les données du jeu : sont mises dans une structure pour pourvoir sauvegarder dans un fichier binaire, et les récupérer facilement
typedef struct {
  int nbJoueur;
  int numeroJoueur;                           //prochain joueur à jouer
  defJoueur jo[3];
  int grille[6][8];
} jeu;
