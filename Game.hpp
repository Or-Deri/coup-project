#pragma once
#include "Player.hpp"
#include <vector>
#include <string>

namespace coup {
    class Player;
    class Game{
        
        private:

            
            std::vector <Player*> PlayersList;
            int PlayerTurn = 0;

        public:


            Game();
            void addPlayer(Player* player);
            Player* currentPlayer();
            void nextTurn();
            std::string turn();
            std::vector <std::string> players() const;
            std::string winner();
            int playersInTheGame();
            

    };
}