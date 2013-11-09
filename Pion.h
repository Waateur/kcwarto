#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include <iostream>

class Pion
{
    protected :

    int m_couleur;
    int m_forme;
    int m_taille;
    int m_trou;

    public :

    Pion();
    Pion(int couleur, int forme, int taille, int trou);
    Pion(const Pion &pion);
    Pion operator=(const Pion &pion);
    void afficher();
    int getCouleur() const;
    int getForme() const;
    int getTaille() const;
    int getTrou() const;
};

std::ostream &operator<<(std::ostream &out, Pion &pion);

#endif // PION_H_INCLUDED
