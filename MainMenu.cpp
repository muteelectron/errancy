#include "MainMenu.h"


bool MainMenu::run()
{
    Log::write("MainMenu::run start");

    boost::function<void()> but_action_init;
    but_action_init = boost::bind(&MainMenu::poker_run, this);
    poker_new_game_but = new Button("poker_run.button", but_action_init);

    running = true;

    boost::thread* update_thread;
    boost::thread* event_thread;

    while(true)
    {
        next_state = NULL;

        update_thread = new boost::thread(&MainMenu::update, this);
         event_thread = new boost::thread(&MainMenu::event, this);

        render();

        update_thread->join();
         event_thread->join();

        delete update_thread;
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
    running_mtx.unlock();    

    Log::write("MainMenu::update finish");
}


void MainMenu::render()
{
    Log::write("MainMenu::render start");

    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        new_game_but_mtx.lock();
        poker_new_game_but->render();
        new_game_but_mtx.unlock();

        SDL_GL_SwapBuffers();

        running_mtx.lock();
    }
    running_mtx.unlock();

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
    running_mtx.unlock();

    Log::write("MainMenu::event finish");
}


void MainMenu::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
    new_game_but_mtx.lock();
    poker_new_game_but->mouse_event((double)mX / SDL_GetVideoSurface()->w, 
                                    (double)mY / SDL_GetVideoSurface()->h, false);
    new_game_but_mtx.unlock();
}


void MainMenu::OnLButtonDown(int mX, int mY)
{
    new_game_but_mtx.lock();
    poker_new_game_but->mouse_event((double)mX / SDL_GetVideoSurface()->w, 
                                    (double)mY / SDL_GetVideoSurface()->h, true);
    new_game_but_mtx.unlock();
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


void MainMenu::poker_run()
{
    running_mtx.lock();

    next_state = new Poker();
    running = false;

    running_mtx.unlock();
}
