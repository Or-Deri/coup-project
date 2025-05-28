//orderi429@gmail.com
#pragma once
#include <vector>
#include <string>


namespace coup {
    class Player;

    
    class Game{
        
        private:
            /**
             * @brief The list of all players in the game, including eliminated ones.
             * 
             * The order in this list determines the turn rotation.
             */
            std::vector<Player*> playersList;
            /**
            * @brief The index in playersList of the player whose turn it is.
            */
            int playerTurn;
            /**
            * @brief Thename of the last action performed in the game (e.g., "gather", "tax", "coup").
            */
            std::string lastAction;
            /**
            * @brief Pointer to the player who performed the last action.
            */
            Player* lastPlayer = nullptr;
            /**
            * @brief Pointer to the player who was the target of the last action (if any).
            */
            Player* lastTarget; 

        public:

            Game();

            /**
            * @brief Adds a player to the game
            * 
            * @param p pointer to the player to add
            * @return void
            * @throws std::runtime_error if there are alredy 6 players in the game 
            */
            void addPlayer(Player* player);
            /**
            * @brief Gets the last action performed in the game.
            * 
            * @return The name of the last action as a string.
            */
            std::string getLastAction();
            /**
            * @brief Sets the last action performed in the game.
            * 
            * @param name The name of the action.
            */
            void setLastAction(const std::string& name);        
            /**
            * @brief Gets the player who performed the last action.
            * 
            * @return Pointer to the last acting player.
            */
            Player* getLastPlayer();
            /**
            * @brief Sets the player who performed the last action.
            * 
            * @param p Pointer to the player.
            */
            void setLastPlayer(Player* p);
            /**
            * @brief Gets the target of the last action.
            * 
            * @return Pointer to the target player.
            */
            Player* getLastTarget();
            /**
            * @brief Sets the target of the last action.
            * 
            * @param p Pointer to the target player.
            */
            void setLastTarget(Player* p);
            /**
            * @brief Returns the full list of players in the game (including eliminated ones).
            * 
            * @return A vector of pointers to all players.
            */
            std::vector<Player*> getPlayersList();
            /**
             * @brief Returns the current player whose turn it is.
             * 
             * @return Pointer to the player whose turn it currently is.
             */
            Player* currentPlayer();
            /**
            * @brief Advances the turn to the next active player
            * 
            * If the current player has extra turns, they immediately take another turn
            * Otherwise, the turn moves to the next player in the list who is still in the game
            * 
            * @return void
            * @throws std::runtime_error if there are no active players left in the game 
            */
            void nextTurn();
            /**
            * @brief Return the name of the cuurent player
            * 
            * @return std::string The name fo the couurent player
            */
            std::string turn();
            /**
            * @brief Return a vector of the names of all  active players in the game
            * 
            * @return std::vector<std::string> A list of active player name
            */
            std::vector <std::string> players() const;
            /**
            * @brief Checed if hes a winner in game 
            * 
            * @return std::string The name of the winner
            * @throws std::runtime_error If the game is not yet finished 
            */
            std::string winner();
            /**
            * @brief Returns the number of active players in hte game
            * 
            * @return int The number of active players
            */
            int playersInTheGame();
    
            

    };
}