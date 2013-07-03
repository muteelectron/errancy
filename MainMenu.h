#ifndef MENU_H
#define MENU_H

#include "ProgramState.h"
#include "Poker.h"
#include "Button.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "Log.h"

class MainMenu : public ProgramState
{
public:

    bool run();

private:

    bool running;

    ProgramState* next_state;

    void update();
    void render();
    void event();

    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
    void OnLButtonDown(int mX, int mY);
    void OnLButtonUp(int mX, int mY);
    void OnRButtonDown(int mX, int mY);
    void OnRButtonUp(int mX, int mY);
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
    void OnExit();

    void poker_run();

    Button* poker_new_game_but;

    boost::mutex running_mtx;
    boost::mutex new_game_but_mtx;
};

#endif
