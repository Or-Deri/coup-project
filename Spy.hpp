//orderi429@gmail.com
#pragma once
#include "Player.hpp"
#include <string>


namespace coup {
    
    class Spy : public Player {

        private:
            std::vector <Player*> lastBlockedArrestLlist;
        
        public:
            Spy(Game& game, const std::string& name);

            /**
            * @brief This method is called at the beginning of the player's turn.
            * It resets any sanction block that was applied in the previous round,
            * and enforces the rule that a player with 10 or more coins must perform a coup.
            * 
            * @throws std::runtime_error If it not the player's turn
            * @throws std::runtime_error If the player has 10 or more coins, he mast to do undo
            */
            void startTurn() override;
            /**
            * @brief Blocks the target player from using the arrest action in their next turn.
            * 
             * This special ability is available only to Spy players. It does not cost coins and is not a full turn action.
             * The function also sets this Spy as the last actor, and stores the target in the internal list 
             * to allow resetting the block at the start of the next round.
             * 
             * If the Spy has 10 or more coins, they must perform a coup and cannot use this ability.
             * 
             * @param target Reference to the player whose arrest ability will be blocked.
             * 
             * @throws std::runtime_error If the Spy has 10 or more coins and must perform a coup.
            */
            void blockArrest(Player& target);        
    };
}