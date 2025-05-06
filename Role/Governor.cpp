#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"

namespace coup {
 
    Governor(Game& game, const std::string& name) {
        this.game = game;
        this.name = name;
    }

    void startTurn(){}
    void setUndo(bool x){
        this.undoTheTax = x;
    }

    bool isTaxUndo() const{
        return this.undoTheTax;
    }

    void undoTax(){
        if()
    }
    
    void Governor::tax(){
        addCoins(3);
    }
}