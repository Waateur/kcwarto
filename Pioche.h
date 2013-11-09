#ifndef PIOCHE_H_INCLUDED
#define PIOCHE_H_INCLUDED

#include "Pion.h"
#define TAILLE 16

class Pioche
{
    protected :
    Pion* m_pioche;
    int m_taille;

    public :

    Pioche();
    Pioche(int taille);
    Pioche(const Pioche &pioche);
    ~Pioche();
    void afficher();
    Pion prendrePion(int position);
    void remettrePion(Pion &pion, int position);
    Pion getPion(int position) const;
    int getTaille() const;
};


#endif // PIOCHE_H_INCLUDED
