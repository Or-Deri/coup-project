#pragma once
#include "Player.hpp"



namespace coup {

    class Judge : public Player {
        
        private:
        //bool undoTheBribe = false;
            
        public:
            Judge(Game& game, const std::string& name);
            
            //bool isBribeUndo();
            //void setUndo(bool x);

            /**
            * @brief Undoes a bribe action performed by the target player, removing their extra turns.
            * This special ability is available only to Judges.
            *          
            * @param target Reference to the player who performed the bribe.
            * @throws std::runtime_error If the last action was not a bribe.
            * @throws std::runtime_error If the target does not match the last coup target. 
            */
            void undo(Player& target);
    };
}