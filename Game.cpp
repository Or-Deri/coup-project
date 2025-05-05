#include "Game.hpp"
#include "Player.hpp"


Game::Game(){

    Turn = 0;
}

void Game::addPlayer(Player* p){
    Players.push_back(p);
}

Player* Game:: currentPlayer(){
    return Players[Turn];
}

void Game::nextTurn(){
    int current = Turn;
    Turn = (Turn + 1) % Players.size();

    while(!Players[currentPlayer].isInGame){

        Turn = (Turn + 1) % Players.size();
        
        if(current == Turn){
            throw std::runtime_error("No active players");
        }
    }
}

