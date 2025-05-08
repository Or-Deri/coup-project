#include "Judge.hpp"
#include "Game.hpp"
#include "Player.hpp"

namespace coup {



    Judge::Judge(Game& game, const std::string& name) : Player(game, name){}
    
    bool Judge::isBribeUndo(){
        return undoTheBribe ;
    }

    void Judge::setUndo(bool x){
        undoTheBribe = x;
    }

    void Judge::undo(Player* target){
        if (game->lastAction != "bribe") {
            throw std::runtime_error("Judge cannot undo"+game->lastAction);
        }
            
    }
}