#include "Program.h"


int Program::run()
{
    if(init() != 0)
    {
        // ERROR
        return -1;
    }
}


int Program::init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        // ERROR
        return -1;
    }

    int width;
    int height;

    if( ( Surf_Display = SDL_SetVideoMode( width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ) ) == NULL )
    {
        // ERROR
        return -2;
    }

    return 0;
}