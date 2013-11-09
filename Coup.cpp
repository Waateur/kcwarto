#include "Coup.h"


using namespace std;

Coup::Coup(int ligne, int colonne, Pion &pion) : m_ligne(ligne), m_colonne(colonne)
{
    m_pion = pion;
    m_position = -1;
}

Coup::Coup(const Coup &coup)
{
    m_ligne = coup.m_ligne;
    m_colonne = coup.m_colonne;
    m_pion = coup.m_pion;
    m_position = -1;
}

int Coup::getLigne() const
{
    return m_ligne;
}

int Coup::getColonne() const
{
    return m_colonne;
}

Pion Coup::getPion() const
{
    return m_pion;
}

int Coup::getPosition() const
{
    return m_position;
}

void Coup::setLigne(int ligne)
{
    m_ligne = ligne;
}

void Coup::setColonne(int colonne)
{
    m_colonne = colonne;
}

void Coup::setPion(Pion &pion)
{
    m_pion = pion;
}

void Coup::setPosition(int position)
{
    m_position = position;
}
