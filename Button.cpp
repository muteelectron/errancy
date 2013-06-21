#include "Button.h"

Button::Button(char* file_name, void (*foo)())
{
    button_state = NORMAL;

    action = foo;

    char* transparrency_map_file_name;
    char* image_file_name;
    char* image_hovered_file_name;
    char* image_pressed_file_name;

    std::ifstream input(file_name);
    input >> transparrency_map_file_name;
    input >> image_file_name;
    input >> image_hovered_file_name;
    input >> image_pressed_file_name;

    transparrency_map = Surface::OnLoad(transparrency_map_file_name);
    image = new Graphics(image_file_name);
    image_hovered = new Graphics(image_hovered_file_name);
    image_pressed = new Graphics(image_pressed_file_name);
}

Button::~Button()
{

}


bool Button::hover(int x, int y)
{
    return true;
}


bool Button::press(int x, int y)
{
    return true;
}


void Button::render()
{
    switch(button_state)
    {
        case NORMAL:
            image->render();
            break;
        case HOVERED:
            image_hovered->render();
            break;
        case PRESSED:
            image_pressed->render();
            break;
    }
}
