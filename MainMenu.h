#ifndef MENU_H
#define MENU_H

#include "ProgramState.h"

class MainMenu : public ProgramState
{
public:

    MainMenu();
    ~MainMenu();

    bool run();
};

#endif