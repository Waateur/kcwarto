#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
/*!
 * \file Jeu.h
 * \brief un tour de jeu de quarto
 * \author Cedric
 * \version 0.1
 */
#include "Plateau.h"
#include "Pioche.h"
#include "MinMax.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>



  /*! \class jeu
   * \brief la classe reprensentan un tour de  Jeu
   *
   *  La classe gere les deux tour de jeux
   */
class Jeu
{
	/*pion pour la gestion du jeu avec l'interface*/
	Pion pionSequence;

	Plateau m_plateau;
	Pioche m_pioche;

	public :
	 /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Jeu
     */
	Jeu();
	 /*!
     *  \brief Destructeur
     *
     *  Destructeur de la classe Jeu
     */
	~Jeu();
	 /*!
     *  \brief Afficher Jeu
     *
     *  Affiche la pioche et le plateau suivant
     */
	void afficher();
	void afficherPlateau();


	/*!
     *  \brief Selectionne un  pion
     *
     *  Methode qui permet a un joueur de choisir un pion
     *  \return le premier Pion choisis ;
     *
     */
	Pion selectionPion(int & numeroJoueur, bool &nul);
	int tourDeJeu(Pion,int &);
	bool phaseTest(int , int, int& objetGagnant);
	/*!
     *  \brief evalue un ligne
     *
     *  Methode qui permet evaluer un ligne et
     *
     *  \param ligne : le numero de la ligne à evaluer
     *  \return la note attribuer à la ligne
     *
     */
    int tourDeJeuUnJoueur(Pion &pionEnJeu ,int &numeroJoueur);
    int tourDeJeuOrdinateur(Pion &pionEnJeu, int &numeroJoueur, bool &, int);
	void hanSolo(bool, int);
	void leilaDuo();

/***************************************************/
/*Methodes pour gerer l'interfacage avec le moteur */
/***************************************************/

/*
 * recupere le pion dans la pioche en position passee en parametre
 * @param position la position prealablement verifiee .
*/
	void interfaceSelectionPion(int&);
	bool interfacePoserPion(int&, int&, int& objetGagnant);
	int OrdiPoserPion(int& ligne, int& colonne, int pMax, int& objetGagnant);
};

#endif
