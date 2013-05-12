#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "ProgramState.h"
#include "MainMenu.h"

class SplashScreen : public ProgramState
{
public:

    bool run();

private:

    MainMenu* mainmenu;
    void OnExit();
};

#endif