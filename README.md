#kcwarto

## Brief ##
Ce d�pots permets de compiler la libkcwarto ainsi que le client console.
Pour l'instant �a compile sous  Linux et sous Mac. windows sera supporter plus tard.
## Libkcwarto ##
Cette library simple Comprend l'API basique de manipulation d'une partie. 
- Creer une partie 
- Executer un tour de jeu 
- Faire un tour de jeu avec l'algorithme min max ( l'ordi joue )
- Afficher en console l'etat de la partie
la librarie n'a pour l'instant aucune d�pendance.

````sh

make libkcwarto.a
```

## le client console kcwarto ##
Un client console qui permet de faire une partie complete � deux joueur en local ou contre l'ordinateur.
Le client n'a pour l'instant aucune d�pendences.
Pour compiler le client console
````sh

make console
```

## les r�gles de jeu : ##
 Le quarto se pr�sente comme un jeu de plateau, constitu� de 16 cases et de 16 pions. Chaque pion est carract�ris� par quatre caract�ristiques : 
-sa taille (grand ou petit)
-sa forme (rond ou carr�)
-sa couleur (blanc ou noir)
-s'il est point� ou non (tachet� ou pas)
##but du jeu ##
le but du jeu est d'arriver � faire un alignement gagnant, c'est � dire � alligner quatres pions sur le plateau (en ligne, colonne ou diagonnale), 	pr�sentant au moins une carract�ristique en commun. Par exemple, une ligne form�e de quatre pions de petite taille est un alignement gagnant. Le joueur qui parvient � faire un tel alignement gagne la partie.
-si � l'issue de la partie la pioche est vide et qu'il n'y a aucun 	alignement gagnant sur le plateau, alors la partie est nulle.

##D�roulement :##

- au d�part, tous les pions sont dans la pioche, le plateau est vide
- le joueur qui commence choisi un pion dans la pioche, qu'il donne � son adversaire.
-l'adversaire pose alors ce pion sur le plateau et choisi � son tour un pion dans la pioche pour son adversaire.
-le jeu se poursuit ainsi jusqu'a ce qu'un des deux joueurs arrive � faire un alignement gagnant ou que tous les pions soient plac�s sur le plateau

