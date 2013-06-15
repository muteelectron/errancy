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

#include <fstream>
using std::ifstream;


enum GraphicsType{STATIC, ANIMATED};

enum AngleDirection{CW, CCW};

class Graphics
{
public:

    Graphics(char* filename);
    ~Graphics();

    void render();


    int get_center_x();
    int get_center_y();
    int get_width();
    int get_height();
    double get_angle(AngleDirection angle_direction);

    int set_center_x(int center_x_init);
    int set_center_y(int center_y_init);
    int set_width(int width_init);
    int set_height(int height_init);
    double set_angle(double angle_ccw_init, AngleDirection angle_direction);

private:

    void load_image(char* filename);

    GraphicsType graphics_type;
    GLuint texture;

    int center_x;
    int center_y;
    int width;
    int height;
    double angle_ccw;
};

#endif
