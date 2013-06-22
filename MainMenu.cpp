#include "MainMenu.h"


bool MainMenu::run()
{
    Log::write("MainMenu::run start");
    running = true;

    boost::thread* update_thread;
    boost::thread* render_thread;
    boost::thread* event_thread;

    while(true)
    {
        next_state = NULL;

        update_thread = new boost::thread(&MainMenu::update, this);
        render_thread = new boost::thread(&MainMenu::render, this);
         event_thread = new boost::thread(&MainMenu::event, this);

        update_thread->join();
        render_thread->join();
         event_thread->join();

        delete update_thread;
        delete render_thread;
        delete  event_thread;

        if(next_state != NULL)
        {
            next_state->run();
        }
        else
        {
            Log::write("MainMenu::run finish");
            return true;
        }

        
    }

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
    next_state = NULL;
    running = false;
    running_mtx.unlock();
    Log::write("MainMenu::OnExit finish");
}
