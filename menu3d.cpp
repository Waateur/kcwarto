#include "menu3d.h"

Menu3d::Menu3d()
{
    /*creation du device*/
    device = irr::createDevice (
    irr::video::EDT_OPENGL,
    irr::core::dimension2d<irr::u32>(640,480),
    32,
    false,
    false,
    false,
    &receiver);//*/

    /*creation driver et scene manager et gui environement*/
    driver = device->getVideoDriver();
    sceneMgr = device->getSceneManager();
    guiEnv = device->getGUIEnvironment();

    /*Logo en haut a droite*/
    guiEnv->addImage(driver->getTexture("./images/Cwarto.png"),irr::core::position2d<int>(245,1));

    /*Creation de la camera*/
    camera = sceneMgr->addCameraSceneNode(
     0,
	irr::core::vector3df(0, 0, 0),
	irr::core::vector3df(0, 0, 0)
    );
}

Menu3d::~Menu3d()
{
    //device->drop();
}

int Menu3d::run(bool& CPU, bool& fullScreen, bool& quit)
{
    int niveau =0;

    /*Textes*/
    Ssttext =guiEnv->addStaticText(L"kWARTO",irr::core::rect<irr::s32>(640,100,780,120));
    Ssttext2 =guiEnv->addStaticText(L"Fenetre",irr::core::rect<irr::s32>(240,170,400,185));
    Ssttext3 =guiEnv->addStaticText(L"Facile",irr::core::rect<irr::s32>(45,300,245,350));
    Ssttext4 =guiEnv->addStaticText(L"Mode d'affichage",irr::core::rect<irr::s32>(240,150,400,165));
    Ssttext5 =guiEnv->addStaticText(L"LEVEL",irr::core::rect<irr::s32>(45, 360, 245, 375));

    Ssttext->setBackgroundColor(irr::video::SColor(120,0,0,0));
    Ssttext3->setBackgroundColor(irr::video::SColor(120,0,0,0));
    Ssttext4->setBackgroundColor(irr::video::SColor(120,0,0,0));
    Ssttext->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext2->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext3->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext4->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext5->setTextAlignment(irr::gui::EGUIA_CENTER , irr::gui::EGUIA_CENTER);
    Ssttext->setOverrideColor(irr::video::SColor(255,240,195,0));
    Ssttext2->setOverrideColor(irr::video::SColor(255,240,195,0));
    Ssttext3->setOverrideColor(irr::video::SColor(255,240,195,0));//*/
    Ssttext4->setOverrideColor(irr::video::SColor(255,240,195,0));
    Ssttext5->setOverrideColor(irr::video::SColor(255,240,195,0));

    /*bouttons et scrollbar*/

    guiEnv->addButton(irr::core::rect<irr::s32>(155+145,360+60,145+255,385+60), 0, GUI_ID_DEUX_BUTTON,
        L"VS", L"mode deux joueurs");

    guiEnv->addButton(irr::core::rect<irr::s32>(95,360+60,195,385+60), 0, GUI_ID_ORDI_BUTTON,
        L"CPU", L"mode contre ordinateur");

    guiEnv->addButton(irr::core::rect<irr::s32>(355+145,360+60,455+145,385+60), 0, GUI_ID_QUIT_BUTTON,
        L"QUIT", L"Quitter la partie");

    irr::gui::IGUIScrollBar* levelScrollBar =guiEnv->addScrollBar(true,
    irr::core::rect<irr::s32>(45, 360, 245, 375), 0, GUI_ID_LEVEL_SCROLL_BAR);
    levelScrollBar->setMax(2);

    irr::gui::IGUIScrollBar* screenScrollBar =guiEnv->addScrollBar(true,
    irr::core::rect<irr::s32>(240, 170, 400, 185), 0, GUI_ID_SCREEN_BAR);
    screenScrollBar->setMax(1);

    bool encours =true;
    while(device->run() && encours==true){
        if(receiver.getScreenSize()){
            Ssttext2->setText(L"Plein ecran");
            fullScreen = true;
        }
        else{
             Ssttext2->setText(L"Fenetre");
             fullScreen = false;
        }//*/
        if(receiver.getCPUmode()){
            CPU = true;
            encours = false;
        }
        if(receiver.getVSmode()){
            CPU = false;
            encours = false;
        }
        if(receiver.getQuit()){
            quit = true;
            encours = false;
        }
        niveau=receiver.getGameLevel();
        if(niveau==0){
         Ssttext3->setText(L"Niveau facile");
        }else if(niveau==1) {
         Ssttext3->setText(L"Niveau moyen");
        }else if(niveau==2){
            Ssttext3->setText(L"Niveau difficile");
        }



        play();
    }
    device->drop();
    return niveau;
}

void Menu3d::play()
{
    driver->beginScene(true, true, irr::video::SColor(0,10,113,133));
    sceneMgr->drawAll();
    guiEnv->drawAll();
    driver->endScene();
}
