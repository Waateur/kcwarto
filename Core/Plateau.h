#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include "Kase.h"
#define N 4

class Plateau
{
    protected :

    Kase** m_plateau;

    public :

    Plateau();
    ~Plateau();
    void poserPion(int ligne, int colonne, Pion &pion);
    Pion enleverPion(int ligne, int colonne);
    void afficher();
    bool casePleine(int ligne, int colonne);
    bool caseVide(int ligne, int colonne);
	Kase getKase(int, int);
    bool lignePleine(int ligne);
    bool colonnePleine(int colonne);
    bool diag1Pleine();
    bool diag2Pleine();
    bool testLigne(int ligne);
    bool testColonne(int colonne);
    bool testDiag1();
    bool testDiag2();
    int connexiteLigne(int ligne);
    int connexiteColonne(int colonne);
    int connexiteDiag1();
    int connexiteDiag2();
    int connexite();
    int evalGagne();
    int eval(bool etatMax);
};


#endif // PLATEAU_H_INCLUDED
