center_#include "Graphics.h"


Graphics::Graphics(char* filename)
{
    ifstream input(filename);

    char* graphics_type_init;
    char* graphics_file_name;
    input >> graphics_type_init;
    input >> graphics_file_name;

    load_image(graphics_file_name);

    input >> center_x;
    input >> center_y;
    input >> width;

    int height_coef;
    input >> height_coef;
    height = width * height_coef;

    if(graphics_type_init == "static")
    {
        
    }
    else if(graphics_type_init == "animated")
    {
        input >> fps;
        frame_interval_ms = 1000 / fps;
    }
    else
    {
        // ERROR
    }
}


Graphics::~Graphics()
{

}


void Graphics::render()
{

}


int Graphics::get_center_x()
{
    return center_x;
}


int Graphics::get_center_y()
{
    return center_y;
}


int Graphics::get_width()
{
    return width;
}


int Graphics::get_height()
{
    return height;
}


double Graphics::get_angle(AngleDirection angle_direction)
{
    if(angle_direction == CCW)
    {
        return angle_ccw;
    }
    else
    {
        return (angle_ccw == 0 ? 0 : 360 - angle_ccw);
    }
}



void Graphics::set_center_x(int center_x_init)
{
    x = x_init;
}


void Graphics::set_y(int center_y_init)
{
    center_y = center_y_init;
}


void Graphics::set_width(int width_init)
{
    width = width_init;
}


void Graphics::set_height(int height_init)
{
    height = height_init;
}


void Graphics::set_angle(double angle_ccw_init, AngleDirection angle_direction)
{
    if(angle_direction == CCW)
    {
        angle_ccw = angle_ccw_init;
    }
    else
    {
        angle_ccw = 360 - angle_ccw_init;
    }
    angle_ccw -= ((int)angle_ccw / 360) * 360
}


void Graphics::set_fps(int fps_init)
{
    if(fps_init > 0)
    {
        fps = fps_init;
        frame_interval_ms = 1000 / fps_init;
    }
    else
    {
        // ERROR
    }
}


void Graphics::set_frame_interval_ms(double frame_interval_ms_init)
{
    if(frame_interval_ms_init > 0)
    {
        frame_interval_ms = frame_interval_ms_init;
        fps = frame_interval_ms * 1000;
    }
    else
    {
        // ERROR
    }
}


void Graphics::load_image(char* filename)
{
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL)
    {
        // ERROR
    }

    GLint nofcolors;
    nofcolors=image->format->BytesPerPixel;
    GLenum texture_format;

    if(nofcolors==4)
    {
        if(image->format->Rmask==0x000000ff)
        {
            texture_format = GL_RGBA;
        }
        else
        {
            texture_format = GL_BGRA;
        }
    }
    else if(nofcolors == 3) //no alpha channel
    {
        if(image->format->Rmask == 0x000000ff)
        {
            texture_format = GL_RGB;
        }
        else
        {
            texture_format = GL_BGR;
        }
    }
    else
    {
        // ERROR: the image is not truecolor
    }

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, nofcolors, image->w, image->h,
                      texture_format, GL_UNSIGNED_BYTE, image->pixels);


    SDL_FreeSurface(image);
}
