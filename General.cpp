//orderi429@gmail.com
#include "General.hpp"
#include "Game.hpp"
#include <stdexcept>
#include <iostream>


namespace coup {

    General::General(Game& game, const std::string& name)  :Player(game, name){}

    void General::undo(Player& target){

        //Can undo coup only immediately after the action
        if(game->getLastAction() != "coup"){
            throw std::runtime_error("The last action is not coup");
        }

        //Checks if undo is to the correct player
        if (game->getLastTarget() != &target){
            throw std::runtime_error("The target player is incorrect");
        }
        
        if(!this->getInGame() && this != &target){               
            throw std::runtime_error("A General who has left the game cannot undo coup");
        }

        if (coins() < 5){
            throw std::runtime_error ("Not enough coins");
        }

        subCoins(5);

        target.setInGame(true);
        game->setLastAction("");
        game->setLastPlayer(nullptr);
    }


}