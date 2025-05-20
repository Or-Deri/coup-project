#include "General.hpp"
#include "Game.hpp"
#include <stdexcept>
#include <iostream>


namespace coup {

    General::General(Game& game, const std::string& name)  :Player(game, name){
        //undoTheCoup = false;
    }

    void General::undo(Player& target){

        //Can undo coup only immediately after the action
        if(game->getLastAction() != "coup"){
            throw std::runtime_error("The last action is not coup");
        }

        //Checks if undo is to the correct player
        if (game->getLastTarget() != &target){
            throw std::runtime_error("The target player is incorrect");
        }
        
        if (coins() < 5){
            throw std::runtime_error ("Not enough coins");
        }

        subCoins(5);

        target.setInGame(true);
        //undoTheCoup = false;
        game->setLastAction("");
        game->setLastPlayer(nullptr);
    }

    // bool General::isCoupUndo ()const {
    //     return undoTheCoup;
    // }
        
    // void General::setUndo(bool x){
    //     undoTheCoup = x;
    // }
}