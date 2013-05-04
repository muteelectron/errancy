#include "SplashScreen.h"


bool SplashScreen::run()
{
    mainmenu = new MainMenu;
    return mainmenu->run();
}