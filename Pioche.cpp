#include "Pioche.h"

using namespace std;

Pioche::Pioche() : m_taille(TAILLE)
{
    m_pioche = new Pion[m_taille];
    int n = 0;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                for(int l = 0; l < 2; l++)
                {
                    Pion pion(i, j, k, l);
                    m_pioche[n] = pion;
                    n++;
                }
            }
        }
    }
}

Pioche::Pioche(int taille) : m_taille(taille)
{
    m_pioche = new Pion[m_taille];
}

Pioche::Pioche(const Pioche &pioche)
{
    m_taille = pioche.m_taille;
    m_pioche = new Pion[m_taille];
    for(int i = 0; i < m_taille; i ++)
    {
        m_pioche[i] = pioche.m_pioche[i];
    }
}


Pioche::~Pioche()
{
    delete[] m_pioche;
}

void Pioche::afficher()
{
	if(m_taille > 8){
		for(int n = 0; n < 8; n++) cout<<n+1<<": "<<m_pioche[n]<<" | ";
		cout<<endl;
		for(int n = 8; n < m_taille; n++) cout<<n+1<<": "<<m_pioche[n]<<" | ";
	}
	else{
		for(int n = 0; n < m_taille; n++) cout<<n+1<<": "<<m_pioche[n]<<" | ";
	}
}

Pion Pioche::prendrePion(int position)
{
    Pion pion(m_pioche[position]);
    Pion *nouvellePioche = new Pion[m_taille-1];
    for(int i = 0; i < (position); i++) nouvellePioche[i] = m_pioche[i];
    for(int i = (position); i < (m_taille - 1); i++) nouvellePioche[i] = m_pioche[i + 1];
    m_taille--;
    delete[] m_pioche;
    m_pioche = new Pion[m_taille];
    for(int i = 0; i < m_taille; i++) m_pioche[i] = nouvellePioche[i];
    delete[] nouvellePioche;
    return pion;
}

void Pioche::remettrePion(Pion &pion, int position)
{
    Pion *nouvellePioche = new Pion[m_taille+1];
    for(int i = 0; i < (position); i++) nouvellePioche[i] = m_pioche[i];
    nouvellePioche[position] = pion;
    for(int i = position ; i < m_taille ; i++) nouvellePioche[i + 1] = m_pioche[i];
    m_taille++;
    delete[] m_pioche;
    m_pioche = new Pion[m_taille];
    for(int i = 0; i < m_taille; i++) m_pioche[i] = nouvellePioche[i];
    delete[] nouvellePioche;
}

Pion Pioche::getPion(int position) const
{
    return m_pioche[position];
}

int Pioche::getTaille() const
{
    return m_taille;
}
