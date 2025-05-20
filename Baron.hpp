#pragma once
#include "Player.hpp"

namespace coup {
    
    class Baron : public Player{

        public:
        

            Baron(Game& game, const std::string& name);

            /**
            * @brief Adds 1 coin  to the Baron also if he under sancition,
            * it resets the arrest block trackin.
            * 
            * @throws std::runtime_error If it is not the player's turn.
            */
            void gather() override;

            /**
            * @brief Allows the Baron to invest 3 coins in exchange for 6 coins.
            * This special action is unique to the Baron. 
            * The function also resets the last arrested target and advances the game to the next turn.
            * 
            * @throws std::runtime_error If it is not the Baron's turn.
            * @throws std::runtime_error If the Baron does not have at least 3 coins.
            */
            void invest();

            /**
            * @brief Adds 2 coin to the player , it resets the arrest block trackin ,
            * and allows governors to optionally undo the action,
            * if the Baron is under sanction, he only receives 1 coin instead. 
            * 
            * @return void
            * @throws std::runtime_error If it is not the player's turn.
            */
            void tax() override;



    };
}