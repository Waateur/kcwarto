#include "Pion.h"

using namespace std;

Pion::Pion() : m_couleur(0), m_forme(0), m_taille(0), m_trou(0)
{
}

Pion::Pion(int couleur, int forme, int taille, int trou) : m_couleur(couleur), m_forme(forme), m_taille(taille), m_trou(trou)
{
}

Pion::Pion(const Pion &pion) : m_couleur(pion.m_couleur), m_forme(pion.m_forme), m_taille(pion.m_taille), m_trou(pion.m_trou)
{
}

Pion Pion::operator=(const Pion &pion)
{
    m_couleur = pion.m_couleur;
    m_forme = pion.m_forme;
    m_taille = pion.m_taille;
    m_trou = pion.m_trou;
    return *this;
}

void Pion::afficher()
{
    cout<<m_couleur<<m_forme<<m_taille<<m_trou;
}

int Pion::getCouleur() const
{
    return m_couleur;
}

int Pion::getForme() const
{
    return m_forme;
}

int Pion::getTaille() const
{
    return m_taille;
}

int Pion::getTrou() const
{
    return m_trou;
}

ostream &operator<<(ostream &out, Pion &pion)
{
    out<<pion.getCouleur()<<pion.getForme()<<pion.getTaille()<<pion.getTrou();
    return out;
}
