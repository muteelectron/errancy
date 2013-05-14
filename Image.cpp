#include "Image.h"

Image::~Image()
{
    SDL_FreeSurface(surface);
}

bool Image::OnLoad(char* File)
{
    SDL_Surface* Surf_Temp = NULL;
    if((Surf_Temp = IMG_Load(File)) == NULL)
    {
        return false;
    }
    surface = SDL_DisplayFormatAlpha(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);
    return true;
}


bool Image::OnDraw(SDL_Surface* Surf_Dest, int X, int Y)
{
    if(Surf_Dest == NULL || surface == NULL)
    {
        return false;
    }
    SDL_Rect DestR;
    DestR.x = X;
    DestR.y = Y;
    SDL_BlitSurface(surface, NULL, Surf_Dest, &DestR);
    return true;
}


bool Image::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* surface, int X, int Y, int X2, int Y2, int W, int H)
{
    if(Surf_Dest == NULL || surface == NULL)
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
    SDL_BlitSurface(surface, &SrcR, Surf_Dest, &DestR);
    return true;
}