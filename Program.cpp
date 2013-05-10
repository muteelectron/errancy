#include "Program.h"


bool Program::run()
{
    if(!init())
    {
        return false;
    }

    splashscreen = new SplashScreen;
    return splashscreen->run();
}


int Program::init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        Log::write("");
        return false;
    }

    int width;
    int height;

    if( ( Surf_Display = SDL_SetVideoMode( width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ) ) == NULL )
    {
        Log::write("");
        return false;
    }

    return true;
}