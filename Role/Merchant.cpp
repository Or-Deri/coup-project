#include "Merchant.hpp"
#include "Game.hpp"

namespace coup {

    Merchant(Game& game, const std::string& name){
        this.game = game;
        this.name = name;
    }

    void GiveBonus(){ // צריך לתת רק שיש לפחות 3 מטבעות
        if(this.getCoins >= 3){
            this.addCoins(1);
        }
    }

    void AttackedByArrest(){
        this.subCoins(2);
    }
    
}