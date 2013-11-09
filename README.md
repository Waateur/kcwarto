#kcwarto

## Brief ##
Ce dépots permets de compiler la libkcwarto ainsi que le client console.
Pour l'instant ça compile sous  Linux et sous Mac. windows sera supporter plus tard.
## Libkcwarto ##
Cette library simple Comprend l'API basique de manipulation d'une partie. 
- Creer une partie 
- Executer un tour de jeu 
- Faire un tour de jeu avec l'algorithme min max ( l'ordi joue )
- Afficher en console l'etat de la partie
la librarie n'a pour l'instant aucune dépendance.

````sh

make libkcwarto.a
```

## le client console kcwarto ##
Un client console qui permet de faire une partie complete à deux joueur en local ou contre l'ordinateur.
Le client n'a pour l'instant aucune dépendences.
Pour compiler le client console
````sh

make console
```

## les règles de jeu : ##
 Le quarto se présente comme un jeu de plateau, constitué de 16 cases et de 16 pions. Chaque pion est carractérisé par quatre caractéristiques : 
-sa taille (grand ou petit)
-sa forme (rond ou carré)
-sa couleur (blanc ou noir)
-s'il est pointé ou non (tacheté ou pas)
##but du jeu ##
le but du jeu est d'arriver à faire un alignement gagnant, c'est à dire à alligner quatres pions sur le plateau (en ligne, colonne ou diagonnale), 	présentant au moins une carractéristique en commun. Par exemple, une ligne formée de quatre pions de petite taille est un alignement gagnant. Le joueur qui parvient à faire un tel alignement gagne la partie.
-si à l'issue de la partie la pioche est vide et qu'il n'y a aucun 	alignement gagnant sur le plateau, alors la partie est nulle.

##Déroulement :##

- au départ, tous les pions sont dans la pioche, le plateau est vide
- le joueur qui commence choisi un pion dans la pioche, qu'il donne à son adversaire.
-l'adversaire pose alors ce pion sur le plateau et choisi à son tour un pion dans la pioche pour son adversaire.
-le jeu se poursuit ainsi jusqu'a ce qu'un des deux joueurs arrive à faire un alignement gagnant ou que tous les pions soient placés sur le plateau

