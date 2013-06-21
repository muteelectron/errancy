#include "MainMenu.h"


bool MainMenu::run()
{
    Log::write("MainMenu::run start");
    running = true;

    boost::thread update_thread(&MainMenu::update, this);
    boost::thread render_thread(&MainMenu::render, this);
    boost::thread event_thread(&MainMenu::event, this);

    while(true)
    {
        nextstate = NULL;

        update_thread.join();
        render_thread.join();
        event_thread.join();
        
        if(nextstate != NULL)
        {
            nextstate->run();
        }
        else
        {
            return true;
        }

        running = true;


    }
    Log::write("MainMenu::run finish");
    return true;
}


void MainMenu::update()
{
    Log::write("MainMenu::update start");
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        running_mtx.lock();
    }
    Log::write("MainMenu::update finish");
}


void MainMenu::render()
{
    Log::write("MainMenu::render start");
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        running_mtx.lock();
    }
    Log::write("MainMenu::render finish");
}


void MainMenu::event()
{
    Log::write("MainMenu::event start");
    SDL_Event event;
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        SDL_PollEvent(&event);
        Event::OnEvent(&event);
        running_mtx.lock();
    }
    Log::write("MainMenu::event finish");
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


void MainMenu::OnExit()
{
    Log::write("MainMenu::OnExit start");
    running_mtx.lock();
    running = false;
    running_mtx.unlock();
    Log::write("MainMenu::OnExit finish");
}
