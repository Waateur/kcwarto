#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include "Pion.h"

class Kase
{
    protected :

    int m_ligne;
    int m_colonne;
    Pion *m_pion;

    public :

    Kase();
    Kase(int ligne, int colonne);
    Kase(int ligne, int colonne, int couleur, int forme, int taille, int trou);
    Kase(const Kase &kase);
    ~Kase();
    Kase operator=(const Kase &kase);
    Pion* getPion() const;
    int getLigne() const;
    int getColonne() const;
    void setLigne(int ligne);
    void setColonne(int colonne);
    void setPion(Pion &pion);
    void setPion();
    bool vide();
    bool pleine();
    void afficher();
};

std::ostream &operator<<(std::ostream &out, Kase &kase);

#endif // CASE_H_INCLUDED
