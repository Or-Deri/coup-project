#pragma once
#include "Player.hpp"

namespace coup {

    class Governor : public Player {

        private:
        
            //bool undoTheTax = false;
        
        public:
        
            Governor(Game& game, const std::string& name);
        
            //void setUndo(bool x);
            //bool isTaxUndo() const;

            /**
            * @brief Undoes a tax action performed by another player, removing the coins they gained.
            * 
            * This special ability is available only to Governors.
            * If the taxed player is also a Governor, they lose 3 coins, otherwise they lose 2 coins.
            * 
            * @param target Reference to the player who performed the tax action.
            * @throws std::runtime_error If the last action was not a tax, or the target is not the last acting player.
            * @throws std::runtime_error If the target does not match the last coup target.
            */ 
            void undo(Player& target);

            /**
            * @brief Adds 3 coin to the governor , it resets the arrest block trackin ,
            * and allows governors to optionally undo the action
            * 
            * @throws std::runtime_error If it is not the player's turn.
            * @throws std::runtime_error If the player bloked by sanction
            */
            void tax() override;
    };

}