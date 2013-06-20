#include "Poker.h"


bool Poker::run(char* template_file_name)
{
    running = true;

    boost::thread render_thread(&Poker::render, this);
    boost::thread game_loop_thread(&Poker::game_loop, this);
    boost::thread event_thread(&Poker::event, this);

    render_thread.join();
    game_loop_thread.join();
    event_thread.join();

    return true;
}


void Poker::render()
{
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        running_mtx.lock();
    }
}


void Poker::game_loop()
{
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        running_mtx.lock();
    }
}


void Poker::event()
{
    SDL_Event event;
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();
        SDL_PollEvent(&event);
        Event::OnEvent(&event);
        running_mtx.lock();
    }
}


void Poker::OnExit()
{
    running_mtx.lock();
    running = false;
    running_mtx.unlock();
}
