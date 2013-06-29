#include "Program.h"


bool Program::run()
{
    Log::write("Program::run start");

    if(!init())
    {
        return false;
    }

    splashscreen = new SplashScreen;
    return splashscreen->run();
    Log::write("Program::run finish");
}


int Program::init()
{
    Log::write("Program::init start");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Log::write("SDL initialization error");
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int width;
    int height;
    std::ifstream screen_res_input("screen_res.txt");
    screen_res_input >> width >> height;

    if(!SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_FULLSCREEN))
    {
        Log::write("SDL_video_surface initialization error");
        return false;
    }


    glViewport(0, 0, width, height);
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 1, 0, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
    Log::write("Program::init finish");
    return true;
}
