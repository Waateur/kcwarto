#include "Moteur3d.h"
#include "menu3d.h"

int main()
{
    bool quit = false;
    int scoreJ1 = 0, scoreJ2 = 0, scoreOrdi = 0, scoreJ1vsOrdi = 0;
    while(1){
        bool CPU=false;
        bool fullScreen = false;
        int pMax=0;
        Menu3d menu;
        pMax=menu.run(CPU, fullScreen, quit);
        if(quit){
            return 0;
        }
        Moteur3d moteur(fullScreen);
        moteur.initialise();
        moteur.run(scoreJ1, scoreJ2, scoreOrdi, scoreJ1vsOrdi, pMax, CPU);
   }
    return 0;
}
