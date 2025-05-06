#pragma once
#include <vector>
#include <string>

namespace coup {
    class Game{
        
        private:
            
            std::vector <Player*> PlayersList;
            int PlayerTurn;

        public:
            Game();
            void addPlayer(Player* player);
            Player* currentPlayer();
            void nextTurn();
            void turn() const;
            sts::vector <std::string> players() const;
            std::string winner() const;
            int playersInTheGame() const;
            

    }
}