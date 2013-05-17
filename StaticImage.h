#ifndef STATICIMAGE_H
#define STATICIMAGE_H

#include "Image.h"
#include "Surface.h"

class StaticImage : Image
{
public:

    StaticImage();
    ~StaticImage();

    void render();

    int getX();
    void setX(const int x_init);

    int getY();
    void setY(const int y_init);

    SDL_Surface* getTarget();
    void setTarget(SDL_Surface* const target_init);

private:

    SDL_Surface* image;
    SDL_Surface* target;

    int x;
    int y;
};

#endif
