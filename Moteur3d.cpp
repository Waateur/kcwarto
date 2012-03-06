#include "Moteur3d.h"


//#include <iostream>
/*Constructeur*/
Moteur3d::Moteur3d(bool fullScreen)
{
    /*creation du device*/
    device = irr::createDevice (
    irr::video::EDT_OPENGL,
    irr::core::dimension2d<irr::u32>(800,600),
    32,
    fullScreen,
    false,
    false,
    &receiver);//*/

    /*creation driver et scene manager et gui environement*/
    driver = device->getVideoDriver();
    sceneMgr = device->getSceneManager();
    guiEnv = device->getGUIEnvironment();

    /*Logo en haut a droite*/
    guiEnv->addImage(driver->getTexture("./images/Cwarto.png"),irr::core::position2d<int>(1,1));


    /*ajout camera*/
    /*camera = sceneMgr->addCameraSceneNodeFPS();//*/
    //camera = sceneMgr->addCameraSceneNodeMaya();//*/
    camera = sceneMgr->addCameraSceneNode(
     0,
	irr::core::vector3df(0, 610, -423),
	irr::core::vector3df(0, 0, 0)
    );    //*/

    /*Les animations pointent sur NULL au depart*/
    anim = NULL;
    animLight = NULL;

    /*Tableau pour les positions dans la pioche*/
    positionsPioche = new irr::core::vector3df[16];

    /*Matrice pour les positions sur le plateau*/
    positionsPlateau = new irr::core::vector3df*[4];
    for(int i = 0; i<4; i++){
            positionsPlateau[i] = new irr::core::vector3df[4];
    }


}

/*Destructeur*/
Moteur3d::~Moteur3d()
{
    //device->drop();
}

/*Initialisation des attributs*/
void Moteur3d::initialise()
{

    /*Creation d'un noeud vide pour la racine*/
    racine = sceneMgr->addEmptySceneNode();

    /*La racine est en position centrale*/
    racine->setPosition(irr::core::vector3df(0, 0, 0));

    /*Creation du plateau*/
    plateau = sceneMgr->addCubeSceneNode(240.0f,
		 0,
	    -1,
		irr::core::vector3df(0, 0, 0),
		irr::core::vector3df(0, 0, 0),
		irr::core::vector3df(1.0f, 0.1f, 1.0f));

	/*Reglages pour le plateau : texture, position et lumiere*/
    if(plateau){
          plateau->setMaterialTexture(0, driver->getTexture("./images/plateau.jpg"));
          plateau->setPosition(irr::core::vector3df(-200, 120, -120));
          plateau->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }

    /*Initialisation des positions des cases sur le plateau*/
    for(int i = 0; i <4; i++){
            for(int j =0; j<4; j++){
                    positionsPlateau[i][j] = irr::core::vector3df(-93.75 + j*62.5, 370, 93.75 - i*62.5);
            }
    }

    /*Vecteur centre pour reperer la racine par rapport au centre du plateau*/
    centre = plateau->getPosition();
    centre = centre.invert();
    centre.Y += 740;

    /*Creation d'un noeud vide pour la pioche*/
    pioche = sceneMgr->addEmptySceneNode();

    /*Positionnement de la pioche*/
    pioche->setPosition(irr::core::vector3df(250, 37, -300));

    /*Initialisation des positions dans la pioche*/
    for(int i = 0; i<16; i++){
        if(i<8){
            positionsPioche[i] = irr::core::vector3df(0, 0, i*75);
        }
        else{
             positionsPioche[i] = irr::core::vector3df(75, 0, (i-8)*75);
        }
    }

    /*Initialisation des booleens a vrai : pions disponibles dans la pioche
      et cases disponibles sur le plateau*/
    for(int i = 0; i<16; i++){
            pionDisponible[i] = true;
    }

    for(int i = 0; i<4;  i++){
            for(int j = 0; j<4; j++){
                    caseDisponible[i][j] = true;
            }
    }

    /* Initialisation du tableau de correspondances entre pioche 3d et core */
    for(int i=0; i<16; i++){
           correspondances[i]= i;
    }

    /*Creation du halo de navigation, rattache a la pioche au depart*/
    light = sceneMgr->addVolumeLightSceneNode(pioche, -1,
    32,                              // Subdivisions on U axis
    32,                              // Subdivisions on V axis
    irr::video::SColor(0, 255, 255, 255), // foot color
    irr::video::SColor(0, 0, 0, 0));

    /*Reglages du halo : texture, echelle, position initiale*/
    light->getMaterial(0).setTexture(0, driver->getTexture("./images/halo.bmp"));
    light->setScale(irr::core::vector3df(100, 50, 100));
    light->setPosition(positionsPioche[0]);

    /*Creation des pions rattaches a la pioche au depart*/
    pion = new irr::scene::ISceneNode* [16];
    for(int i = 0; i<16; i++)
	{
	    if(i<8){
	        if(i%2 == 0){ // caracteristiques : taille petite, forme carre
                pion[i] = sceneMgr->addCubeSceneNode(50.0f,
                pioche,
                -1,
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(1.0f, 1.0f, 1.0f));
            }
            else{ // caracteristiques : taille petite, forme rond
                pion[i] = sceneMgr->addSphereSceneNode(25.0f,
                16, pioche, -1,
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(1.0f, 1.0f, 1.0f));
            }
	    }
	    else{ // caracteristiques : taille grande, forme carre
	        if(i%2 == 0){
                pion[i] = sceneMgr->addCubeSceneNode(50.0f,
                pioche,
                -1,
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(1.0f, 2.0f, 1.0f));
            }
            else{ // caracteristiques : taille grande, forme rond
                pion[i] = sceneMgr->addSphereSceneNode(25.0f,
                16, pioche, -1,
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(0, 0, 0),
                irr::core::vector3df(1.0f, 2.0f, 1.0f));
            }
	    }

        if(pion[i])
        {
            /*Reglages pour les pions : textures*/
            if(i%8<2){ // caracteristiques : blanc, non pointe
                if(i%2 == 0){
                    // caracteristiques : (petit, carre) et (grand, carre)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/blanc.png"));
                }
                else{
                     // caracteristiques : (petit, rond) et (grand, rond)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/blanc2.png"));
                }
            }
            else if(i%8<4){ // caracteristiques : blanc, pointe
                if(i%2 == 0){
                    // caracteristiques : (petit, carre) et (grand, carre)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/blanc_pointe.png"));
                }
                else{
                    // caracteristiques : (petit, rond) et (grand, rond)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/blanc_pointe2.png"));
                }
            }
            else if(i%8<6){ // caracteristiques : noir, non pointe
                if(i%2 == 0){
                    // caracteristiques : (petit, carre) et (grand, carre)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/noir.png"));
                }
                else{
                     // caracteristiques : (petit, rond) et (grand, rond)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/noir2.png"));
                }
            }
            else{ // caracteristiques : noir, pointe
                if(i%2 == 0){
                    // caracteristiques : (petit, carre) et (grand, carre)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/noir_pointe.png"));
                }
                else{
                    // caracteristiques : (petit, rond) et (grand, rond)
                    pion[i]->setMaterialTexture(0, driver->getTexture("./images/noir_pointe2.png"));
                }
            }
             /*Reglages pour les pions : lumiere et position*/
            pion[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            pion[i]->setPosition(positionsPioche[i]);
        }
    }

}


/*Lancement du jeu*/
void Moteur3d::run(int& scoreJ1, int& scoreJ2, int& scoreOrdi, int& scoreJ1vsOrdi, int pMax, bool CPUmode)
{

    /*Drapeaux*/
    bool partieFini = false;
    bool gagne = false;
    bool ordiGagne = false;
    bool mouvementsPion = false;
	bool ordi = false;
    bool deplacerPion = true;
    bool deplacementFini = false;
    bool placementPlateau = false;
    bool placementPlateauFini = true;
    bool deplacerLight = true;
    bool finDeplacementLight = true;
    bool phaseCase = false;
    bool choixCase = false;
    bool phasePion = true;
    bool choixPion = true;
    bool choixIA = false;
    bool rotationEncour =false;
    bool rotationFinis = false;
    bool  reinit = false;
    bool toScore = true;

    /*Variable pour reperer le numero du joueur*/
    int joueur =1;

    /*variable pour memoriser l'objet gagnant (ligne, colonne ou diagonnale)*/
    int objetGagnant = 0;

    /*Variables pour gerer le deplacement du halo dans la pioche et sur le plateau*/
    int selectionPion = 0;
    int ligne = 0;
    int colonne = 0;

    /*Variables pour memoriser le pion a jouer et la case ou le placer*/
    int pionEnJeu = 0;
    irr::core::vector3df kaseEnJeu = positionsPlateau[ligne][colonne];

    /*Variable pour gerer le pion choisi par l'ordi dans la pioche*/
    int positionOrdiCore;

    /* Creation des textes d'affichage*/
    irr::gui::IGUIStaticText * Ssttext =guiEnv->addStaticText(L"testeN1",irr::core::rect<irr::s32>(160,10,760,120));
    irr::gui::IGUIStaticText * Ssttext2 =guiEnv->addStaticText(L"testeN2",irr::core::rect<irr::s32>(640,100,780,120));
    irr::gui::IGUIStaticText * Ssttext3 =guiEnv->addStaticText(L"",irr::core::rect<irr::s32>(700,500,800,600));
    irr::core::stringw scores;
    setScores(scoreJ1, scoreJ2, scoreOrdi, scoreJ1vsOrdi, scores, Ssttext3, CPUmode);
    Ssttext->setBackgroundColor(irr::video::SColor(120,0,0,0));
    Ssttext3->setBackgroundColor(irr::video::SColor(120,0,0,0));
    Ssttext->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext2->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext3->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext->setOverrideColor(irr::video::SColor(255,240,195,0));
    Ssttext3->setOverrideColor(irr::video::SColor(255,240,195,0));

    /*Initialisation des booleens a vrai*/
    for(int i = 0; i<15; i++){
        pionDisponible[i] = true;
    }

    for(int i = 0; i<4;  i++){
        for(int j = 0; j<4; j++){
            caseDisponible[i][j] = true;
        }
    }
    /*Lancement du device*/
    while(device->run() && !partieFini)
    {

        if(!gagne){

            /*Phase de selection d'un pion*/
            if(phasePion){
                /* manipule les stringw puis conversion en wchar_t au dernier moment ac c_str  */
                irr::core::stringw text =L"Joueur ";
                text+=joueur;
                text+=L", selectionnez un pion de la pioche";
                Ssttext->setText(text.c_str());

                /*deplacement dans la pioche : vers le haut*/
                if(receiver.IsKeyDown(irr::KEY_KEY_Z)){
                    if(deplacerLight){
                        choixPion = false;
                        deplacementHautLightPioche(selectionPion);
                        deplacerLight = false;
                        finDeplacementLight = false;
                    }
                }

                /*deplacement dans la pioche : vers le bas*/
                if(receiver.IsKeyDown(irr::KEY_KEY_S)){
                    if(deplacerLight){
                        choixPion = false;
                        deplacementBasLightPioche(selectionPion);
                        deplacerLight = false;
                        finDeplacementLight = false;
                    }
                }

                /*deplacement dans la pioche : vers la droite*/
                if(selectionPion < 8){ // possible seulement si on est a gauche
                    if(receiver.IsKeyDown(irr::KEY_KEY_D)){
                        if(deplacerLight){
                            choixPion = false;
                            deplacementDroiteLightPioche(selectionPion);
                            deplacerLight = false;
                            finDeplacementLight = false;
                        }
                    }
                }

                /*deplacement dans la pioche : vers la gauche*/
                if(selectionPion > 7){ // possible seulement si on est a droite
                    if(receiver.IsKeyDown(irr::KEY_KEY_Q)){
                        if(deplacerLight){
                            choixPion = false;
                            deplacementGaucheLightPioche(selectionPion);
                            deplacerLight = false;
                            finDeplacementLight = false;
                        }
                    }
                }

                /*Attente de la fin du deplacement de la lumiere dans la pioche*/
                if(!finDeplacementLight){
                    if(animLight->hasFinished()){

                        /*fin du deplacement*/
                        light->removeAnimator(animLight);
                        animLight->drop();

                        /*mise a jour des drapeaux*/
                        finDeplacementLight = true;
                        deplacerLight = true;
                        choixPion = true;
                    }
                }

                /*Selection du pion a mettre en jeu*/
                if(pionDisponible[selectionPion]){
                    if(choixPion){
                        if(receiver.IsKeyDown(irr::KEY_SPACE)){
                            if(!CPUmode){
                                joueur=joueur%2;
                                joueur++;
                            }
                            /*Mise a jour du pion a jouer*/
                            pionEnJeu = selectionPion;

                            /*Le pion n'est plus disponible*/
                            pionDisponible[selectionPion] = false;

                            /*Tour jeu core*/
                            jeuCore.interfaceSelectionPion(correspondances[selectionPion]);
                            jeuCore.afficher();

                             /* MAJ correspondances entre les pioches 3d et core*/
                            majCorrespondance(selectionPion);



                            /*Mise a jour des drapeaux*/
                            choixPion =false;
                            phasePion = false;
                            mouvementsPion = true;
                            deplacerPion = true;
                            if(CPUmode){
                                choixIA = true;
                            }

                            /*Le halo disparait*/
                            light->setVisible(false);
                        }
                    }
                }
            }

            /*Phase de selection d'une case*/
            if(phaseCase){
                if(!choixIA){

                    /*gestion des deplacements de la lumiere sur le plateau*/

                    /*gestion deplacement vers le bas : touche S*/
                    if(receiver.IsKeyDown(irr::KEY_KEY_S)){
                        if(deplacerLight){
                            choixCase = false;
                            deplacementBasLightPlateau(ligne, colonne);
                            deplacerLight = false;
                            finDeplacementLight = false;
                        }
                    }

                    /*gestion deplacement vers le haut : touche Z*/
                    if(receiver.IsKeyDown(irr::KEY_KEY_Z)){
                        if(deplacerLight){
                            choixCase = false;
                            deplacementHautLightPlateau(ligne, colonne);
                            deplacerLight = false;
                            finDeplacementLight = false;
                        }
                    }

                    /*gestion deplacement vers la droite : touche D*/
                    if(receiver.IsKeyDown(irr::KEY_KEY_D)){
                        if(deplacerLight){
                            choixCase = false;
                            deplacementDroiteLightPlateau(ligne, colonne);
                            deplacerLight = false;
                            finDeplacementLight = false;
                        }
                    }

                    /*gestion deplacement vers la gauche : touche Q*/
                    if(receiver.IsKeyDown(irr::KEY_KEY_Q)){
                        if(deplacerLight){
                            choixCase = false;
                            deplacementGaucheLightPlateau(ligne, colonne);
                            deplacerLight = false;
                            finDeplacementLight = false;
                        }
                    }

                    /*Attente de la fin du deplacement de la lumiere sur le plateau*/
                    if(!finDeplacementLight){
                        if(animLight->hasFinished()){

                            /*fin du deplacement*/
                            light->removeAnimator(animLight);
                            animLight->drop();

                            /*mise a jour des drapeaux*/
                            finDeplacementLight = true;
                            deplacerLight = true;
                            choixCase = true;
                        }
                    }

                    /*Selection de la case ou placer le pion*/
                    if(caseDisponible[ligne][colonne]){
                        if(choixCase){
                            if(receiver.IsKeyDown(irr::KEY_SPACE)){
                                kaseEnJeu = positionsPlateau[ligne][colonne];

                                /*la case n'est plus disponible*/
                                caseDisponible[ligne][colonne] = false;

                                /*Jeu core : placement du pion sur le plateau*/
                                gagne=jeuCore.interfacePoserPion(ligne, colonne, objetGagnant);
                                jeuCore.afficher();
                                /*Mise a jour des drapeaux*/
                                choixCase =false;
                                phaseCase = false;
                                mouvementsPion = true;
                                placementPlateau = true;

                                /*Le halo disparait*/
                                light->setVisible(false);
                            }
                        }
                    }
                }
                else{
                    /*Choix IA*/
                    choixIA = false;
                    /*Lancement de l'IA pour le choix du coup a jouer et
                      memorisation du pion choisi par l'IA pour l'adversaire*/
                    positionOrdiCore = jeuCore.OrdiPoserPion(ligne, colonne, pMax, objetGagnant);

                    /*memorisation de la case choisie par l'IA*/
                    kaseEnJeu = positionsPlateau[ligne][colonne];

                    /*la case n'est plus disponible*/
                    caseDisponible[ligne][colonne] = false;

                    /*test de victoire*/
                    if(positionOrdiCore == -1){
                            gagne = true;
                            ordiGagne = true;
                    }

                    /*Mise a jour des drapeaux*/
                    mouvementsPion = true;
                    placementPlateau = true;
                    ordi=true;
                }
            }

            /*Mouvements des pions*/
            if(mouvementsPion){
                if(deplacerPion){
                    /* manipule les stringw puis conversion en wchar_t au dernier moment ac c_str  */
                    irr::core::stringw text;
                    if(CPUmode && !ordi){
                     text=L"l'ordi reflechit....";
                    }
                    else{
                        text =L"Joueur : ";
                        text+=joueur;
                        text+=L", selectionnez une case du plateau";
                    }
                    Ssttext->setText(text.c_str());

                    /*deplacement du pion selectionne vers le centre*/
                    deplacerPionCentre(pionEnJeu);

                    /*mise a jour des drapeaux*/
                    deplacerPion = false;
                    deplacementFini = false;
                }

                if(!deplacementFini){
                 if (anim){
                       if(anim->hasFinished()){

                            /*Fin du deplacement vers le centre*/
                            finDeplacement(pionEnJeu);

                            /*Mise a jour des drapeaux*/
                            deplacementFini = true;
                            mouvementsPion=false;
                            phaseCase = true;
                            choixCase = true;
                            deplacerLight = true;

                            /*Reinitialisation de la position a choisir sur le plateau :
                              a faire lorsque ce n'est plus a l'ordi de jouer*/
                            if(!CPUmode || ordi){
                                ligne = 0;
                                colonne = 0;
                                bool suivant = true;
                                while(suivant){
                                     if(colonne < 4){
                                        if(ligne <4){
                                            if(caseDisponible[ligne][colonne]){
                                                suivant = false;
                                            }
                                            else{
                                                ligne ++;
                                            }
                                        }
                                        else{
                                            ligne = 0;
                                            colonne++;
                                        }
                                    }
                                }

                                /*Reglage du halo : focus sur le plateau*/
                                light->setParent(plateau);
                                irr::core::vector3df placement = positionsPlateau[ligne][colonne];
                                placement.Y = 130;
                                light->setPosition(placement);
                                light->setVisible(true);
                                if(ordi){
                                    ordi=false;
                                }
                            }
                       }
                   }
              }
              if(placementPlateau){

                  /*Placement du pion sur la case*/
                  deplacementPlateau(pionEnJeu,kaseEnJeu);

                  /*Mise a jour des drapeaux*/
                  placementPlateau=false;
                  placementPlateauFini = false;

              }
              if(!placementPlateauFini){

                    if(anim){
                        if(anim->hasFinished()){

                            /*Fin du placement sur la case*/
                            finPlacementPlateau(pionEnJeu);

                            /*Mise a jour des drapeaux*/
                            placementPlateauFini = true;
                            if(!CPUmode || !ordi){
                                mouvementsPion = false;
                                phasePion = true;
                                choixPion = true;
                                deplacerLight = true;

                                /*Reinitialisation du pion a selectionner dans la pioche*/
                                selectionPion = 0;
                                while(!pionDisponible[selectionPion]){
                                    selectionPion++;
                                }

                                /*Reglage du halo : focus sur la pioche*/
                                light->setParent(pioche);
                                light->setPosition(positionsPioche[selectionPion]);
                                light->setVisible(true);
                            }
                            else{
                                pionEnJeu = inverseCorrespondance(positionOrdiCore);
                                majCorrespondance(pionEnJeu);
                                pionDisponible[pionEnJeu]=false;
                                deplacerPion = true;
                            }
                        }
                    }
                }
            }
        }
        else{
            /*gestion de l'affichage en cas de victoire*/
            irr::core::stringw text =L"";
            switch(objetGagnant){
                case 0 :
                text =L"la ligne ";
                text+=ligne+1;
                break;

                case 1:
                text =L"la colonne ";
                text+=colonne+1;
                break;

                case 2 :
                text =L"la premiere diagonnale ";
                break;

                case 3:
                text =L"la deuxieme diagonnale ";
                break;

                default:
                break;
            }
            text+=L" est gagnante!!!\n";

            /*Gestion des scores et textes*/
            if(toScore){
                if(ordiGagne){
                    text+=L"desole, l'ordi gagne...";
                    scoreOrdi++;
                }
                else{
                    text+=L"Joueur ";
                    text+=joueur;
                    text+=L", bravo, vous avez gagne!";
                    if(joueur == 1){
                        if(CPUmode){
                            scoreJ1vsOrdi++;
                        }
                        else{
                            scoreJ1++;
                        }
                    }
                    else if(joueur == 2){
                        scoreJ2++;
                    }
                }
                setScores(scoreJ1, scoreJ2, scoreOrdi, scoreJ1vsOrdi, scores, Ssttext3, CPUmode);
                text+=L"\n press Return(entree) to continue petit point  petit point petit point ";
                Ssttext->setText(text.c_str());
                toScore = false;
            }
            if(receiver.IsKeyDown(irr::KEY_RETURN)){
                partieFini = true;
            }

        }
        /* Tourne le plateau si A ou E presser */
        rotationPlateau(rotationEncour , rotationFinis, reinit);
        /*Lancement de la scene*/
        play();

    }
     device->drop();
     printf("partie finie\n\r");
}

/*Deplacement d'un pion de la pioche vers le centre*/
void Moteur3d::deplacerPionCentre(int i)
{
    /*Positions de depart et d'arrivee*/
    irr::core::vector3df depart = pioche->getPosition();
    int decal = plateau->getPosition().Y;
    irr::core::vector3df arrivee = irr::core::vector3df(0, decal + 74, 0);

    /*raccord du pion a la racine*/
    pion[i]->setParent(racine);

    /*repositionnement des coordonnees de depart par rapport a la racine*/
    depart.X += positionsPioche[i].X;
    depart.Y += positionsPioche[i].Y;
    depart.Z += positionsPioche[i].Z;

    /*creation de l'animation*/
    anim =sceneMgr->createFlyStraightAnimator(depart,
    arrivee, 1000,false);

    /*Lancement de l'animation*/
    pion[i]->addAnimator(anim);
}


/*gestion de l'arrivee d'un pion au centre*/
void Moteur3d::finDeplacement(int i)
{
    /*destruction de l'animation*/
    pion[i]->removeAnimator(anim);
    anim->drop();
    anim = NULL;


}
/* Tourne le plateau dans un sens ou dans l'autres */
void Moteur3d::rotationPlateau(bool &rotationEncour , bool & rotationFinis ,bool & reinit )
{
    int coef=1;
    irr::core::vector3df rotation = plateau->getRotation();

    if(receiver.IsKeyDown(irr::KEY_KEY_E) and  rotationEncour == false and reinit==false ){
    coef = -1;
    rotationEncour =true;

    }else if(receiver.IsKeyDown(irr::KEY_KEY_A) and  rotationEncour==false and reinit == false){
    coef =1;
    rotationEncour =true;
    }else if (receiver.IsKeyDown(irr::KEY_KEY_R)){
       reinit = true;
    }
    if(rotationEncour == true and rotationFinis == false){
        /* Definition de la rotation */
        irr::core::vector3df rotationInit= plateau->getRotation();
        irr::core::vector3df rotationSupp(0,0.5*coef,0);

        rotationSupp+=rotationInit;
        plateau->setRotation(rotationSupp);
        rotationFinis=true;
    }
    if(rotationEncour == true and rotationFinis == true and reinit == false){
        rotationFinis = false;
        rotationEncour = false;
    }
    if(rotationEncour == false and rotationFinis == false and reinit == true){
        int angle = rotation.Y;
        if(angle%360 > 0){
            rotation.Y -=0.5;
            plateau->setRotation(rotation);
        }else if (angle%360 < 0){
            rotation.Y +=0.5;
            plateau->setRotation(rotation);
        }else {
            reinit = false;
        }
    }
}




/*Placement d'un pion du centre vers une case*/
void Moteur3d::deplacementPlateau(int i, irr::core::vector3df kase)
{
    centre = plateau->getPosition();
   // centre-=plateau->getRotation();
    centre = centre.invert();
    centre.Y += 740;//*/

    /*Rattachement du pion au plateau*/
    plateau->addChild(pion[i]);
    if(i<8){
        /*pion de petite taille*/
        pion[i]->setScale(irr::core::vector3df(1,10,1));
    }
    else{
        /*pion de grande taille*/
        pion[i]->setScale(irr::core::vector3df(1,20,1));
    }
    pion[i]->setPosition(centre);

    /*ajustement de la position de la case pour un pion de grande taille*/
    if(i>=8){
        kase.Y = 620;
    }//*/

    /*Creation de l'animation*/
    anim =sceneMgr->createFlyStraightAnimator(centre,
    kase, 1000,false);

    /*Lancement de l'animation*/
    pion[i]->addAnimator(anim);

}


/*destruction de l'animation qui deplace un pion vers une case*/
void Moteur3d::finPlacementPlateau(int i)
{
    pion[i]->removeAnimator(anim);
    anim->drop();
    anim = NULL;
}

/*Deplacement de la lumiere sur la plateau : vers le bas*/
void Moteur3d::deplacementBasLightPlateau(int& ligne, int& colonne)
{
    if(ligne < 3){
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        ligne ++;
        irr::core::vector3df arrivee = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        arrivee.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
    }
    else{
        ligne = 0;
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        depart, 500,false);
    }
    /*Lancement de l'animation*/
    light->addAnimator(animLight);
}

/*Deplacement de la lumiere sur la plateau : vers le haut*/
void Moteur3d::deplacementHautLightPlateau(int& ligne, int& colonne)
{
    if(ligne == 0){
        ligne = 3;
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        depart, 500,false);
    }
    else{
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        ligne --;
        irr::core::vector3df arrivee = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        arrivee.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
    }
    /*Lancement de l'animation*/
    light->addAnimator(animLight);
}

/*Deplacement de la lumiere sur la plateau : vers la droite*/
void Moteur3d::deplacementDroiteLightPlateau(int& ligne, int& colonne)
{
    if(colonne < 3){
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        colonne ++;
        irr::core::vector3df arrivee = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        arrivee.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
    }
    else{
        colonne = 0;
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        depart, 500,false);
    }
    light->addAnimator(animLight);
}

/*Deplacement de la lumiere sur la plateau : vers la gauche*/
void Moteur3d::deplacementGaucheLightPlateau(int& ligne, int& colonne)
{
    if(colonne == 0){
        colonne = 3;
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        depart, 500,false);
    }
    else{
        irr::core::vector3df depart = positionsPlateau[ligne][colonne];
        colonne --;
        irr::core::vector3df arrivee = positionsPlateau[ligne][colonne];
        depart.Y = 130;
        arrivee.Y = 130;
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
    }
    /*Lancement de l'animation*/
    light->addAnimator(animLight);
}

/*Deplacement de la lumiere dans la pioche : vers le haut*/
void Moteur3d::deplacementHautLightPioche(int& selectionPion)
{
    if(selectionPion == 7 || selectionPion == 15){
        if(selectionPion == 7){
            selectionPion = 0;
        }
        else{
            selectionPion = 8;
        }
        irr::core::vector3df depart = positionsPioche[selectionPion];
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        depart, 500,false);
    }
    else{
        irr::core::vector3df depart = positionsPioche[selectionPion];
        selectionPion ++;
        irr::core::vector3df arrivee = positionsPioche[selectionPion];
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
    }
    light->addAnimator(animLight);
}

/*Deplacement de la lumiere dans la pioche : vers le bas*/
void Moteur3d::deplacementBasLightPioche(int& selectionPion)
{
    if(selectionPion == 0 || selectionPion == 8){
        if(selectionPion == 0){
            selectionPion = 7;
        }
        else{
            selectionPion = 15;
        }
        irr::core::vector3df depart = positionsPioche[selectionPion];
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        depart, 500,false);
    }
    else{
        irr::core::vector3df depart = positionsPioche[selectionPion];
        selectionPion --;
        irr::core::vector3df arrivee = positionsPioche[selectionPion];
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
    }
    light->addAnimator(animLight);
}

/*Deplacement de la lumiere dans la pioche : vers la droite*/
void Moteur3d::deplacementDroiteLightPioche(int& selectionPion)
{
    if(selectionPion < 8){
        irr::core::vector3df depart = positionsPioche[selectionPion];
        selectionPion += 8;
        irr::core::vector3df arrivee = positionsPioche[selectionPion];
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
        light->addAnimator(animLight);
    }
}

/*Deplacement de la lumiere dans la pioche : vers la gauche*/
void Moteur3d::deplacementGaucheLightPioche(int& selectionPion)
{
    if(selectionPion > 7){
        irr::core::vector3df depart = positionsPioche[selectionPion];
        selectionPion -= 8;
        irr::core::vector3df arrivee = positionsPioche[selectionPion];
        animLight =sceneMgr->createFlyStraightAnimator(depart,
        arrivee, 500,false);
        light->addAnimator(animLight);
    }
}

/*Mise a jour des positions dans la pioche apres selection d'un pion*/
void Moteur3d::majCorrespondance(int pionSelection)
{
     int k = pionSelection;
   correspondances[k] = -1;
   for(int i = k+1  ; i <16; i++){
       if(correspondances[i] != -1){
                             correspondances[i]--;
       }
   }
}

/*Correspondance inverse Core, 3d pour la pioche*/
int Moteur3d::inverseCorrespondance(int positionCore){
    for(int i =0; i<16; i++){
            if(correspondances[i] == positionCore){
                                  return i;
            }
    }
    return -1;
}

void Moteur3d::setScores(int scoreJ1, int scoreJ2, int scoreOrdi,int scoreJ1vsOrdi, irr::core::stringw& scores, irr::gui::IGUIStaticText* Ssttext, bool CPUmode)
{
    scores = L"Scores :\n";
    if(CPUmode){
        scores +=L"Joueur1 : ";
        scores +=scoreJ1vsOrdi;
        scores +=L"\nOrdi : ";
        scores += scoreOrdi;
    }
    else{
        scores +=L"Joueur1 : ";
        scores +=scoreJ1;
        scores +=L"\nJoeur2 : ";
        scores += scoreJ2;
    }
    Ssttext->setText(scores.c_str());
}

/*Lancement d'une scene*/
void Moteur3d::play()
{
    driver->beginScene(true, true, irr::video::SColor(0,10,113,133));
    sceneMgr->drawAll();
    device->getGUIEnvironment()->drawAll();
    driver->endScene();
}
