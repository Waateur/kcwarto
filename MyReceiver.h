#ifndef RECEIVER_H_INCLUDED
#define RECEIVER_H_INCLUDED

#include <irrlicht.h>

enum
{
	GUI_ID_DEUX_BUTTON = 0,
	GUI_ID_ORDI_BUTTON,
	GUI_ID_QUIT_BUTTON,
	GUI_ID_LEVEL_SCROLL_BAR,
	GUI_ID_SCREEN_BAR
};

class MyReceiver :public irr::IEventReceiver
{
      private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	int levelBar;
	bool fullScreen;
	bool CPU;
	bool VS;
	bool quit;

       public:
    MyReceiver();
    ~MyReceiver();
	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event);
	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

	bool getScreenSize();
	bool getCPUmode();
	bool getVSmode();
	bool getQuit();
	int getGameLevel();

};




#endif //RECEIVER_H_INCLUDED
