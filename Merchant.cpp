#include "Merchant.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>
namespace coup {

    Merchant::Merchant(Game& game, const std::string& name) : Player(game, name){}

    void Merchant::startTurn() {
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }
        //If a player was blocked by sanction in the previous turn, the block is removed
        if (lastBlockedBySanction != nullptr){  
            lastBlockedBySanction->setSanctionBlocked(false);
            lastBlockedBySanction = nullptr;
        }

        if(coins() >= 3){
            addCoins(1);
        }
    }

    void Merchant::attackedByArrest(){
        subCoins(2);
    }
    
}