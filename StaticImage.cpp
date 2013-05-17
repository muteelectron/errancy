#include "StaticImage.h"

StaticImage::StaticImage()
{

}


StaticImage::~StaticImage()
{

}

void StaticImage::render()
{
    Surface::OnDraw(target, image, x, y);
}


int StaticImage::getX()
{
    return x;
}


void StaticImage::setX(const int x_init)
{
    x = x_init;
}



int StaticImage::getY()
{
    return y;
}


void StaticImage::setY(const int y_init)
{
    y = y_init;
}



SDL_Surface* StaticImage::getTarget()
{
    return target;
}


void StaticImage::setTarget(SDL_Surface* const target_init)
{
    target = target_init;
}
