#include "MainMenu.h"


bool MainMenu::run()
{
    poker = new Poker;
    return poker->run();
}