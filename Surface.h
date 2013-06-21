#ifndef SURFACE_H
#define SURFACE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class Surface
{
   public:

      static SDL_Surface* OnLoad( char* File );
      static bool OnDraw( SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y );
      static bool OnDraw( SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H );
};

#endif
