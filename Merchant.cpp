#include "Merchant.hpp"
#include "Game.hpp"
#include "Player.hpp"
namespace coup {

    Merchant::Merchant(Game& game, const std::string& name) : Player(game, name){}

    void Merchant::startTurn(){

         //If a player was blocked by sanction in the previous turn, the block is removed
        if (lastBlockedBySanction != nullptr){  
            lastBlockedBySanction->setSanctionBlocked(false);
            lastBlockedBySanction = nullptr;
        }

        if(coins() >= 3){
            addCoins(1);
        }
        
    }

    void Merchant::giveBonus(){ // צריך לתת רק שיש לפחות 3 מטבעות
        if(coins() >= 3){
            addCoins(1);
        }
    }

    void Merchant::attackedByArrest(){
        subCoins(2);
    }
    
}