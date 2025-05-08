#include "Merchant.hpp"
#include "Game.hpp"
#include "Player.hpp"
namespace coup {

    Merchant::Merchant(Game& game, const std::string& name) : Player(game, name){}

    void Merchant::startTurn(){
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