#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <stdexcept>


namespace coup {
 
    Governor::Governor(Game& game, const std::string& name): Player(game, name)  {}
    

    void Governor::setUndo(bool x){
        undoTheTax = x;
    }

    bool Governor::isTaxUndo() const{
        return undoTheTax;
    }

    void Governor::undo(Player& target){
 
        if (game->getLastAction() != "tax" || game->getLastPlayer() != &target) {                  //Governor can undo only tax , and only right after it was done
            throw std::runtime_error("Governor cannot undo "+game->getLastAction());
        }


        Governor* governor = dynamic_cast<Governor*>(game->getLastPlayer());
        if(governor){                   // If the player is Governor, he received 3 coins 
            game->getLastPlayer()->subCoins(3);
        }
        else{                          // Everyone else gets 2 coins
            game->getLastPlayer()->subCoins(2);
        }

        game->setLastAction("");
        game->setLastPlayer(nullptr);
    }
    
    void Governor::tax(){
        addCoins(3);
        
        lastIBlockedArrest = nullptr;


        game->setLastAction("tax");
        game->setLastPlayer(this);
        game->nextTurn();
    }
}