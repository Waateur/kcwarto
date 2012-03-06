#include "MyReceiver.h"




MyReceiver::MyReceiver() : 	levelBar(0), fullScreen(false), CPU(false), VS(false), quit(false)
{
 for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;

}

MyReceiver::~MyReceiver()
{
}

bool MyReceiver::OnEvent(const irr::SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT){
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
	}
    else if (event.EventType == irr::EET_GUI_EVENT)
		{
			irr::s32 id = event.GUIEvent.Caller->getID();
			//irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

				case irr::gui::EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_LEVEL_SCROLL_BAR)
				{
					levelBar = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					return false;
				}else if(id== GUI_ID_SCREEN_BAR){
					int pos=((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					if(pos== 0){
						fullScreen = false;
						return false;
					}else {
						fullScreen = true;
						return false;
					}
				}
				break;//*/


			case irr::gui::EGET_BUTTON_CLICKED:

				switch(id)
				{
				case GUI_ID_ORDI_BUTTON:
                    VS = false;
					CPU = true;
					return false;

				case GUI_ID_DEUX_BUTTON:
					CPU=false;
					VS = true;
					return false;

                case GUI_ID_QUIT_BUTTON:
                    quit = true;
                    return false;

				default:
					return false;
				}

			default:
                return false;
			}//*/
		}
		else return false;
		return false;
}

bool MyReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

bool MyReceiver::getScreenSize()
{
    return fullScreen;
}

bool MyReceiver::getCPUmode()
{
    return CPU;
}

bool MyReceiver::getVSmode()
{
    return VS;
}

bool MyReceiver::getQuit()
{
    return quit;
}

int MyReceiver::getGameLevel()
{
    return levelBar;
}
