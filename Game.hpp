#pragma once
#include "Player.hpp"
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

        public:

            Game();
            void addPlayer(Player* player);
            
            std::string getLastAction();
            void setLastAction(const std::string& name);
            
            Player* getLastPlayer();
            void setLastPlayer(Player* p);
            
            Player* currentPlayer();
            void nextTurn();
            std::string turn();
            std::vector <std::string> players() const;
            std::string winner();
            int playersInTheGame();
            

    };
}