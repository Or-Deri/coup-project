#pragma once
#include <string>
#include "Game.hpp"

namespace coup {

    class Player {
        
        protected:
            int coins = 0;
            std::string name;
            bool inGame = true:
            Game& game;

        public:

            Player(Game& game, const std::string& name);

            std::string getName() const;
            int getCoins() const;
            void addCoins(int x);
            void subCoins(int x);
            
            bool isInGame() const;
            void lost();
            virtual void startTurn();


            void gather();
            virtual void tax();
            void bribe();
            void sanction(Player& target);
            void coup(Player& target);
        
    }

}