#include "Kase.h"

using namespace std;

Kase::Kase() : m_ligne(0), m_colonne(0), m_pion(NULL)
{
}

Kase::Kase(int ligne, int colonne) : m_ligne(ligne), m_colonne(colonne), m_pion(NULL)
{
}

Kase::Kase(int ligne, int colonne, int couleur, int forme, int taille, int trou) : m_ligne(ligne), m_colonne(colonne)
{
    m_pion = new Pion(couleur, forme, taille, trou);
}

Kase::Kase(const Kase &kaseACopier) : m_ligne(kaseACopier.m_ligne), m_colonne(kaseACopier.m_colonne)
{
    m_pion = new Pion(*(kaseACopier.m_pion));
}

Kase::~Kase()
{
    delete m_pion;
}

Kase Kase::operator=(const Kase &kase)
{
    delete m_pion;
    m_pion = new Pion(*(kase.m_pion));
    m_ligne = kase.m_ligne;
    m_colonne = kase.m_colonne;
    return *this;
}

Pion* Kase::getPion() const /*Attention quand retourne NULL*/
{
    return m_pion;
}

int Kase::getColonne() const
{
    return m_colonne;
}

int Kase::getLigne() const
{
    return m_ligne;
}

void Kase::setLigne(int ligne)
{
    m_ligne = ligne;
}

void Kase::setColonne(int colonne)
{
    m_colonne = colonne;
}

void Kase::setPion(Pion &pion)
{
    delete m_pion;
    m_pion = new Pion(pion.getCouleur(), pion.getForme(), pion.getTaille(), pion.getTrou());
}

void Kase::setPion()
{
    delete m_pion;
    m_pion = NULL;
}

bool Kase::vide()
{
    if(m_pion == NULL) return true;
    return false;
}

bool Kase::pleine()
{
    if(m_pion != NULL) return true;
    return false;
}

void Kase::afficher()
{
    if(vide()) cout<<"    ";
    else cout<<*m_pion;
}

ostream &operator<<(ostream &out, Kase &kase)
{
    if(kase.vide())
    {
        out<<"    ";
        return out;
    }
    out<<*(kase.getPion());
    return out;
}
