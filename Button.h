#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:

    Button(void (*foo)());
    ~Button();

private:

    void (*action)();
};

#endif