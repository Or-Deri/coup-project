//orderi429@gmail.com
#include "Judge.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>
#include <iostream>


namespace coup {



    Judge::Judge(Game& game, const std::string& name) : Player(game, name){}

    void Judge::undo(Player& target){
        std::cout << "[DEBUG] Judge undo called with target: " << target.getName() << std::endl;

        if (game->getLastAction() != "bribe") {  
            throw std::runtime_error("The last action is not bribe");
        }

        if(game->getLastTarget() != &target) {               
            throw std::runtime_error("The target player is incorrect");
        }
        if(!this->getInGame()) {               
            throw std::runtime_error("A Judge who has left the game cannot undo bribe");
        }

        target.setExtraTurns(0);

        game->setLastAction("");
        game->setLastPlayer(nullptr);
    }
}