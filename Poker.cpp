#include "Poker.h"


bool Poker::run()
{
    Log::write("Poker has started");
    running = true;

    boost::thread render_thread(&Poker::render, this);
    boost::thread update_thread(&Poker::update, this);
    boost::thread game_loop_thread(&Poker::game_loop, this);
    boost::thread event_thread(&Poker::event, this);

    render_thread.join();
    update_thread.join();
    game_loop_thread.join();
    event_thread.join();

    return true;
}


void Poker::render()
{
    while(running)
    {

    }
}


void Poker::update()
{
    while(running)
    {

    }
}


void Poker::game_loop()
{
    while(running)
    {

    }
}


void Poker::event()
{
    SDL_Event event;
    while(running)
    {
        SDL_PollEvent(&event);
        Event::OnEvent(&event);
    }
}


void Poker::OnExit()
{
    Log::write("Poker OnExit");
    running = false;
}
