#include "Button.h"

Button::Button(void (*foo)())
{
    action = foo;
}

Button::~Button()
{

}