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

    void render();


    int get_x();
    int get_y();
    int get_width();
    int get_height();
    double get_angle();

    int set_x(int x_init);
    int set_y(int y_init);
    int set_width(int width_init);
    int set_height(int height_init);
    double set_angle(double angle);

private:

    GraphicsType graphics_type;
    GLuint texture;

    int x;
    int y;
    int width;
    int height;
    double angle;
};

#endif
