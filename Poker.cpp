#include "Poker.h"


Poker::Poker()
: num_of_seats(10)
{

}


bool Poker::run()
{
    Log::write("Poker::run start");

    if(std::ifstream("choosen_save.txt") != NULL)
    {
        std::ifstream path_to_save("choosen_save.txt");
        char* save_file_name;
        path_to_save >> save_file_name;

        load_game(save_file_name);
    }
    else
    {
        load_template_game();
    }

    running = true;

    boost::thread game_loop_thread(&Poker::game_loop, this);
    boost::thread event_thread(&Poker::event, this);

    render();

    game_loop_thread.join();
    event_thread.join();

    CleanUp();

    Log::write("Poker::run finish");

    return true;
}


void Poker::CleanUp()
{
    Log::write("Poker::CleanUp start");

    for(int i = 0; i < num_of_seats; ++i)
    {
        delete[] seat[i];
    }
    delete[] seat;

    delete[] pack;

    Log::write("Poker::CleanUp finish");
}


void Poker::render()
{
    Log::write("Poker::render start");

    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i = 0; i < num_of_seats; ++i)
        {
            chair[i]->render();
            
            seat_mtx[i].lock();

                if(seat[i] != NULL)
                {
                    seat[i]->render();
                }

            seat_mtx[i].unlock();
        }

        table_mtx.lock();
            table->render();
        table_mtx.unlock();

        pack_mtx.lock();
            pack->render();
        pack_mtx.unlock();

        for(int i = 0; i < 5; ++i)
        {
            table_card_mtx[i].lock();
                if(table_card[i] == NULL)
                {
                    break;
                }
                else
                {
                    table_card[i]->render();
                }
            table_card_mtx[i].unlock();
        }

        SDL_GL_SwapBuffers();

        running_mtx.lock();
    }
    running_mtx.unlock();

    Log::write("Poker::render finish");
}


void Poker::game_loop()
{
    running_mtx.lock();
    while(running)
    {
        running_mtx.unlock();

        while(num_of_players > 1)
        {
            poker_round();
            button = closer_seat(button + 1);
        }

        running_mtx.lock();
    }
    running_mtx.unlock();
}


void Poker::poker_round()
{
    bank = 0;

    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < num_of_seats; ++j)
        {
            seat_mtx[j].lock();

                if(seat[j] != NULL)
                {
                    seat[j]->pick_card(pack->pop_top());
                }

            seat_mtx[j].unlock();
        }
    }

    // BLINDS
    cur_player = closer_seat(button + 1);

    seat_mtx[cur_player].lock();
        seat[cur_player]->give_cash(small_blind);
    seat_mtx[cur_player].unlock();

    cur_player = closer_seat(cur_player + 1);

    seat_mtx[cur_player].lock();
        seat[cur_player]->give_cash(big_blind);
    seat_mtx[cur_player].unlock();

// УТОЧНИТЬ: ОСТАЛЬНЫЕ ПОВЫШАЮТ ДО БОЛЬШОГО БЛАИНДА 
//           ИЛИ ОЛ-ИНА ИГРОКА С БОЛЬШИМ БЛАИНДОМ
    highest_stake = big_blind;
    highest_stake_player = cur_player;
    cur_player = closer_seat(cur_player + 1);
    // PREFLOP
    trade_round();
    if(highest_stake == big_blind)
    {
        highest_stake_player = closer_seat(cur_player + 1);
        trade_round();
    }

    // FLOP
    pack_mtx.lock();
        table_card_mtx[0].lock();
            table_card[0] = pack->pop_top();
        table_card_mtx[0].unlock();

        table_card_mtx[1].lock();
            table_card[1] = pack->pop_top();
        table_card_mtx[1].unlock();

        table_card_mtx[2].lock();
            table_card[2] = pack->pop_top();
        table_card_mtx[2].unlock();
    pack_mtx.unlock();

    cur_player = closer_seat(closer_seat(closer_seat(button + 1)
                 + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();

    // TURN
    pack_mtx.lock();
    table_card_mtx[3].lock();
    table_card[3] = pack->pop_top();
    table_card_mtx[3].unlock();
    pack_mtx.unlock();

    cur_player = closer_seat(closer_seat(closer_seat(closer_seat
                 (button + 1) + 1) + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();

    // RIVER
    pack_mtx.lock();
    table_card_mtx[4].lock();
        table_card[4] = pack->pop_top();
    table_card_mtx[4].unlock();
    pack_mtx.unlock();

    cur_player = closer_seat(closer_seat(closer_seat(closer_seat
                 (closer_seat(button + 1) + 1) + 1) + 1) + 1);
    highest_stake = 0;
    highest_stake_player = cur_player;

    trade_round();
}


void Poker::trade_round()
{
    int stake;

    do
    {
        seat_mtx[cur_player].lock();
            stake = seat[cur_player]->stake(highest_stake);
        seat_mtx[cur_player].unlock();

        bank += stake;
        if(stake == 0)
        {
            // CHECK
        }
        else if(stake > 0 && highest_stake == 0)
        {
            // BET
            highest_stake = stake;
            highest_stake_player = cur_player;
        }
        else if(stake > 0 && highest_stake > 0)
        {
            // RAISE
            highest_stake = stake;
            highest_stake_player = cur_player;
        }
        else if(highest_stake > 0 && stake < highest_stake)
        {
            // ALL IN
        }
        else if(stake == highest_stake)
        {
            // CALL
        }
        else if(stake == -1)
        {
            // FOLD
            Card** folded_card;

            seat_mtx[cur_player].lock();
                folded_card = seat[cur_player]->fold();
            seat_mtx[cur_player].unlock();

            pack_mtx.lock();
                pack->push_bot(folded_card[0]);
                pack->push_bot(folded_card[1]);
            pack_mtx.unlock();
        }
        cur_player = closer_seat(cur_player + 1);
    }while(cur_player != highest_stake_player);
}


void Poker::event()
{
    Log::write("Poker::event start");

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

    Log::write("Poker::event finish");
}


void Poker::save_game(char* save_file_name)
{

}


void Poker::load_game(char* load_file_name)
{
    // UNDONE

    ifstream load_file(load_file_name);

    if()
    {

    }

    bool* seat_taken;
    seat_taken = new bool[num_of_seats];

    load_file.read((char*)&user_seat, sizeof(int));

    num_of_players = 0;
    for(int i = 0; i < num_of_seats; ++i)
    {
        if(seat_taken[i])
        {
            ++num_of_players;
            if(i != user_seat)
            {
                load_file.read((char*)seat[i], sizeof(PokerBot));
            }
            else
            {
                load_file.read((char*)seat[i], sizeof(PokerPlayer));
            }
        }
        else
        {
            seat[i] = NULL;
        }
    }

    int cards_in_pack;
    Card* card_temp;
    load_file.read((char*)cards_in_pack, sizeof(int));
    for(int i = 0; i < cards_in_pack; ++i)
    {
        card_temp = new Card();
        load_file.read((char*)card_temp, sizeof(Card));
        pack->push_bot(card_temp);
    }

    load_file.read((char*)&small_blind, sizeof(int));
    load_file.read((char*)&big_blind, sizeof(int));
}


void Poker::load_template_game()
{
    num_of_players = 10;
    user_seat = 0;

    seat = new PokerPlayer*[num_of_players];
    seat_mtx = new boost::mutex[num_of_seats];

    seat[user_seat] = new PokerUser("graphics/player.graphics");
    seat[user_seat]->pick_cash(10000);

    for(int i = 1; i < num_of_players; ++i)
    {
        seat[i] = new PokerBot("graphics/player.graphics");
        seat[i]->pick_cash(10000);
    }

    pack = new Pack("graphics/cards/card_back.graphics");

    Card* card_temp;
    Graphics* card_back;
    Graphics* card_front;
    card_front = new Graphics("graphics/cards/card_back.graphics");

    std::string file_path;
    std::string file_extension;
    std::string file_name_temp;
    CardSuit cur_suit;
    int card_value;

    file_path      = "graphics/cards/";
    file_extension = ".graphics";
    file_name_temp = "X00";
    for(int i = 0; i < 52; ++i)
    {
        switch(i / 13)
        {
            case 0:
                file_name_temp[0] = 'C';
                cur_suit = CLUBS;
                break;
            case 1:
                file_name_temp[0] = 'D';
                cur_suit = DIAMONDS;
                break;
            case 2:
                file_name_temp[0] = 'H';
                cur_suit = HEARTS;
                break;
            case 3:
                file_name_temp[0] = 'S';
                cur_suit = SPADES;
                break;
        }

        card_value = (i % 13) + 2;

        file_name_temp[1] = card_value / 10 + 48;
        file_name_temp[2] = card_value % 10 + 48;
        card_front = new Graphics(file_path + file_name_temp + file_extension);
        card_temp = new Card(cur_suit, card_value, card_front, card_back);
        pack->push_bot(card_temp);
    }
    pack->shuffle();

    table = new Graphics("graphics/table.graphics");

    chair = new Graphics*[num_of_seats];
    for(int i = 0; i < num_of_seats; ++i)
    {
        chair[i] = new Graphics("graphics/chair.graphics");
    }

    table_card = new Card*[5];
    table_card_mtx = new boost::mutex[5];
    small_blind = 2;
    big_blind = 4;
    button = 0;
}


void Poker::OnExit()
{
    Log::write("Poker::OnExit start");
    running_mtx.lock();
    running = false;
    running_mtx.unlock();
    Log::write("Poker::OnExit finish");
}


int Poker::closer_seat(int seat_num)
{
    if(seat[seat_num] != NULL)
    {
        return seat_num;
    }

    int i;
    i = seat_num;

    do
    {
        ++i;
        if(i == num_of_seats)
        {
            i = 0;
        }
    }while(seat[i] == NULL && i != seat_num);
    if(seat[i] != NULL)
    {
        return i;
    }
    else
    {
        // ERROR: THERE AREN'T ANY PLAYERS
    }
}
