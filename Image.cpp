#include "Image.h"

Image::Image(char* filename)
{
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL)
    {
        // ERROR
    }

    if ( (image->w & (image->w - 1)) != 0 )
    {
        // ERROR: image.bmp's width is not a power of 2
    }


    if ( (image->h & (image->h - 1)) != 0 )
    {
        // ERROR: image.bmp's height is not a power of 2
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
        // ERROR: the image is not truecolor...this will break
    }

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, nofcolors, image->w, image->h,
                      texture_format, GL_UNSIGNED_BYTE, image->pixels);

    width  = image->w;
    height = image->h;
    angle  = 0;
    x      = 0;
    y      = 0;

    SDL_FreeSurface(image);

}


Image::~Image()
{
    glDeleteTextures( 1, &texture );
}


void Image::render()
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();

    glRotatef(angle, 0, 0, 1);

    glBegin(GL_QUADS);

        glTexCoord2d(0, 0);
        glVertex2d(x, y);

        glTexCoord2d(1, 0);
        glVertex2d(x + width, y);

        glTexCoord2d(1, 1);
        glVertex2d(x + width, y + height);

        glTexCoord2d(0, 1);
        glVertex2d(x, y + height);

    glEnd();

    glPopMatrix();
}


void Image::set_x(int x_init)
{
    x = x_init;
}


void Image::set_y(int y_init)
{
    y = y_init;
}


void Image::set_width(int width_init)
{
    width = width_init;
}


void Image::set_y(int height_init)
{
    height = height_init;
}


void Image::set_angle(double angle_init)
{
    angle = angle_init;
}


int Image::get_x()
{
    return x;
}


int Image::get_y()
{
    return y;
}


int Image::get_width()
{
    return width;
}


int Image::get_height()
{
    return height;
}


double Image::get_angle()
{
    return angle;
}
