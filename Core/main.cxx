#include "Jeu.h"
#include "Menu.h"

using namespace std;

int main()
{
	int choixPrincipal = 0;
	while(choixPrincipal != 4)
	{
		choixPrincipal = menuPrincipal();
		Jeu jeu;
		switch(choixPrincipal)
		{
			case 1 :
			bool ordiDepart;
			int pMax;
			menuSolo(ordiDepart, pMax);
			jeu.hanSolo(ordiDepart, pMax);
			break;
			
			case 2 :
			menuDuo();
			jeu.leilaDuo();
			break;
			
			case 3 :
			cout<<"Dommage pour toi !!!!"<<endl;
			break;
			
			case 4 :
			cout<<"Au revoir..."<<endl;
			return 0;
			break;
			
			default :
			break;
		}
	}	
	return 0;
}
