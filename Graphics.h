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

#include <cmath>
#include <fstream>
#include <string>
#include "Log.h"


enum GraphicsType{STATIC, ANIMATED};

enum AngleDirection{CW, CCW};
enum AngleType{DEGREE, RADIAN};

class Graphics
{
public:

    Graphics(std::string file_name);
    ~Graphics();

    virtual void render();


    virtual double get_center_x();
    virtual double get_center_y();
    virtual double get_width();
    virtual double get_height();
    virtual double get_angle(AngleDirection angle_direction, AngleType angle_type);
    virtual int get_fps();
    virtual unsigned int get_frame_interval_ms();

    virtual void set_center_x(double center_x_init);
    virtual void set_center_y(double center_y_init);
    virtual void set_width(double width_init);
    virtual void set_height(double height_init);
    virtual void set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type);
    virtual void set_fps(int fps_init);
    virtual void set_frame_interval_ms(unsigned int frame_interval_ms_init);


private:

    void load_image(std::string file_name);

    GraphicsType graphics_type;
    GLuint texture;

    double center_x;
    double center_y;
    double width;
    double height;
    double angle_ccw_rad;
    double angle_ccw_rad_default;
    double semi_diagonal;

    int num_of_frames;
    int fps;
    unsigned int frame_interval_ms;
    unsigned int first_render_time;
};

#endif
