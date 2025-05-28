//orderi429@gmail.com
#pragma once
#include "Player.hpp"



namespace coup {

    class Judge : public Player {
        

            
        public:
            Judge(Game& game, const std::string& name);
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