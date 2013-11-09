#include "Jeu.h"

using namespace std;

Jeu::Jeu()
{
}

Jeu::~Jeu()
{
}

void Jeu::afficher()
{
	m_plateau.afficher();
	m_pioche.afficher();
}

void Jeu::afficherPioche()
{
	m_pioche.afficher();
}

void Jeu::afficherPlateau()
{
	m_plateau.afficher();
}

Pion Jeu::selectionPion(int & numeroJoueur, bool &nul)
{
		Pion pionEnJeu;
		if(m_pioche.getTaille() == 0)
		{
		    nul = true;
		    numeroJoueur = -1;
		    return pionEnJeu;
		}
        int numeroPiece = 0;
        cout<<endl<<"Voici la pioche : "<<endl<<endl;
        m_pioche.afficher();
        while(numeroPiece < 1 || numeroPiece > m_pioche.getTaille())
        {
            string saisie;
            cout<<endl<<endl<<"Joueur"<<(numeroJoueur%2) +1<<" choisissez une piece pour votre adversaire : "<<endl;
            cin>>saisie;
            istringstream buffer(saisie);
            buffer >> numeroPiece;
        }
		numeroPiece--;
        pionEnJeu = m_pioche.prendrePion(numeroPiece);
        cout<<endl<<"Vous avez choisi la piece : "<<pionEnJeu<<endl;
        numeroJoueur++;
        return pionEnJeu;
}

int Jeu::tourDeJeu(Pion pionEnJeu ,int & numeroJoueur)
{
    if(numeroJoueur == -1) return -1;
	int ligne , colonne, objetGagnant = 0;
	do
	{
		ligne = 0;
		colonne = 0;
		cout<<endl<<"Voici le plateau :"<<endl<<endl;
		m_plateau.afficher();
		cout<<endl<<"Voici la piece que votre adversaire a choisie : "<<pionEnJeu<<endl;
		cout<<endl<<"Joueur"<<(numeroJoueur%2)+1<<" donnez une ligne et une colonne ou placer le pion :"<<endl;
		while(ligne < 1 || ligne > 4)
		{
		    string saisieLigne;
			cout<<endl<<"Ligne :";
			cin>>saisieLigne;
            istringstream buffer(saisieLigne);
            buffer >> ligne;
		}
		while(colonne < 1 || colonne > 4)
		{
		    string saisieColonne;
			cout<<endl<<"Colonne :";
			cin>>saisieColonne;
            istringstream buffer(saisieColonne);
            buffer >> colonne;
		}
		ligne--;
		colonne--;
	} while(m_plateau.casePleine(ligne, colonne));
	m_plateau.poserPion(ligne, colonne, pionEnJeu);
	cout<<endl<<"Voici le plateau :"<<endl<<endl;
	m_plateau.afficher();
	cout<<endl<<endl;
	if(phaseTest(ligne,colonne, objetGagnant)){
		cout<<endl<<"Bravo joueur "<<(numeroJoueur%2)+1;
		return -1;
	}
	else
	{
	return numeroJoueur;
	}
}


/* objetGagnant vaut :
    0 si c'est une ligne
    1 si c'est une colonne
    2 si c'est la premiere diagonnale
    3 si c'est la deuxieme diagonnale*/
bool Jeu::phaseTest(int ligne, int colonne, int& objetGagnant)
{
	if(m_plateau.lignePleine(ligne))
	{
		if(m_plateau.testLigne(ligne))
		{
			cout<<endl<<"La ligne "<<ligne + 1<<" est gagnante !!!"<<endl<<endl;
			objetGagnant = 0;
			return true;
		}
	}if(m_plateau.colonnePleine(colonne))
	{
		if(m_plateau.testColonne(colonne))
		{
			cout<<endl<<"La colonne "<<colonne + 1<<" est gagnante !!!"<<endl<<endl;
			objetGagnant = 1;
			return true;
		}
	}
	if(ligne == colonne)
	{
		if(m_plateau.diag1Pleine())
		{
			if(m_plateau.testDiag1())
			{
				cout<<endl<<"La premiere diagonnale est gagnante !!!"<<endl<<endl;
				objetGagnant = 2;
				return true;
			}
		}
	}
		if((ligne + colonne) == N -1)
	{
		if(m_plateau.diag2Pleine())
		{
			if(m_plateau.testDiag2())
			{
				cout<<endl<<"La deuxieme diagonnale est gagnante !!!"<<endl<<endl;
				objetGagnant = 3;
				return true;
			}
		}
	}
	return false ;
}

int Jeu::tourDeJeuOrdinateur(Pion &pionEnJeu, int &numeroJoueur, bool &nul, int pMax)
{
    if(numeroJoueur == -1) return -1;
    int ligne, colonne, position, objetGagnant, taillePioche = m_pioche.getTaille();
    if(taillePioche != 0)
    {
        Coup coup = decisionMinMax(pionEnJeu, m_plateau, m_pioche, pMax);
        ligne = coup.getLigne();
        colonne = coup.getColonne();
        position = coup.getPosition();
    }
    else
    {
        for(int i = 0; i < N; i ++)
        {
            for(int j = 0; j < N; j++)
            {
                if(m_plateau.caseVide(i, j))
                {
                    ligne = i;
                    colonne = j;
                }
            }
        }
    }
    cout<<endl<<endl<<"L'ordinateur joue la ligne "<<ligne + 1<<" et la colonne "<<colonne + 1<<endl<<endl;
	cout<<endl;
    m_plateau.poserPion(ligne, colonne, pionEnJeu);
	cout<<endl<<"Voici le plateau :"<<endl<<endl;
    m_plateau.afficher();
    if(phaseTest(ligne,colonne, objetGagnant)){
		return -1;
	}
	if(taillePioche == 0)
	{
	    nul = true;
	    return -1;
	}
	pionEnJeu = m_pioche.prendrePion(position);
	numeroJoueur --;
	return numeroJoueur;
}

int Jeu::tourDeJeuUnJoueur(Pion &pionEnJeu ,int & numeroJoueur)
{
    if(numeroJoueur == -1) return -1;
	int ligne , colonne, objetGagnant;
	do
	{
		ligne = 0;
		colonne = 0;
		cout<<endl<<"Voici la piece que l'ordinateur a choisie : "<<pionEnJeu<<endl;
		cout<<endl<<"Voici la pioche : "<<endl<<endl;
        m_pioche.afficher();
		cout<<endl<<endl<<"Joueur"<<(numeroJoueur%2)+1<<" donnez une ligne et une colonne ou placer le pion :"<<endl;
		while(ligne < 1 || ligne > 4)
		{
			string saisieLigne;
			cout<<endl<<"Ligne :";
			cin>>saisieLigne;
            istringstream buffer(saisieLigne);
            buffer >> ligne;
		}
		while(colonne < 1 || colonne > 4)
		{
			string saisieColonne;
			cout<<endl<<"Colonne :";
			cin>>saisieColonne;
            istringstream buffer(saisieColonne);
            buffer >> colonne;
		}
		ligne--;
		colonne--;
	} while(m_plateau.casePleine(ligne, colonne));
	m_plateau.poserPion(ligne, colonne, pionEnJeu);
	cout<<endl<<"Voici le plateau :"<<endl<<endl;
	m_plateau.afficher();
	cout<<endl<<endl;
	if(phaseTest(ligne,colonne, objetGagnant)){
		return -1;
	}
	else
	{
	return numeroJoueur;
	}
}

void Jeu::hanSolo(bool ordiDepart, int pMax)
{
	bool nul = false;
	bool ordiGagne = false;
	int joueur =0 ;
	if(ordiDepart)
	{
		ordiDepart = false;
		srand(time(NULL));
		int position = (int)((float) rand() / RAND_MAX * (16));
		Pion pionSelection = m_pioche.prendrePion(position);
		cout<<endl<<"Voici le plateau :"<<endl<<endl;
		m_plateau.afficher();
		tourDeJeuUnJoueur(pionSelection, joueur);
	}
	while(joueur != -1){
	Pion pionSelection = selectionPion(joueur, nul);
	joueur = tourDeJeuOrdinateur(pionSelection, joueur, nul, pMax);
	if(joueur == -1 && !nul)
	{
	     ordiGagne = true;
	}
	joueur = tourDeJeuUnJoueur(pionSelection, joueur);
    }
    if(nul) cout<<endl<<endl<<"Match nul !!!"<<endl;
	else if(ordiGagne) cout<<endl<<endl<<"L'ordi gagne !!!"<<endl;
    else cout<<endl<<"Bravo joueur vous avez battu l'ordi !!!"<<endl;
}

void Jeu::leilaDuo()
{
	bool nul = false;
	afficherPlateau();
	int joueur =0 ;
	while(joueur != -1){
		Pion pionSelection = selectionPion(joueur, nul);
		joueur = tourDeJeu(pionSelection,joueur);
	}
	if(nul) cout<<endl<<endl<<"Match nul !!!"<<endl;
	else cout<<", vous avez gagne !!!!!!"<<endl<<endl;
}

/***************************************************/
/*Methodes pour gerer l'interfacage avec le moteur */
/***************************************************/

void Jeu::interfaceSelectionPion(int& position)
{
	pionSequence = m_pioche.prendrePion(position);
}

bool Jeu::interfacePoserPion(int& ligne, int& colonne, int& objetGagnant)
{
	m_plateau.poserPion(ligne, colonne, pionSequence);
	return phaseTest(ligne, colonne, objetGagnant);
}

/*ordi pose un pion*/
/*retourne la position du pion choisi dans la pioche ou -1 si l'ordi gagne ou -2 si match nul*/
int Jeu::OrdiPoserPion(int& ligne, int& colonne, int pMax, int& objetGagnant)
{
    //if(numeroJoueur == -1) return -1;
    int position, taillePioche = m_pioche.getTaille();
    if(taillePioche != 0)
    {
        Coup coup = decisionMinMax(pionSequence, m_plateau, m_pioche, pMax);
        ligne = coup.getLigne();
        colonne = coup.getColonne();
        position = coup.getPosition();
    }
    else
    {
        for(int i = 0; i < N; i ++)
        {
            for(int j = 0; j < N; j++)
            {
                if(m_plateau.caseVide(i, j))
                {
                    ligne = i;
                    colonne = j;
                }
            }
        }
    }
    cout<<endl<<endl<<"L'ordinateur joue la ligne "<<ligne + 1<<" et la colonne "<<colonne + 1<<endl<<endl;
	cout<<endl;
    m_plateau.poserPion(ligne, colonne, pionSequence);
	cout<<endl<<"Voici le plateau :"<<endl<<endl;
    m_plateau.afficher();
    if(phaseTest(ligne,colonne, objetGagnant)){
		return -1;
	}
	if(taillePioche == 0)
	{
	    //nul = true;
	    return -2 ;
	}
	pionSequence = m_pioche.prendrePion(position);
	//numeroJoueur --;
	return position;
}




