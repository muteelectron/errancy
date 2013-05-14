#ifndef PROGRAM_H
#define PROGRAM_H

#include <SDL/SDL.h>
#include <fstream>
#include "ProgramState.h"
#include "SplashScreen.h"

class Program : public ProgramState
{
public:

    bool run();

private:

    int init();

    SDL_Surface* Surf_Display;

    SplashScreen* splashscreen;
};

#endif