#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"

namespace coup {
 
    Governor(Game& game, const std::string& name) {
        this.game = game;
        this.name = name;
    }

    void setUndo(bool x){
        this.undoTheTax = x;
    }

    bool isTaxUndo() const{
        return this.undoTheTax;
    }

    void undo(player target){
    
    }
    
    void Governor::tax(){
        addCoins(3);
    }
}