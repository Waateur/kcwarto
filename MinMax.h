#ifndef MINMAX_H_INCLUDED
#define MINMAX_H_INCLUDED

#include "Plateau.h"
#include "Pioche.h"
#include "Coup.h"

/* fonction d'evaluation */
int evaluation(bool etatMax, Plateau &plateauDeJeu);
/* fonction valeur min max reccursive */
int valeurMinMax(Coup &coup, bool etatMax, Plateau &plateau, Pioche &pioche, int pMax, int alpha, int beta);
/* fonction decidant du coup a jouer pour l'ordinateur */
Coup decisionMinMax(Pion &pionEnMain, Plateau &plateau, Pioche &pioche, int pMax);

#endif // MINMAX_H_INCLUDED
