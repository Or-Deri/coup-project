#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"

namespace coup {
 
    Governor::Governor(Game& game, const std::string& name): Player(game, name)  {}
    

    void Governor::setUndo(bool x){
        undoTheTax = x;
    }

    bool Governor::isTaxUndo() const{
        return undoTheTax;
    }

    void Governor::undo(Player target){
        if (game->lastAction != "tax") {                  //Governor can undo only tax
            throw std::runtime_error("Governor cannot undo "+game->lastAction);
        }


        Governor* governor = dynamic_cast<Governor*>(&(game->lastPlayer));
        if(governor){                   // If the player is Governor, he received 3 coins 
            game->lastPlayer->subCoins(3);
        }
        else{                          // Everyone else gets 2 coins
            game->lastPlayer->subCoins(2);
        }
    }
    
    void Governor::tax(){
        addCoins(3);
    }
}