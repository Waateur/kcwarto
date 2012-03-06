#ifndef MENU3D_H_INCLUDED
#define MENU3D_H_INCLUDED

#include "MyReceiver.h"

class Menu3d {

  private:

  irr::video::IVideoDriver* driver;
  irr::scene::ISceneManager* sceneMgr;
  irr::IrrlichtDevice* device;
  irr::gui::IGUIEnvironment* guiEnv;
  irr::scene::ICameraSceneNode* camera;
  MyReceiver receiver;
  /* Test sur stacticText  */
  irr::gui::IGUIStaticText * Ssttext;
  irr::gui::IGUIStaticText * Ssttext2;
  irr::gui::IGUIStaticText * Ssttext3;
  irr::gui::IGUIStaticText * Ssttext4;
  irr::gui::IGUIStaticText * Ssttext5;


  public:

  Menu3d();
  ~Menu3d();
  int run(bool&, bool&, bool&);
  void play();
};



#endif // MENU3D_H_INCLUDED
