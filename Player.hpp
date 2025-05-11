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
            Player* lastIBlockedArrest;

        public:

            Player( Game& game, const std::string& name);

            std::string getName() const;
            int coins() const;
            void addCoins(int x);
            void subCoins(int x);
            
            bool isInGame() const;
            void setInGame(bool x);
            virtual void startTurn();

            int getExtraTurns();
            void subExtraTurns();

            void setArrestBlocked(bool x);
            bool isArrestBlocked() const;

            void setSanctionBlocked(bool x);
            bool isSanctionBlocked();

            Player* getLastIBlockedArrest() const;
            void setLastIBlockedArrest(Player& target);

            virtual void gather();
            virtual void tax();
            virtual void bribe();
            void arrest(Player& target);
            void sanction(Player& target);
            void coup(Player& target);


        
    };

}