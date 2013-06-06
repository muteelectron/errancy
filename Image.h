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

    void set_x(double x_init);
    void set_y(double y_init);
    void set_angle(double angle_init);

    double get_x();
    double get_y();
    double get_angle();

private:

    GLuint texture;

    double x;
    double y;

    double width;
    double height;

    double angle;
};

#endif

