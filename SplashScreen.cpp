#include "SplashScreen.h"


bool SplashScreen::run()
{
    Log::write("SplashScreen has started");
    mainmenu = new MainMenu;
    return mainmenu->run();
}

void SplashScreen::OnExit()
{
    
}
