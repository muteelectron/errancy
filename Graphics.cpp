#include "Graphics.h"

 //    *.graphics file template    //
////////////////////////////////////
// graphics type(static or animated)
// image's file name
// center's x coordinat
// center's y coordinat
// width(in 0-1 interval)
// number of frames(only if graphics is animated)
// frames per second(only if graphics is animated)


Graphics::Graphics(std::string file_name)
{
    if(std::ifstream(file_name.c_str()) == NULL)
    {
        Log::write("ERROR: " + file_name + " doesn't exist");
    }
    
    std::ifstream input(file_name.c_str());

    std::string graphics_type_init;
    std::string graphics_file_name;
    input >> graphics_type_init;
    input >> graphics_file_name;

    input >> center_x;
    input >> center_y;
    input >> width;

    load_image(graphics_file_name);

    semi_diagonal = sqrt(pow(width / 2, 2) + pow(height / 2, 2));

    double height_coef;
    height_coef = height / width;

    // height_coef == tan(PI - angle)

    angle_ccw_rad_default = M_PI - atan(height_coef);
    angle_ccw_rad = 0;

    if(graphics_type_init == "static")
    {
        num_of_frames = 1;
    }
    else if(graphics_type_init == "animated")
    {
        input >> num_of_frames;
        input >> fps;
        frame_interval_ms = 1000 / fps;
        first_render_time = 0;
    }
    else
    {
        // ERROR
    }
}


Graphics::~Graphics()
{
    glDeleteTextures(1, &texture);
}


void Graphics::render()
{
    glPushMatrix();

    glRotatef(360 - angle_ccw_rad * 180 / M_PI, 0, 0, 1);

    double top_left_corner_x;
    double top_left_corner_y;
    top_left_corner_x = center_x + semi_diagonal * cos(angle_ccw_rad + angle_ccw_rad_default);
    top_left_corner_y = center_y + semi_diagonal * sin(angle_ccw_rad + angle_ccw_rad_default);

    glBindTexture(GL_TEXTURE_2D, texture);

    int cur_frame;
    if(graphics_type == ANIMATED)
    {
        if(first_render_time == 0)
        {
            first_render_time = SDL_GetTicks();
            cur_frame = 0;
        }
        else
        {
            cur_frame = ((SDL_GetTicks() - first_render_time) / frame_interval_ms) % num_of_frames;
        }
    }
    else
    {
        cur_frame = 0;
    }

    glBegin(GL_QUADS);

        // Bottom-Left
        glTexCoord2d((double)cur_frame / num_of_frames, 1);
        glVertex2f(top_left_corner_x, top_left_corner_y - height);

        // Bottom-Right
        glTexCoord2d((double)(cur_frame + 1) / num_of_frames, 1);
        glVertex2f(top_left_corner_x + width, top_left_corner_y - height);

        // Top-Right
        glTexCoord2d((double)(cur_frame + 1) / num_of_frames, 0);
        glVertex2f(top_left_corner_x + width, top_left_corner_y);

        // Top-Left
        glTexCoord2d((double)cur_frame / num_of_frames, 0);
        glVertex2f(top_left_corner_x, top_left_corner_y);

    glEnd();

    glPopMatrix();
}


double Graphics::get_center_x()
{
    return center_x;
}


double Graphics::get_center_y()
{
    return center_y;
}


double Graphics::get_width()
{
    return width;
}


double Graphics::get_height()
{
    return height;
}


double Graphics::get_angle(AngleDirection angle_direction, AngleType angle_type)
{
    double angle_return;

    if(angle_direction == CCW)
    {
        angle_return = angle_ccw_rad;
    }
    else
    {
        angle_return = (angle_ccw_rad == 0 ? 0 : 2 - angle_ccw_rad);
    }

    if(angle_type == RADIAN)
    {
        return angle_return;
    }
    else
    {
        return angle_return * 180 / M_PI;
    }
}


int Graphics::get_fps()
{
    return fps;
}


unsigned int Graphics::get_frame_interval_ms()
{
    return frame_interval_ms;
}


void Graphics::set_center_x(double center_x_init)
{
    center_x = center_x_init;
}


void Graphics::set_center_y(double center_y_init)
{
    center_y = center_y_init;
}


void Graphics::set_width(double width_init)
{
    width = width_init;
}


void Graphics::set_height(double height_init)
{
    height = height_init;
}


void Graphics::set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type)
{
    if(angle_init < 0)
    {
        // ERROR
    }

    if(angle_type == RADIAN)
    {
        angle_ccw_rad = angle_init;
    }
    else
    {
        angle_ccw_rad = angle_init * M_PI / 180;
    }

    angle_ccw_rad -= ((int)angle_ccw_rad / 2) * 2;

    if(angle_direction == CW)
    {
        angle_ccw_rad = (angle_ccw_rad == 0 ? 0 : 2 - angle_ccw_rad);
    }
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


void Graphics::set_frame_interval_ms(unsigned int frame_interval_ms_init)
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


void Graphics::load_image(std::string file_name)
{
    SDL_Surface* image = IMG_Load(file_name.c_str());
    if (image == NULL)
    {
        Log::write("ERROR: " + file_name + " doesn't exist");
    }

    height = width * image->h / image->w;

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
