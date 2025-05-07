#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"

namespace coup {
 
    Governor::Governo(Game& game, const std::string& name) {
        this.game = game;
        this.name = name;
    }

    void setUndo(bool x){
        this.undoTheTax = x;
    }

    bool isTaxUndo() const{
        return this.undoTheTax;
    }

    void Governor::undo(Player target){
    
    }
    
    void tax(){
        addCoins(3);
    }
}