#pragma once
#include "Player.hpp"

namespace coup {

    class General : public Player {
    
    private:
        //bool undoTheCoup = false;
    
    public:
        General(Game& game, const std::string& name);
        //bool isCoupUndo() const;
        //void setUndo(bool x);
        
        /**
        * @brief Undoes a coup action performed on a target player, restoring them to the game.
        * This special ability is available only to Generals, cost 5 coins. 
        * 
        * @param target Reference to the player who was eliminated and should be restored.
        * 
        * @throws std::runtime_error If the last action was not a coup.
        * @throws std::runtime_error If the target does not match the last coup target.
        * @throws std::runtime_error If the General does not have at least 5 coins.
        */
        void undo(Player& target); 
    };

}
