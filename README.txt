***********************************************************************************
Quarto, les r�gles de jeu :

	- Le quarto se pr�sente comme un jeu de plateau, constitu� de 16 cases et 	de 16 pions. Chaque pion est carract�ris� par quatre caract�ristiques : 
		-sa taille (grand ou petit)
		-sa forme (rond ou carr�)
		-sa couleur (blanc ou noir)
		-s'il est point� ou non (tachet� ou pas)

	-le but du jeu est d'arriver � faire un alignement gagnant, c'est � dire � 
	alligner quatres pions sur le plateau (en ligne, colonne ou diagonnale), 	pr�sentant au moins une carract�ristique en commun. Par exemple, une ligne 	form�e de quatre pions de petite taille est un alignement gagnant. Le 	joueur qui parvient � faire un tel alignement gagne la partie.

	-si � l'issue de la partie la pioche est vide et qu'il n'y a aucun 	alignement gagnant sur le plateau, alors la partie est nulle.

	D�roulement :

	- au d�part, tous les pions sont dans la pioche, le plateau est vide
	- le joueur qui commence choisi un pion dans la pioche, qu'il donne � son 	adversaire.
	-l'adversaire pose alors ce pion sur le plateau et choisi � son tour un 	pion dans la pioche pour son adversaire.
	-le jeu se poursuit ainsi jusqu'a ce qu'un des deux joueurs arrive � faire 	un alignement gagnant ou que tous les pions soient plac�s sur le plateau


***********************************************************************************
Pour compiler :

	- D�posez le dossier Projet_L3_Janod&Richier dans le dossier examples d'irrlicht.
	
	- Ensuite 3 solutions :

		(1) Lancez le fichier quarto.dev (le programme devCpp se lance)
		 Appuyez sur f9 (build and run) : le jeu se lance.
		
		(2) Lancez le fichier cwarto-linux.cbp ou cwarto-windows.cbp avec 			Code::blocks
		Verfifez les parametres du linker qui d�pendent de la machine 
		et compilez puis executez.
		le fichier excutable sera cr�e dans le dossier du projet.
		
		(3) Utiliser le makefile qui va creer un executable dans le dossier 		du projet 

		(4) en cas de problem de compilation un executable est fourni pour 			windows

***********************************************************************************
Le menu:

	-choisir un mode d'affichage avec la scrollBar du haut : fen�tre ou plein
	�cran
	
	-vous pouvez choisir entre trois niveaux de difficult�s pour le mode jeu 		contre ordinateur, cel� � l'aide de la scrollBar LEVEL

		-Selectionner le mode de jeu voulu � l'aide des boutons du bas : 	CPU pour lancer le mode joueur contre ordinateur (c'est le joueur qui 	commence), ou VS pour lancer le mode deux joueurs (c'est le joueur1 qui 	commence la partie). L� le jeu se lance.

	-Le bouton QUIT permet de quitter le jeu

***********************************************************************************
Pour jouer :

	- Pour d�placer le halo bleut� dans la pioche ou le plateau, utilisez les 		touches Z, Q, S, et D pour haut, gauche, bas et droite.

	- Pour selectionner un pion dans la pioche ou une case sur le plateau, 	appuyez sur la barre d'espace.

	- Suivez les instructions � l'�cran pour l'alternance joueur1/joueur2.

	- Vous pouvez faire pivoter le plateau pour une meilleur visibilit� durant
	la phase de jeu. Pour cel� utilisez les touches A ou E pour faire pivoter 		vers la gauche ou la droite. Le plateau se repositionnera en position 		initiale en appuyantsur la touche R.


