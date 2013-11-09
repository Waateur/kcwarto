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
	private:
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
    /*!
    * \brief Affiche Pioche
    *
    *  Affiche l etat de la pioche seulement
    */
    void afficherPioche();

    /*!
    * \brief Display the game s Board
    *
    * Display Only the Game Board
    */
    void afficherPlateau();

    /*!
     *  \brief Selectionne un  pion
     *  \param numeroJoueur Numero du joueur qui actione
     *  \param nul repere pour match nul ( tous les poins en jeu)
     *  Methode qui  affiche la pioche STDOU puis 
     *  permet a un joueur de choisir un pion via STDIN
     *  \return le premier Pion choisis ;
     *
     */
	Pion selectionPion(int & numeroJoueur, bool &nul);
    /*!
    * \brief  poser une pion et verifie victoire 
    * \param pion Le pion choisis par adversaire
    * \param numeroJoueur Le numero du joueur qui va agir
    * \return -1 si victoire numero du joueur sinon
    */
    int tourDeJeu(Pion pion,int & numeroJoueur);
    bool phaseTest(int , int, int& objetGagnant);
    int tourDeJeuOrdinateur(Pion &pionEnJeu, int &numeroJoueur, bool &, int);
    int tourDeJeuUnJoueur(Pion &pionEnJeu ,int & numeroJoueur);
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
