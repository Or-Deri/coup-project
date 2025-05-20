#include "Spy.hpp"
#include "Game.hpp"
#include <stdexcept>




namespace coup {

    Spy::Spy(Game& game, const std::string& name): Player(game, name){
        lastBlockedArrest = nullptr;
    }



    void Spy::startTurn(){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        //If a player was blocked by sanction in the previous turn, the block is removed
        if (lastBlockedBySanction != nullptr){
            lastBlockedBySanction->setSanctionBlocked(false);
            lastBlockedBySanction = nullptr;
        }

        if (lastBlockedArrest != nullptr){
            lastBlockedArrest->setArrestBlocked(false);
            lastBlockedArrest = nullptr;
        }
    }

    void Spy::blockArrest(Player& target){ 
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        setLastTargetArrest(nullptr);
        game->setLastTarget(nullptr);
        game->setLastAction("blockArrest");
        game->setLastPlayer(this);

        target.setArrestBlocked(true);
        lastBlockedArrest = &target; 
    }
}