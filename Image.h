#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Image
{
public:

    ~Image();

    bool OnLoad(char* File);
    bool OnDraw(SDL_Surface* Surf_Dest, int X, int Y);
    bool OnDraw(SDL_Surface* Surf_Dest, int X, int Y, int X2, int Y2, int W, int H);

private:

    SDL_Surface* surface;
};

#endif