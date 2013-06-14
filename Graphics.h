#ifndef GRAPHICS_H
#define GRAPHICS_H


#if defined WIN32

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <gl/glu.h>

#else

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#endif


enum GraphicsType{STATIC, ANIMATED};

class Graphics
{
public:

    Graphics(char* filename);
    ~Graphics();

private:

    GraphicsType graphics_type;
    GLuint texture;
};

#endif