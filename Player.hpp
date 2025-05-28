//orderi429@gmail.com
#pragma once
#include <string>
#include "Game.hpp"

namespace coup {

    class Game;

    class Player {
        
        protected:
            /**
            * @brief The name of the player, used to identify whose turn it is.
            */
            std::string name;
            /**
            * @brief Number of coins currently held by the player.
            */
            int balance;
            /**
            * @brief Indicates whether the player is still active in the game.
            */
            bool inGame;
            /**
            * @brief Pointer to the game instance the player is part of.
            */
            Game* game;
            /**
            * @brief Indicates if the player is blocked from using arrest this turn.
            */
            bool arrestBlocked;
            /**
            * @brief Indicates if the player is blocked from using economic actions (gather/tax) this turn.
            */
            bool sanctionBlocked;
            /**
            * @brief Pointer to the player who was sanctioned by this player in the previous turn.
            * 
            * This is used at the beginning of the current turn to cancel the sanction effect 
            * It is then reset to nullptr after being handled.
            */
            Player* lastSanctionedTarget;
            /**
            * @brief The player that was arrested by this player on their previous turn.
            * 
            * Used to prevent arresting the same player two turns in a row.
            */
            Player* lastTargetArrest;
            /**
            * @brief Number of extra turns this player can take before switching to the next player. 
            * This value is set when a player performs a bribe.
            */
            int extraTurns;
        public:

            Player( Game& game, const std::string& name);

            // Destructor
            virtual ~Player();         
            // Copy constructor       
            Player(const Player& other);
            // Copy assignment
            Player& operator=(const Player& other); 

            /**
            * @brief Returns the name of the player.
            */
            std::string getName() const;
            /**
            * @brief Returns the number of coins the player holds.
            */
            int coins() const;
            /**
            * @brief Adds the given number of coins to the player.
            * @param x Number of coins to add.
            */
            void addCoins(int x);
            /**
            * @brief Subtracts the given number of coins from the player.
            * @param x Number of coins to subtract.
            */
            void subCoins(int x);
            /**
            * @brief Checks whether the player is still active in the game.
            * @return true if the player is active, false otherwise.
            */
            bool getInGame() const;
            /**
            * @brief Sets whether the player is in the game or not.
            * @param x true to mark the player as active, false to eliminate them.
            */
            void setInGame(bool x);
            /**
            * @brief Returns the number of extra turns granted to the player.
            * This is used for the bribe mechanic — when a player performs a bribe, they receive 2 extra turns.
            */
            int getExtraTurns();
            /**
            * @brief Decreases the player's extra turns by 1.
            */
            void subExtraTurns();
            /**
            * @brief Sets the number of extra turns the player has.
            * @param x Number of extra turns to assign.
            */
            void setExtraTurns(int x);
            /**
            * @brief Sets whether the player is blocked from performing arrest.
            * @param x true to block, false to unblock.
            */
            void setArrestBlocked(bool x);
            /**
            * @brief Checks whether the player is blocked from performing arrest.
            * @return true if blocked, false otherwise.
            */
            bool isArrestBlocked() const;
            /**
            * @brief Sets whether the player is blocked from performing economic actions (gather/tax).
            * @param x true to block, false to unblock.
            */
            void setSanctionBlocked(bool x);
            /**
            * @brief Checks whether the player is blocked from gather/tax due to sanction.
            * @return true if blocked, false otherwise.
            */
            bool isSanctionBlocked();
            /**
            * @brief Returns the player who was last arrested by this player.
            */
            Player* getLastTargetArrest() const;
            /**
            * @brief Sets the last player arrested by this player.
            * @param target Pointer to the arrested player.
            */
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