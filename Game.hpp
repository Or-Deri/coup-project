#pragma once
#include <vector>
#include <string>


namespace coup {
    class Player;

    
    class Game{
        
        private:
            std::vector<Player*> playersList;
            int playerTurn;
            std::string lastAction;
            Player* lastPlayer = nullptr;
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
            
            std::string getLastAction();
            void setLastAction(const std::string& name);
            
            Player* getLastPlayer();
            void setLastPlayer(Player* p);

            Player* getLastTarget();
            void setLastTarget(Player* p);
            

            std::vector<Player*> getPlaersList();

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