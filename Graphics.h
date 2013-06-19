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
using std::ifstream;


enum GraphicsType{STATIC, ANIMATED};

enum AngleDirection{CW, CCW};
enum AngleType{DEGREE, RADIAN};

class Graphics
{
public:

    Graphics(char* file_name);
    ~Graphics();

    void render();


    int get_center_x();
    int get_center_y();
    int get_width();
    int get_height();
    double get_angle(AngleDirection angle_direction, AngleType angle_type);
    int get_fps();
    double get_frame_interval();

    void set_center_x(int center_x_init);
    void set_center_y(int center_y_init);
    void set_width(int width_init);
    void set_height(int height_init);
    void set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type);
    void set_fps(int fps_init);
    void set_frame_interval_ms(double frame_interval_ms_init);


private:

    void load_image(char* file_name);

    GraphicsType graphics_type;
    GLuint texture;

    int center_x;
    int center_y;
    int width;
    int height;
    double angle_ccw_rad;
    double angle_ccw_rad_default;
    double semi_diagonal;

    int num_of_frames;
    int fps;
    unsigned int frame_interval_ms;
    unsigned int last_render_time;
};

#endif
