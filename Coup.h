#ifndef COUP_H_INCLUDED
#define COUP_H_INCLUDED

#include "Pion.h"


class Coup
{
    protected :

    int m_ligne;
    int m_colonne;
    Pion m_pion;
    int m_position;


    public :

    Coup(int ligne, int colonne, Pion &pion);
    Coup(const Coup &coup);
    int getLigne() const;
    int getColonne() const;
    int getPosition() const;
    Pion getPion() const;
    void setLigne(int ligne);
    void setColonne(int colonne);
    void setPion(Pion &pion);
    void setPosition(int position);
};

#endif // COUP_H_INCLUDED
