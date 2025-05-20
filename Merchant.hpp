#pragma once
#include "Player.hpp"
#include <string>


namespace coup {

    class Merchant : public Player {
            
        public:
            Merchant(Game& game, const std::string& name);

            /**
            * @brief This method is called at the beginning of the Merchant turn.
            * It resets any sanction block that was applied in the previous round,
            * and enforces the rule that a player with 10 or more coins must perform a coup.
            * if the Merchant has 3 or more coins at the start of the turn, they receive 1 bonus coin.
            * 
            * @throws std::runtime_error If it not the player's turn
            * @throws std::runtime_error If the player has 10 or more coins, he mast to do undo
            */
            void startTurn() override;

            void attackedByArrest();
            
        
    };
}