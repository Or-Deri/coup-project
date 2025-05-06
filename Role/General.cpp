#include "General.hpp"
#include "Game.hpp"


namespace coup {

    General::General(Game& game, const std::string& name){
        this.game = game;
        this.name = name;
    }
    void startTurn(){}

    void General::undoCoup(){
        if (this.getCoins < 5){
            throw runtime_error ("Not enough coins");
        }

        this.subCoins(5);
        setUndo(false);
    }

        
    bool General::isCoupUndo ()const {
        return this.undoTheCoup;
    }
        
    void General::setUndo(book x){
        this.undoTheCoup = x;
    }

    void General::ReturnsCoin(player& target){
        target.subCoins(1);
        this.addCoins(1);
    }

}