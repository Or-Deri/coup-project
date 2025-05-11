#include "Judge.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>


namespace coup {



    Judge::Judge(Game& game, const std::string& name) : Player(game, name){}
    
    bool Judge::isBribeUndo(){
        return undoTheBribe ;
    }

    void Judge::setUndo(bool x){
        undoTheBribe = x;
    }

    void Judge::undo(Player& target){

        if (game->getLastAction() != "bribe" || game->getLastPlayer() != &target) {                  //Judge can undo only tax ,and only right after it was done
            throw std::runtime_error("--------------Judge cannot undo -----------------");
        }

        target.subExtraTurns();
        target.subExtraTurns();

        game->setLastAction("");
        game->setLastPlayer(nullptr);
        
    }
}