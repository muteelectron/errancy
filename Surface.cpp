#include "Surface.h"
#include <fstream>


SDL_Surface *Surface::OnLoad(std::string File)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;
    if((Surf_Temp = IMG_Load(File.c_str())) == NULL)
    {
        return NULL;
    }
    Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);
    return Surf_Return;
};

bool Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y)
{
    if(Surf_Dest == NULL || Surf_Src == NULL)
    {
        return false;
    }
    SDL_Rect DestR;
    DestR.x = X;
    DestR.y = Y;
    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);
    return true;
};

bool Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X,
                     int Y, int X2, int Y2, int W, int H)
{
    if(Surf_Dest == NULL || Surf_Src == NULL)
    {
        return false;
    }
    SDL_Rect DestR;
    DestR.x = X;
    DestR.y = Y;
    SDL_Rect SrcR;
    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;
    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);
    return true;
}
