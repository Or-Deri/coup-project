#include "Governor.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <stdexcept>


namespace coup {
 
    Governor::Governor(Game& game, const std::string& name): Player(game, name)  {}
    

    // void Governor::setUndo(bool x){
    //     undoTheTax = x;
    // }

    // bool Governor::isTaxUndo() const{
    //     return undoTheTax;
    // }

    void Governor::undo(Player& target){
 
        if (game->getLastAction() != "tax"){ 
            throw std::runtime_error("The last action is not tax");
        }

        if(game->getLastTarget() != &target) {               
            throw std::runtime_error("The target player is incorrect");
        }
        Governor* governor = dynamic_cast<Governor*>(game->getLastTarget());
        if(governor){                   // If the player is Governor, he received 3 coins 
            target.subCoins(3);
        }
        else{                          // Everyone else gets 2 coins
            target.subCoins(2);
        }

        //setUndo(false);

        game->setLastAction("");
        game->setLastPlayer(nullptr);
        
    }
    
    void Governor::tax() {

        if (game->turn() != getName()) {
            throw std::runtime_error("It is not your turn");
        }    
        
        if (coins() >= 10) {
            throw std::runtime_error("You must perform a coup this turn");
        }

        if(sanctionBlocked){
            throw std::runtime_error("You are blocked by sanction");
        }

        addCoins(3);
        setLastTargetArrest(nullptr);

        game->setLastAction("tax");
        game->setLastPlayer(this);
        game->setLastTarget(this);
    }
}