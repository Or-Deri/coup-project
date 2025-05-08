#include "General.hpp"
#include "Game.hpp"
#include <stdexcept>



namespace coup {

    General::General(Game& game, const std::string& name)  :Player(game, name){}

    void General::undo(Player& target){
        if (coins() < 5){
            throw std::runtime_error ("Not enough coins");
        }

        subCoins(5);
        setUndo(false);
    }

        
    bool General::isCoupUndo ()const {
        return undoTheCoup;
    }
        
    void General::setUndo(bool x){
        undoTheCoup = x;
    }

    void General::ReturnsCoin(Player& target){
        target.subCoins(1);
        addCoins(1);
    }

}