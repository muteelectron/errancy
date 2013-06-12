#ifndef IMAGE_H
#define IMAGE_H

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

class Image
{
public:

    Image(char* filename);
    ~Image();

    void render();

    void set_x(int x_init);
    void set_y(int y_init);
    void set_width(int width_init);
    void set_height(int height_init);
    void set_angle(double angle_init);

    int get_x();
    int get_y();
    int get_width();
    int get_height();
    double get_angle();

private:

    GLuint texture;

    int x;
    int y;

    int width;
    int height;

    double angle;
};

#endif

