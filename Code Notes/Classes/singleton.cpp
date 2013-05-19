#include "singleton.h"

Game* Game::sm_game = nullptr;

Game* Game::Get()
{
    if(sm_game == nullptr)
    {
        sm_game = new Game();
    }
    return sm_game;
}

void Game::Release()
{
    if(sm_game != nullptr)
    {
        delete sm_game;
    }
    sm_game = nullptr;
}