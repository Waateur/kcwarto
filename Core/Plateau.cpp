#include "Plateau.h"

using namespace std;

Plateau::Plateau()
{
    m_plateau = new Kase*[N];
    for(int i = 0; i < N; i++) m_plateau[i] = new Kase[N];
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            m_plateau[i][j].setLigne(i);
            m_plateau[i][j].setColonne(j);
        }
    }
}

Plateau::~Plateau()
{
    for(int i = 0; i < N; i++) delete[] m_plateau[i];
    delete[] m_plateau;
}

void Plateau::poserPion(int ligne, int colonne, Pion &pion)
{
    m_plateau[ligne][colonne].setPion(pion);
}

Pion Plateau::enleverPion(int ligne, int colonne)
{
    Pion pionAEnlever = *m_plateau[ligne][colonne].getPion();
    m_plateau[ligne][colonne].setPion();
    return pionAEnlever;
}

void Plateau::afficher()
{
    cout<<endl<<"  |   1  |   2  |   3  |   4  |"<<endl;
    cout<<"__|______|______|______|______|"<<endl;
    cout<<"  |      |      |      |      |"<<endl;
    for(int i = 0; i < N; i++)
    {
        cout<<i + 1<<" | ";
        for(int j = 0; j < N; j++)
        {
            cout<<m_plateau[i][j]<<" | ";
        }
        cout<<endl<<"__|______|______|______|______|"<<endl;
        cout<<"  |      |      |      |      |"<<endl;
    }
}

bool Plateau::casePleine(int ligne, int colonne)
{
    if(m_plateau[ligne][colonne].pleine()) return true;
    return false;
}

bool Plateau::caseVide(int ligne, int colonne)
{
    if(m_plateau[ligne][colonne].vide()) return true;
    return false;
}
Kase Plateau::getKase(int ligne , int colonne )
{
	return (m_plateau[ligne][colonne]);

}


bool Plateau::lignePleine(int ligne)
{
    for(int j = 0; j < N; j++)
    {
        if(m_plateau[ligne][j].vide()) return false;
    }
    return true;
}

bool Plateau::colonnePleine(int colonne)
{
    for(int i = 0; i < N; i++)
    {
        if(m_plateau[i][colonne].vide()) return false;
    }
    return true;
}

bool Plateau::diag1Pleine()
{
    for(int i = 0; i < N; i++)
    {
        if(m_plateau[i][i].vide()) return false;
    }
    return true;
}

bool Plateau::diag2Pleine()
{
    for(int i = 0; i < N; i++)
    {
        if(m_plateau[i][N - 1 - i].vide()) return false;
    }
    return true;
}

bool Plateau::testLigne(int ligne)
{
	if(!lignePleine(ligne)) return false;
    int couleur = 0, forme = 0, taille = 0, trou = 0;
    for(int j = 0; j < N; j++)
    {
        couleur += m_plateau[ligne][j].getPion()->getCouleur();
        forme += m_plateau[ligne][j].getPion()->getForme();
        taille += m_plateau[ligne][j].getPion()->getTaille();
        trou += m_plateau[ligne][j].getPion()->getTrou();
    }
    if( (couleur%4) == 0 || (forme%4) == 0 || (taille%4) == 0 || (trou%4) == 0) return true;
    return false;
}

bool Plateau::testColonne(int colonne)
{
	if(!colonnePleine(colonne)) return false;
    int couleur = 0, forme = 0, taille = 0, trou = 0;
    for(int i = 0; i < N; i++)
    {
        couleur += m_plateau[i][colonne].getPion()->getCouleur();
        forme += m_plateau[i][colonne].getPion()->getForme();
        taille += m_plateau[i][colonne].getPion()->getTaille();
        trou += m_plateau[i][colonne].getPion()->getTrou();
    }
    if( (couleur%4) == 0 || (forme%4) == 0 || (taille%4) == 0 || (trou%4) == 0) return true;
    return false;
}

bool Plateau::testDiag1()
{
	if(!diag1Pleine()) return false;
    int couleur = 0, forme = 0, taille = 0, trou = 0;
    for(int i = 0; i < N; i++)
    {
        couleur += m_plateau[i][i].getPion()->getCouleur();
        forme += m_plateau[i][i].getPion()->getForme();
        taille += m_plateau[i][i].getPion()->getTaille();
        trou += m_plateau[i][i].getPion()->getTrou();
    }
    if( (couleur%4) == 0 || (forme%4) == 0 || (taille%4) == 0 || (trou%4) == 0) return true;
    return false;
}

bool Plateau::testDiag2()
{
	if(!diag2Pleine()) return false;
    int couleur = 0, forme = 0, taille = 0, trou = 0;
    for(int i = 0; i < N; i++)
    {
        couleur += m_plateau[i][N - 1 - i].getPion()->getCouleur();
        forme += m_plateau[i][N -1 - i].getPion()->getForme();
        taille += m_plateau[i][N -1 - i].getPion()->getTaille();
        trou += m_plateau[i][N -1 - i].getPion()->getTrou();
    }
    if( (couleur%4) == 0 || (forme%4) == 0 || (taille%4) == 0 || (trou%4) == 0) return true;
    return false;
}

int Plateau::connexiteLigne(int ligne)
{

			/* initialisation des variables */
		/**
		 * Tableau de caracteristique
		 * couleur => 0 , forme => 1, taille => 2, trou=>3;
		 */
		int carac[4];
		int nbCasesPleine = 0;
		/* nombre de caracteristique communes */
		int carCom = 0 ;
		/* on identifie les caracteristique communes et le nombres de cases pleines  */
		for(int i = 0; i < N; i ++)
		{
			if(casePleine(ligne, i))
			{
				nbCasesPleine ++;
				if(nbCasesPleine == 1) /* initialisation des caracteristiques */
				{
					carac[0] = getKase(ligne,i).getPion()->getCouleur();
					carac[1] = getKase(ligne,i).getPion()->getForme();
					carac[2] = getKase(ligne,i).getPion()->getTaille();
					carac[3] = getKase(ligne,i).getPion()->getTrou();
				}
				/* si valeur non commune  carac = -1  sinon  carac vaut la valeur commune  */
				else
				{
					if(getKase(ligne,i).getPion()->getCouleur() != carac[0]) carac[0] = -1;
					if(getKase(ligne,i).getPion()->getForme() != carac[1]) carac[1] = -1;
					if(carac[2] != getKase(ligne,i).getPion()->getTaille()) carac[2] = -1;
					if(carac[3] != getKase(ligne,i).getPion()->getTrou()) carac[3] = -1;
				}
			}

		}
		/* si la ligne ne contient pas au moins deux pions, retourne 0  */
		if(nbCasesPleine <= 1) return 0;
		/*  parcour de carac pour connaitre le nombre de Caracs communes ) */
		for(int j =0 ; j<4 ; j++ ){
			if(carac[j]!=-1 ){
				carCom++;
			}
		}
		return carCom;
}

int Plateau::connexiteColonne(int colonne)
{

			/* initialisation des variables */
		/**
		 * Tableau de caracteristique
		 * couleur => 0 , forme => 1, taille => 2, trou=>3;
		 */
		int carac[4];
		int nbCasesPleine = 0;
		/* nombre de caracteristique communes */
		int carCom = 0 ;
		/* on identifie les caracteristique communes et le nombres de cases pleines  */
		for(int i = 0; i < N; i ++)
		{
			if(casePleine(i, colonne))
			{
				nbCasesPleine ++;
				if(nbCasesPleine == 1) /* initialisation des caracteristiques */
				{
					carac[0] = getKase(i, colonne).getPion()->getCouleur();
					carac[1] = getKase(i, colonne).getPion()->getForme();
					carac[2] = getKase(i, colonne).getPion()->getTaille();
					carac[3] = getKase(i, colonne).getPion()->getTrou();
				}
				/* si valeur non commune  carac = -1  sinon  carac vaut la valeur commune  */
				else
				{
					if(getKase(i, colonne).getPion()->getCouleur() != carac[0]) carac[0] = -1;
					if(getKase(i, colonne).getPion()->getForme() != carac[1]) carac[1] = -1;
					if(carac[2] != getKase(i, colonne).getPion()->getTaille()) carac[2] = -1;
					if(carac[3] != getKase(i, colonne).getPion()->getTrou()) carac[3] = -1;
				}
			}

		}
		/* si la colonne ne contient pas au moins deux pions, retourne 0  */
		if(nbCasesPleine <= 1) return 0;
		/*  parcour de carac pour connaitre le nombre de Caracs communes ) */
		for(int j =0 ; j<4 ; j++ ){
			if(carac[j]!=-1 ){
				carCom++;
			}
		}
		return carCom;
}

int Plateau::connexiteDiag1()
{

			/* initialisation des variables */
		/**
		 * Tableau de caracteristique
		 * couleur => 0 , forme => 1, taille => 2, trou=>3;
		 */
		int carac[4];
		int nbCasesPleine = 0;
		/* nombre de caracteristique communes */
		int carCom = 0 ;
		/* on identifie les caracteristique communes et le nombres de cases pleines  */
		for(int i = 0; i < N; i ++)
		{
			if(casePleine(i, i))
			{
				nbCasesPleine ++;
				if(nbCasesPleine == 1) /* initialisation des caracteristiques */
				{
					carac[0] = getKase(i, i).getPion()->getCouleur();
					carac[1] = getKase(i, i).getPion()->getForme();
					carac[2] = getKase(i, i).getPion()->getTaille();
					carac[3] = getKase(i, i).getPion()->getTrou();
				}
				/* si valeur non commune  carac = -1  sinon  carac vaut la valeur commune  */
				else
				{
					if(getKase(i, i).getPion()->getCouleur() != carac[0]) carac[0] = -1;
					if(getKase(i, i).getPion()->getForme() != carac[1]) carac[1] = -1;
					if(carac[2] != getKase(i, i).getPion()->getTaille()) carac[2] = -1;
					if(carac[3] != getKase(i, i).getPion()->getTrou()) carac[3] = -1;
				}
			}

		}
		/* si la diagonnale ne contient pas au moins deux pions, retourne 0  */
		if(nbCasesPleine <= 1) return 0;
		/*  parcour de carac pour connaitre le nombre de Caracs communes ) */
		for(int j =0 ; j<4 ; j++ ){
			if(carac[j]!=-1 ){
				carCom++;
			}
		}
		return carCom;
}

int Plateau::connexiteDiag2()
{

			/* initialisation des variables */
		/**
		 * Tableau de caracteristique
		 * couleur => 0 , forme => 1, taille => 2, trou=>3;
		 */
		int carac[4];
		int nbCasesPleine = 0;
		/* nombre de caracteristique communes */
		int carCom = 0 ;
		/* on identifie les caracteristique communes et le nombres de cases pleines  */
		for(int i = 0; i < N; i ++)
		{
			if(casePleine(i, N-1-i))
			{
				nbCasesPleine ++;
				if(nbCasesPleine == 1) /* initialisation des caracteristiques */
				{
					carac[0] = getKase(i, N-1-i).getPion()->getCouleur();
					carac[1] = getKase(i, N-1-i).getPion()->getForme();
					carac[2] = getKase(i, N-1-i).getPion()->getTaille();
					carac[3] = getKase(i, N-1-i).getPion()->getTrou();
				}
				/* si valeur non commune  carac = -1  sinon  carac vaut la valeur commune  */
				else
				{
					if(getKase(i, N-1-i).getPion()->getCouleur() != carac[0]) carac[0] = -1;
					if(getKase(i, N-1-i).getPion()->getForme() != carac[1]) carac[1] = -1;
					if(carac[2] != getKase(i, N-1-i).getPion()->getTaille()) carac[2] = -1;
					if(carac[3] != getKase(i, N-1-i).getPion()->getTrou()) carac[3] = -1;
				}
			}

		}
		/* si la diagonnale ne contient pas au moins deux pions, retourne 0  */
		if(nbCasesPleine <= 1) return 0;
		/*  parcour de carac pour connaitre le nombre de Caracs communes ) */
		for(int j =0 ; j<4 ; j++ ){
			if(carac[j]!=-1 ){
				carCom++;
			}
		}
		return carCom;
}

int Plateau::connexite()
{
    int connexite = 0;
    for(int i = 0; i < N; i++)
    {
        connexite += connexiteLigne(i) + connexiteColonne(i);
    }
    connexite += connexiteDiag1() + connexiteDiag2();
    return (100 + connexite);
}

/* evaluation des situations gagnantes nulles ou autres : retourne 200 si ganant, 199 si nul, 100 sinon */
int Plateau::evalGagne()
{
    /* initialisation des variables pour compter le nombre de lignes et de colonnes pleines, afin de traiter le cas de match nul */
    int nombreLignesPleines = 0, nombreColonnesPleines = 0;
    /*traitement des cas gagnants et comptage des lignes et colonnes pleines */
    for(int i = 0; i < N; i++)
    {
        if(lignePleine(i))
        {
            if(testLigne(i)) return 200;
            else nombreLignesPleines ++;
        }
        if(colonnePleine(i))
        {
            if(testColonne(i)) return 200;
            else nombreColonnesPleines ++;
        }
    }
    /* traitement des cas gagnants avec les diagonnales */
    if(testDiag1() || testDiag2()) return 200;
    /* traitement du cas du match nul */
    if((nombreLignesPleines + nombreColonnesPleines) == 8) return 199;
    /* Dans les autres cas on renvoie 100 */
    else return 100;
}

/* evaluation des situations gagnantes nulles ou autre en fonction d'une position max ou min */
int Plateau::eval(bool etatMax)
{
    /* si position max, on retourne la valeur de evalGagne */
    if(etatMax) return evalGagne();
    /* si position min, on retourne le complement a 200 de la valeur de evalGagne */
    else return (200 - evalGagne());
}
