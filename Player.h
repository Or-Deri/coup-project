#pragma once
#include <string>


class Player {
    
    private:
        int coins;
        std::string name;
        bool inGame:
    public:

        std::string getName const;
        int getCoins const;
        void addCoins(int x);
        void subCoins(int x);
        
        bool isInGame const;
        void lost;


    
}