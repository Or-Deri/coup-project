#include "Judge.hpp"
#include "Game.hpp"

namespace coup {



    Judge(Game& game, const std::string& name){
        this.game = game;
        this.name = name;
    }
    void startTurn(){}
    bool isBribeUndo() const{
        return this.undoTheBribe ;
    }

    void setUndo(bool x){
        this.undoTheBribe = x;
    }

    void undoBribe(){

    }
}