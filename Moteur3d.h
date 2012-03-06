#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED


#include "MyReceiver.h"
#include "Core/Jeu.h"



// : public IEventReceiver
class Moteur3d
{
      private:
      irr::video::IVideoDriver* driver;
      irr::scene::ISceneManager* sceneMgr;
      irr::IrrlichtDevice* device;
      irr::gui::IGUIEnvironment* guiEnv;
      irr::scene::ICameraSceneNode* camera;
      irr::scene::ISceneNode* racine;
      irr::scene::ISceneNode* plateau;
      irr::scene::ISceneNode* pioche;
      irr::scene::ISceneNode** pion;
      irr::scene::IVolumeLightSceneNode * light;
      irr::core::vector3df *positionsPioche;
      irr::core::vector3df** positionsPlateau;
      MyReceiver receiver;
      irr::scene::ISceneNodeAnimator* anim;
      irr::scene::ISceneNodeAnimator* animLight;
      irr::scene::ISceneNodeAnimator* animRotat;
      irr::core::vector3df centre;
      irr::scene::ITextSceneNode * texTampon;

      /*Tableau de booleens pour memoriser les pions encore jouables*/
      bool pionDisponible[16];

    /*Matrice de booleens pour memoriser les cases vides du plateau*/
    bool caseDisponible[4][4];

    /*Tableau de correspondances pour la position d'un pion dans la pioche moteur 3d et la pioche core*/
    int correspondances[16];

    /*Jeu core*/
    Jeu jeuCore;


      public :

      Moteur3d(bool fullScreen = false);
      ~Moteur3d();
      void initialise();
      void runA();
      void run(int& scoreJ1, int& scoreJ2, int& scoreOrdi, int& scoreJ1vsOrdi, int pMax=0, bool CPUmode=false);
      void runD(int pMax=0, bool CPUmode=false);
      void deplacerPionCentre(int i);
      void finDeplacement(int i);
      void rotationPlateau(bool &rotationEncour , bool & rotationFinis, bool & reinit );
      void deplacementPlateau(int i, irr::core::vector3df kase);
      void finPlacementPlateau(int pionEnJeu);
      void deplacementBasLightPlateau(int& ligne, int& colonne);
      void deplacementDroiteLightPlateau(int& ligne, int& colonne);
      void deplacementHautLightPlateau(int& ligne, int& colonne);
      void deplacementGaucheLightPlateau(int& ligne, int& colonne);
      void deplacementHautLightPioche(int& selectionPion);
      void deplacementBasLightPioche(int& selectionPion);
      void deplacementDroiteLightPioche(int& selectionPion);
      void deplacementGaucheLightPioche(int& selectionPion);
      void majCorrespondance(int pionSelection);
      int inverseCorrespondance(int positionCore);
      void setScores(int scoreJ1, int scoreJ2, int scoreOrdi,int scoreJ1vsOrdi, irr::core::stringw& scores, irr::gui::IGUIStaticText* Ssttext, bool CPUmode);
      void play();

};

#endif //MOTEUR_H_INCLUDED
