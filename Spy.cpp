#include "Spy.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <stdexcept>




namespace coup {

    Spy::Spy(Game& game, const std::string& name): Player(game, name){
        lastBlockedByArrest = nullptr;
    }


    void Spy::startTurn(){
        
        if (game->turn() != getName()) {
            throw std::runtime_error("Not spy's turn");
        }

        if (lastBlockedByArrest != nullptr){
            lastBlockedByArrest->setArrestBlocked(false);
            lastBlockedByArrest = nullptr;
        }

        //If a player was blocked by sanction in the previous turn, the block is removed
        if (lastBlockedBySanction != nullptr){
            lastBlockedBySanction->setSanctionBlocked(false);
            lastBlockedBySanction = nullptr;
        }


        // מבקש מהמשתמש שחקן מטרה מתוך השחקנים שמשחקים 
        //seeCoins(target);
        //blockArrest(target)


    }

    void Spy::blockArrest(Player& target){
        

        seeCoins(target);

        target.setArrestBlocked(true);
        lastBlockedByArrest = &target; // נרשום כדי שנוכל לנקות אחר כך
    }

    int Spy::seeCoins(Player& target) const {
        return target.coins();
    }

}