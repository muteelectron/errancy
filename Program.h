#ifndef PROGRAM_H
#define PROGRAM_H

#if defined WIN32

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <gl/glu.h>

#else

#include <SDL/SDL.h>
#include <GL/gl.h>

#endif

#include <fstream>
#include "ProgramState.h"
#include "SplashScreen.h"

class Program : public ProgramState
{
public:

    bool run();

private:

    int init();

    SplashScreen* splashscreen;
};

#endif
