#include "MainMenu.h"


bool MainMenu::run()
{
    running = true;

    boost::thread update_thread(&MainMenu::update, this);
    boost::thread render_thread(&MainMenu::render, this);
    boost::thread event_thread(&MainMenu::event, this);

    update_thread.join();
    render_thread.join();
    event_thread.join();

    poker = new Poker;
    return poker->run();
}


void MainMenu::update()
{
    while(running)
    {

    }
}


void MainMenu::render()
{
    while(running)
    {
        
    }
}


void MainMenu::event()
{
    SDL_Event event;
    while(running)
    {
        SDL_PollEvent(&event);
        Event::OnEvent(&event);
    }
}


void MainMenu::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{

}


void MainMenu::OnLButtonDown(int mX, int mY)
{

}


void MainMenu::OnLButtonUp(int mX, int mY)
{

}


void MainMenu::OnRButtonDown(int mX, int mY)
{

}


void MainMenu::OnRButtonUp(int mX, int mY)
{

}


void MainMenu::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{

}


void MainMenu::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{

}