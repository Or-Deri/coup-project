//orderi429@gmail.com
#include "Spy.hpp"
#include "Game.hpp"
#include <stdexcept>




namespace coup {

    Spy::Spy(Game& game, const std::string& name): Player(game, name){}

    void Spy::startTurn(){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }

        //If a player was blocked by sanction in the previous turn, the block is removed
        if (lastSanctionedTarget != nullptr){
            lastSanctionedTarget->setSanctionBlocked(false);
            lastSanctionedTarget = nullptr;
        }

        for (Player* p : lastBlockedArrestLlist){
            if (p != nullptr) {
                p->setArrestBlocked(false);
            }
        }
        lastBlockedArrestLlist.clear();

    }

    void Spy::blockArrest(Player& target){ 
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        setLastTargetArrest(nullptr);
        game->setLastTarget(nullptr);
        game->setLastAction("block arrest");
        game->setLastPlayer(this);

        target.setArrestBlocked(true);
        lastBlockedArrestLlist.push_back(&target);
    }
}