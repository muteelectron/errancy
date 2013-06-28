#include "Button.h"

Button::Button(std::string file_name, boost::function<void()> action_init)
{
    if(std::ifstream(file_name.c_str()) == NULL)
    {
        Log::write("ERROR: " + file_name + " doesn't exist");
    }
    
    state = NORMAL;

    action = action_init;

    std::string transparency_map_file_name;
    std::string image_file_name;
    std::string image_hovered_file_name;

    std::ifstream input(file_name.c_str());
    input >> transparency_map_file_name;
    input >> image_file_name;
    input >> image_hovered_file_name;

    transparency_map = Surface::OnLoad(transparency_map_file_name);
    image = new Graphics(image_file_name);
    image_hovered = new Graphics(image_hovered_file_name);
}

Button::~Button()
{
    SDL_FreeSurface(transparency_map);
    delete image;
    delete image_hovered;
}


bool Button::mouse_event(int click_x, int click_y, bool clicked)
{
    click_x -= image->get_center_x();
    click_y -= image->get_center_y();

    if(abs(click_x) <= image->get_width() && abs(click_y) <= image->get_height())
    {
        Uint32 pixel;
        int x;
        int y;
        x = click_x * SDL_GetVideoSurface()->w;
        y = click_y * SDL_GetVideoSurface()->h;

        pixel =  *(Uint32*)((Uint8*)transparency_map->pixels +
                   transparency_map->format->BytesPerPixel * x + transparency_map->pitch * y);

        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
        SDL_GetRGBA(pixel, transparency_map->format, &r, &g, &b, &a);

        if(a > 0)
        {
            if(clicked)
            {
                state = PRESSED;
                action();
            }
            else
            {
                state = HOVERED;
            }
            return true;
        }
        else
        {
            state = NORMAL;
            return false;
        }
    }
    else
    {
        state = NORMAL;
        return false;
    }
}


void Button::render()
{
    switch(state)
    {
        case NORMAL:
            image->render();
            break;
        case HOVERED:
            image_hovered->render();
            break;
        case PRESSED:
            break;
    }
}


void Button::set_state(ButtonState state_init)
{
    state = state_init;
}


ButtonState Button::get_state()
{
    return state;
}


int Button::get_center_x()
{
    return image->get_center_x();
}


void Button::set_center_x(int x_init)
{
    image->set_center_x(x_init);
    image_hovered->set_center_x(x_init);
}


int Button::get_center_y()
{
    return image->get_center_y();
}


void Button::set_center_y(int y_init)
{
    image->set_center_y(y_init);
    image_hovered->set_center_y(y_init);
}


double Button::get_angle(AngleDirection angle_direction, AngleType angle_type)
{
    return image->get_angle(angle_direction, angle_type);
}


void Button::set_angle(double angle_init, AngleDirection angle_direction, AngleType angle_type)
{
    image->set_angle(angle_init, angle_direction, angle_type);
    image_hovered->set_angle(angle_init, angle_direction, angle_type);
}
