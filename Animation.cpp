#include "Animation.h"


Animation::Animation()
{

}


Animation::~Animation()
{
    SDL_FreeSurface(image);
}