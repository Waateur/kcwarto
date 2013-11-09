#include "MinMax.h"

using namespace std;

/* fonction d'evaluation */
int evaluation(bool etatMax, Plateau &plateauDeJeu)
{
    /* on fait la moyenne entre l'evaluation du plateau et sa connexite */
    int resultat = 0.5 * plateauDeJeu.eval(etatMax) + 0.5 * plateauDeJeu.connexite();
    return resultat;
}

/* fonction valeur min max reccursive, avec coupe alpha  */
int valeurMinMax(Coup &coup, bool etatMax, Plateau &plateau, Pioche &pioche, int pMax, int alpha, int beta)
{
    /* evaluation du plateau dans la situation precedente en cas de victoire, defaite, nul ou profondeur max */
    /* utilisation de non etatMax car on evalue la situation precedente */
    int testGagne = plateau.eval(!etatMax); /* permet d'identifier les cas ganant, perdant, nul ou autre */
    int testEval = evaluation(!etatMax, plateau); /* donne la valeur du plateau a renvoyer dans un cas terminal */
    if (testGagne != 100 || pMax == 0) /* condition d'arret de la reccursivite : cas gagnant, perdant nul ou profondeur max atteinte */
    {
        return testEval;
    }
    /* evaluation de la situation courante dans un cas non terminal */
    Pion pionEnMain = coup.getPion(); /* le pion à donner contenu dans coup courant devient le pion a jouer pour l'adversaire */
    if(etatMax) /* dans une situation max on fait la coupe alpha */
    {
      for(int i = 0; i < N; i++)
      {
          for(int j = 0; j < N; j++)
          {
              if(plateau.caseVide(i, j)) /* pour chaque position libre du plateau courant */
              {
                  plateau.poserPion(i, j, pionEnMain); /* on pose le pion courant sur la position libre */
                  if(pioche.getTaille() == 0) /* gestion du cas ou il n'y a plus de pion dans la pioche */
                  {
                      int valeur = evaluation(etatMax, plateau);
                      plateau.enleverPion(i, j);
                      return valeur;
                  }
                  /* cas ou la pioche n'est pas vide */
                  for(int k = 0; k < pioche.getTaille(); k++) /* pour chaque pion restant */
                  {
                      /* on definit le coup a evaluer */
                      coup.setLigne(i);
                      coup.setColonne(j);
                      Pion nouveauPion = pioche.prendrePion(k); /* pion a donner a l'adversaire */
                      coup.setPion(nouveauPion);
                      Pioche piocheTemp = pioche; /*creation de la pioche suivante, ne contenant plus le pion choisi */
                      pioche.remettrePion(nouveauPion, k); /*remise du pion choisi dans la pioche courante */
                      /* evaluation du coup dans la situation suivante, donc non etatMax */
                      int valeur = valeurMinMax(coup, !etatMax, plateau, piocheTemp, pMax - 1, alpha, beta);
                      if(alpha < valeur) alpha = valeur; /* alpha devient le max entre alpha et valeur */
                      /* coupe alpha */
                      if(alpha >= beta)
                      {
                          /* on enleve le pion courant de la position qui vient d'etre etudiee */
                          plateau.enleverPion(i, j);
                          return alpha; /* alpha est le max des evaluations */
                      }
                  }
                  /* on enleve le pion courant de la position qui vient d'etre etudiee */
                  plateau.enleverPion(i, j);
              }
          }
      }
      return alpha; /* si on a parcouru toute la branche, alpha represente le max */
    }
    else /*si on est en situation min on fait la coupe beta */
    {
      for(int i = 0; i < N; i++)
      {
          for(int j = 0; j < N; j++)
          {
              if(plateau.caseVide(i, j)) /* pour chaque position libre du plateau courant */
              {
                  plateau.poserPion(i, j, pionEnMain); /* on pose le pion courant sur la position libre */
                  if(pioche.getTaille() == 0) /* gestion du cas ou il n'y a plus de pion dans la pioche */
                  {
                      int valeur = evaluation(etatMax, plateau);
                      plateau.enleverPion(i, j);
                      return valeur;
                  }
                  /* cas ou la pioche n'est pas vide */
                  for(int k = 0; k < pioche.getTaille(); k++) /* pour chaque pion restant */
                  {
                      /* on definit le coup a evaluer */
                      coup.setLigne(i);
                      coup.setColonne(j);
                      Pion nouveauPion = pioche.prendrePion(k); /* pion a donner a l'adversaire */
                      coup.setPion(nouveauPion);
                      Pioche piocheTemp = pioche; /*creation de la pioche suivante, ne contenant plus le pion choisi */
                      pioche.remettrePion(nouveauPion, k); /*remise du pion choisi dans la pioche courante */
                      /* evaluation du coup dans la situation suivante, donc non etatMax */
                      int valeur = valeurMinMax(coup, !etatMax, plateau, piocheTemp, pMax - 1, alpha, beta);
                      if(beta > valeur) beta = valeur; /* beta devient le min entre beta et valeur */
                      /* coupe beta  : si beta est plus petit que alpha, la recherche n'est plus necessaire*/
                      if(beta <= alpha)
                      {
                          /* on enleve le pion courant de la position qui vient d'etre etudiee */
                          plateau.enleverPion(i, j);
                          return beta; /* beta est le min des evaluations */
                      }
                  }
                  /* on enleve le pion courant de la position qui vient d'etre etudiee */
                  plateau.enleverPion(i, j);
              }
          }
      }
      return beta; /* si on a parcouru toute la branche, beta est le min */
    }
}

/* fonction decidant du coup a jouer pour l'ordinateur : position ou placer le pion courant et pion a donner a l'adversaire */
Coup decisionMinMax(Pion &pionEnMain, Plateau &plateau, Pioche &pioche, int pMax)
{
    int alpha = 0, imax, jmax, kmax;
    for(int k = 0; k < pioche.getTaille(); k++) /* pour chaque pion restant dans la pioche */
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                if(plateau.caseVide(i, j)) /* pour chaque position libre sur le plateau courant */
                {
                    plateau.poserPion(i, j, pionEnMain); /* on pose le pion courant sur la position libre */
                    Pion nouveauPion = pioche.prendrePion(k); /* pion a donner a l'adversaire */
                    Coup coup = Coup(i, j, nouveauPion); /* coup a evaluer */
                    Pioche piocheTemp = pioche; /* creation de la pioche suivante */
                    pioche.remettrePion(nouveauPion,k); /* remise du pion choisi dans la pioche actuelle */
                    /* evaluation du coup dans la situation suivante donc dans un etat min : etatMax vaut false */
                    int valeur = valeurMinMax(coup, false, plateau, piocheTemp, pMax, alpha, 200);
                    /* mise a jour de la valeur max */
                    if(valeur > alpha)
                    {
                        alpha = valeur;
                        imax = i;
                        jmax = j;
                        kmax = k;
                    }
                    /* on retire le pion en cours de la position qui vient d'etre etudiee */
                    plateau.enleverPion(i, j);
                }
            }
        }
    }
    /* definition et retour du coup qui possede la valeur max */
    Pion pionADonner = pioche.getPion(kmax);
    Coup meilleurCoup = Coup(imax, jmax, pionADonner);
    meilleurCoup.setPosition(kmax);
    return meilleurCoup;
}
