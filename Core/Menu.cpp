#include "Menu.h"

using namespace std;

int menuPrincipal()
{
		cout<<endl<<endl<<endl<<endl<<endl;	
	cout<<"		 ########  #        # ########## ########## ##########  ######## "<<endl;
	cout<<"		#        # #        # #        # #        #     #      #        #"<<endl;
	cout<<"		#        # #        # #        # #        #     #      #        #"<<endl;
	cout<<"		#     #  # #        # ########## #########      #      #        #"<<endl;
	cout<<"		#      # # #        # #        # #       #      #      #        #"<<endl;
	cout<<"		 ########  ########## #        # #        #     #       ######## "<<endl;
	cout<<endl<<endl<<endl<<endl<<endl;

	cout<<"			1: Joue Contre Han		2: si tu as un ami"<<endl;
	cout<<"			3: si ton ami est loin		4: si je te saoule"<<endl;
	cout<<endl<<endl;
	cout<<"Vas y je t'ecoute ! :";
	int choix = 0;
	while(choix < 1 || choix > 4)
	{
		string saisieChoix;
		cin>>saisieChoix;
		istringstream buffer(saisieChoix);
		buffer >> choix;
	}
	return choix;
}

void menuSolo(bool &ordiDepart, int &pMax)
{
	pMax = 0;
	cout<<endl<<endl<<"Niveau de difficulte entre 1 et 4 : ";
	while(pMax < 1 || pMax > 5)
	{
		string saisieChoix;
		cin>>saisieChoix;
		istringstream buffer(saisieChoix);
		buffer >> pMax;
	}
	pMax --;
	cout<<endl<<"Vous avez choisi le niveau "<<pMax+1<<endl<<endl;
	cout<<"Qui commence ? (1 : ordinateur  2 : vous)";
	int choix = 0;
	while(choix < 1 || choix > 2)
	{
		string saisieChoix;
		cin>>saisieChoix;
		istringstream buffer(saisieChoix);
		buffer >> choix;
	}
	if(choix == 1) ordiDepart = true;
	else ordiDepart = false;
}

void menuDuo()
{
	cout<<endl<<endl<<"Le joueur 1 commence en choisissant un pion pour son adversaire"<<endl<<endl;
}
