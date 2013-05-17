#include "Program.h"


bool Program::run()
{
    Log::write("Program has started");
    if(!init())
    {
        return false;
    }

    splashscreen = new SplashScreen;
    return splashscreen->run();
}


int Program::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Log::write("SDL initialization error");
        return false;
    }

    int width;
    int height;
    std::ifstream screen_res_input("screen_res.txt");
    screen_res_input >> width >> height;

    if((Surf_Display = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)) == NULL)
    {
        Log::write("SDL_video_surface initialization error");
        return false;
    }

    return true;
}
