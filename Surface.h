#ifndef SURFACE_H
#define SURFACE_H

#if defined WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#endif

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
