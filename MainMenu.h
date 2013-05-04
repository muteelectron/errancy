#ifndef MENU_H
#define MENU_H

#include "ProgramState.h"
#include "Poker.h"

class MainMenu : public ProgramState
{
public:

    bool run();

private:

    Poker* poker;
};

#endif