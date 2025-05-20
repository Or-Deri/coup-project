#pragma once
#include <string>
#include "Game.hpp"

namespace coup {

    class Game;

    class Player {
        
        protected:
            int balance;
            std::string name;
            bool inGame;
            Game* game;
            bool arrestBlocked;
            bool sanctionBlocked;
            Player* lastBlockedBySanction;
            int extraTurns;
            Player* lastTargetArrest;

        public:

            Player( Game& game, const std::string& name);

            std::string getName() const;
            int coins() const;
            void addCoins(int x);
            void subCoins(int x);
            
            bool isInGame() const;
            void setInGame(bool x);

            

            int getExtraTurns();
            void subExtraTurns();
            void setExtraTurns(int x);

            void setArrestBlocked(bool x);
            bool isArrestBlocked() const;

            void setSanctionBlocked(bool x);
            bool isSanctionBlocked();

            Player* getLastTargetArrest() const;
            void setLastTargetArrest(Player* target);

            /**
            * @brief This method is called at the beginning of the player's turn.
            * It resets any sanction block that was applied in the previous round,
            * and enforces the rule that a player with 10 or more coins must perform a coup.
            * 
            * @throws std::runtime_error If it not the player's turn
            * @throws std::runtime_error If the player has 10 or more coins, he mast to do undo
            */
            virtual void startTurn();

            /**
            * @brief Skips the player's turn when no valid actions are available
            * @throws std::runtime_error If it is not the player's turn
            */
            void pass();

            /**
            * @brief Adds 1 coin to the player , and advances the game to the next turn
            * it resets the arrest block trackin.
            * 
            * @return void
            * @throws std::runtime_error If it is not the player's turn.
            * @throws std::runtime_error If the player bloked by sanction
            */
            virtual void gather();

            /**
            * @brief Adds 2 coin to the player , it resets the arrest block trackin ,
            * and allows governors to optionally undo the action
            * 
            * @return void
            * @throws std::runtime_error If it is not the player's turn.
            * @throws std::runtime_error If the player bloked by sanction
            */
            virtual void tax();
            
            /**
            * @brief Grants the player 2 extra turns in exchange for 4 coins,it resets the arrest block trackin
            * and allows judge to optionally undo the action
            * 
            * @throws std::runtime_error If it is not the player's turn.
            * @throws std::runtime_error If to the player does not have enough coins to perform a bribe.
            */
            virtual void bribe();
            
            /**
             * @brief Steals 1 coin from the target player ,
             * if the target is a Merchant they lose 2 coins to the bank instead
             * If the target is a General, nothing happens
             * 
             * @param target Reference to the player being arrested.
             * @throws std::runtime_error If it is not the player's turn.
             * @throws std::runtime_error If the player is blocked from performing arrest
             * @throws std::runtime_error If the player tries to arrest the same target as in their previous arrest.
             */
            void arrest(Player& target);
            
            /**
            * @brief Blocks the target player from performing tax and gather,
            * if the target is a Judge, the action costs 4 coins, for all other roles, it costs 3 coins.
            * 
            * @param target Reference to the player being sanction.
            * @throws std::runtime_error If it is not the player's turn.
            * @throws std::runtime_error If to the player does not have enough coins to perform a sanction.
            */
            void sanction(Player& target);
            
            /**
            * @brief Coup the target player from the game at the cost of 7 coins.
            * 
            * The target player is removed from the game.
            * After the action, the game checks if any General wants to undo the coup.
            * 
            * @param target Reference to the player being coup.
            * 
            * @throws std::runtime_error If it is not the player's turn.
            * @throws std::runtime_error If the player does not have enough coins to perform a coup.
            */
            void coup(Player& target);
    };

}